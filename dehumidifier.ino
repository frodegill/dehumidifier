#include "global.h"

#include "log.h"
#include "mqtt.h"
#include "ntp.h"
#include "settings.h"

#ifdef TESTING
# include "testing.h"
#else
# include <DHTesp.h>           // Library: DHT_sensor_library_for_ESPx
# include <Ticker.h>
# include <TimeLib.h>
# include <math.h>
#endif

/*
 MQTT paths:
 dehumidifier/<sensorid>/indoor_temp
 dehumidifier/<sensorid>/indoor_humidity
 dehumidifier/<sensorid>/outdoor_temp
 dehumidifier/<sensorid>/outdoor_humidity
 dehumidifier/<sensorid>/humidity_diff
 dehumidifier/<sensorid>/voltage
 dehumidifier/<sensorid>/config/humidity_diff_trigger                      [-100.0 - 100.0]
 dehumidifier/<sensorid>/config/power_fan_cutoff                           [0.0 - 15.0]
 dehumidifier/<sensorid>/debug
 */

#define DHT_MODEL (DHTesp::AM2302)

#if (LOG_LEVEL>LOG_LEVEL_NONE)
  Log g_log;
#endif // (LOG_LEVEL>LOG_LEVEL_NONE)
MQTT g_mqtt;
NTP g_ntp;
time_t local_time;
Settings g_settings;
DHTesp indoor_dht;
DHTesp outdoor_dht;

bool setup_mode;

volatile uint16_t fan_value[2];
float indoor_tempsensor_value[2];
float indoor_humiditysensor_value[2];
float outdoor_tempsensor_value[2];
float outdoor_humiditysensor_value[2];
float humidity_diff_value[2];
float voltage_value[2];

void updateValue(const String& topic, float new_value, volatile float& old_value)
{
  if (new_value != old_value)
  {
    g_mqtt.publishMQTTValue(topic, String(new_value));
    old_value = new_value;
  }
}

void updateValue(const String& topic, uint16_t new_value, volatile uint16_t& old_value)
{
  if (new_value != old_value)
  {
    g_mqtt.publishMQTTValue(topic, String(new_value));
    old_value = new_value;
  }
}

void setup()
{
  Serial.end();
  Serial1.end();
  delay(1000);

#if (LOG_LEVEL>LOG_LEVEL_NONE)
  g_log.enable();
  LOG_INFO("start setup");
#endif // (LOG_LEVEL>LOG_LEVEL_NONE)

  g_settings.enable();
  
  pinMode(I_SETUP_MODE_PIN, INPUT);
  delay(100);

  if (HIGH == digitalRead(I_SETUP_MODE_PIN))
  {
    LOG_INFO("Mode = SETUP");
    setup_mode = true;
    g_settings.activateSetupAP();
  }
  else
  {
    LOG_INFO("Mode = NORMAL");
    setup_mode = false;

    pinMode(I_INDOOR_TEMPHUMID_SENSOR_PIN, OUTPUT); //DHT handles this pin itself, but it should be OUTPUT before setup
    indoor_dht.setup(I_INDOOR_TEMPHUMID_SENSOR_PIN, DHT_MODEL);

    pinMode(I_OUTDOOR_TEMPHUMID_SENSOR_PIN, OUTPUT); //DHT handles this pin itself, but it should be OUTPUT before setup
    outdoor_dht.setup(I_OUTDOOR_TEMPHUMID_SENSOR_PIN, DHT_MODEL);

    pinMode(O_VOLTAGE_ACTIVATE_PIN, OUTPUT);
    pinMode(O_FAN_RELAY_ACTIVATE_PIN, OUTPUT);

    digitalWrite(O_VOLTAGE_ACTIVATE_PIN, LOW);
    digitalWrite(O_FAN_RELAY_ACTIVATE_PIN, LOW);

    fan_value[CURRENT] = fan_value[OLD] = 0;
    indoor_tempsensor_value[CURRENT] = indoor_tempsensor_value[OLD] = 0.0f;
    indoor_humiditysensor_value[CURRENT] = indoor_humiditysensor_value[OLD] = 0.0f;
    outdoor_tempsensor_value[CURRENT] = outdoor_tempsensor_value[OLD] = 0.0f;
    outdoor_humiditysensor_value[CURRENT] = outdoor_humiditysensor_value[OLD] = 0.0f;
    humidity_diff_value[CURRENT] = humidity_diff_value[OLD] = 0.0f;
    voltage_value[CURRENT] = voltage_value[OLD] = 0.0f;

    if (!g_settings.activateWifi())
    {
      // reset?
    }
  }
}

