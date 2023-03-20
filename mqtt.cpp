#include "mqtt.h"

#include "global.h"
#include "log.h"
#include "settings.h"


void globalMQTTCallback(char* topic, byte* payload, unsigned int length)
{
  //LOG_DEBUG("start mqtt callback");
  g_mqtt.callback(topic, payload, length);  
}


void MQTT::callback(char* topic, byte* payload, unsigned int length)
{
  if (0 != strncmp(g_settings.mqtt_sensorid_param, topic, strlen(g_settings.mqtt_sensorid_param)))
  {
    LOG_INFO((String("Ignoring unrelated mqtt::callback ")+String(topic)).c_str());
    return;
  }

  String value;
  value.concat(reinterpret_cast<const char*>(payload), length);

  LOG_DEBUG((String("mqttCallback: ")+String(topic)+String(" value ")+value).c_str());

  const char* key = topic + strlen(g_settings.mqtt_sensorid_param);
  if (0 == strcmp("config/humidity_diff_trigger", key))
  {
    g_settings.conf_humidity_diff_trigger_value = max(-100.0, min(100.0, atof(value.c_str())));
    LOG_INFO((String("mqttCallback conf_humidity_diff_trigger_value=")+String((float)g_settings.conf_humidity_diff_trigger_value)).c_str());
  }
  else if (0 == strcmp("config/power_fan_cutoff", key))
  {
    g_settings.conf_power_fan_cutoff_value = max(0.0, min(15.0, atof(value.c_str())));
    LOG_INFO((String("mqttCallback conf_power_fan_cutoff_value=")+String((float)g_settings.conf_power_fan_cutoff_value)).c_str());
  }
}

bool MQTT::publishMQTTValue(const String& topic, const String& msg)
{
  //LOG_DEBUG("start mqtt::publishMQTTValue1");
  if (isEnabled() && connectMQTT())
  {
    if (!mqtt_client.publish((String(g_settings.mqtt_sensorid_param)+topic).c_str(), msg.c_str(), true))
    {
#if (LOG_LEVEL>LOG_LEVEL_NONE)
      if (g_log.log_mode!=Log::LOG_NONE)
      {
        Serial.println((String("publishMQTTValue topic=")+String(g_settings.mqtt_sensorid_param)+topic+String(" msg=")+msg+String(" returned false")).c_str());
      }
#endif // (LOG_LEVEL>=LOG_LEVEL_ERROR)
      return false;
    }
    return true;
  }
  else
  {
    LOG_ERROR("Cannot publish. Not connected");
    return false;
  }
}

bool MQTT::publishMQTTValue(const String& topic, float value)
{
  //LOG_DEBUG("start mqtt::publishMQTTValue2");
  return publishMQTTValue(topic, String(value, 4));
}

bool MQTT::connectMQTT()
{
  //LOG_DEBUG("start mqtt::connectMQTT");
  byte i = 0;
  while (i++<10 && isEnabled() && !mqtt_client.connected())
  {
    LOG_DEBUG("MQTT connect");
    if (mqtt_client.connect(g_settings.mqtt_sensorid_param, g_settings.mqtt_username_param, g_settings.mqtt_password_param))
    {
      LOG_INFO("MQTT connected");

      bool subscribe_ok = true;
      
      String topic;

      topic = String(g_settings.mqtt_sensorid_param)+F("config/humidity_diff_trigger");
      LOG_INFO((String("Subscribing to ") + topic).c_str());
      subscribe_ok &= mqtt_client.subscribe(topic.c_str());

      topic = String(g_settings.mqtt_sensorid_param)+F("config/power_fan_cutoff");
      LOG_INFO((String("Subscribing to ") + topic).c_str());
      subscribe_ok &= mqtt_client.subscribe(topic.c_str());

      if (!subscribe_ok)
      {
        LOG_ERROR("MQTT topics subscribed with error");
      }
    }
    else
    {
      LOG_INFO("MQTT waiting for reconnect");
      LOG_DEBUG(g_settings.mqtt_sensorid_param);
      LOG_DEBUG(g_settings.mqtt_username_param);
      LOG_DEBUG(g_settings.mqtt_password_param);
      // Wait 3 seconds before retrying
      delay(3000);
    }
  }
  return mqtt_client.connected();
}

bool MQTT::isRequested()
{
  return g_settings.mqtt_servername_param && *g_settings.mqtt_servername_param;
}

void MQTT::initialize()
{
  LOG_DEBUG("start mqtt::initialize");
  mqtt_client.setClient(esp_client);
  mqtt_client.setServer(g_settings.mqtt_servername_param, 1883);
  mqtt_client.setCallback(globalMQTTCallback);
  mqtt_enabled = true;
  connectMQTT();
}

void MQTT::loop()
{
  mqtt_client.loop();
}