void loop()
{
  if (!setup_mode)
  {
    //Read indoor temp/humidity
    delay(max(1000, indoor_dht.getMinimumSamplingPeriod()));
    TempAndHumidity temp_and_humidity = indoor_dht.getTempAndHumidity();
    if (indoor_dht.getStatus() == DHTesp::ERROR_NONE)
    {
      indoor_tempsensor_value[CURRENT] = temp_and_humidity.temperature;
      indoor_humiditysensor_value[CURRENT] = temp_and_humidity.humidity;

      updateValue(F("indoor_temp"), indoor_tempsensor_value[CURRENT], indoor_tempsensor_value[OLD]);
      updateValue(F("indoor_humidity"), indoor_humiditysensor_value[CURRENT], indoor_humiditysensor_value[OLD]);
    }
    else
    {
      LOG_ERROR((String("reading indoor temp and humidity failed with error ")+String((int)indoor_dht.getStatus())).c_str());
    }

    //Read outdoor temp/humidity
    delay(max(1000, outdoor_dht.getMinimumSamplingPeriod()));
    temp_and_humidity = outdoor_dht.getTempAndHumidity();
    if (outdoor_dht.getStatus() == DHTesp::ERROR_NONE)
    {
      outdoor_tempsensor_value[CURRENT] = temp_and_humidity.temperature;
      outdoor_humiditysensor_value[CURRENT] = temp_and_humidity.humidity;

      updateValue(F("outdoor_temp"), outdoor_tempsensor_value[CURRENT], outdoor_tempsensor_value[OLD]);
      updateValue(F("outdoor_humidity"), outdoor_humiditysensor_value[CURRENT], outdoor_humiditysensor_value[OLD]);
    }
    else
    {
      LOG_ERROR((String("reading outdoor temp and humidity failed with error ")+String((int)outdoor_dht.getStatus())).c_str());
    }

    //Calculate what outdoor humidity would be for indoor temp
    float otemp = outdoor_tempsensor_value[CURRENT];
    float ohumid = outdoor_humiditysensor_value[CURRENT];
    float itemp = indoor_tempsensor_value[CURRENT];
    float constA = 17.625;
    float constB = 243.04;
    float dew = constB*(log(ohumid/100.0)+((constA*otemp)/(constB+otemp))) / (constA-log(ohumid/100.0)-((constA*otemp)/(constB+otemp)));
    float oihumid = 100.0*exp((constA*dew)/(constB+dew)) / exp((constA*itemp)/(constB+itemp));
    humidity_diff_value[CURRENT] = outdoor_humiditysensor_value[CURRENT] - oihumid;
    updateValue(F("humidity_diff"), humidity_diff_value[CURRENT], humidity_diff_value[OLD]);

    //Read voltage
    digitalWrite(O_VOLTAGE_ACTIVATE_PIN, HIGH);
    delay(100);
    voltage_value[CURRENT] = analogRead(A0)*15.0/MAX_ANALOG_VALUE; 
    digitalWrite(O_VOLTAGE_ACTIVATE_PIN, LOW);
    updateValue(F("voltage"), voltage_value[CURRENT], voltage_value[OLD]);

    //Start or stop the fan?
    if (humidity_diff_value[CURRENT]>g_settings.conf_humidity_diff_trigger_value &&
        voltage_value[CURRENT]>g_settings.conf_power_fan_cutoff_value)
    {
      digitalWrite(O_FAN_RELAY_ACTIVATE_PIN, HIGH);
    }
    else
    {
      digitalWrite(O_FAN_RELAY_ACTIVATE_PIN, LOW);
    }
  }

  //Wait a minute
  int i;
  for (i=0; i<60; i++)
  {
    g_settings.processNetwork(setup_mode);
    delay(1000);
  }
}
