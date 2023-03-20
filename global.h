#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef TESTING
# include "testing.h"
#else
# include <pins_arduino.h>
#endif

static constexpr uint8_t I_SETUP_MODE_PIN               = D7; // pull Up to enable setup mode
static constexpr uint8_t O_VOLTAGE_ACTIVATE_PIN         = D2;
static constexpr uint8_t I_INDOOR_TEMPHUMID_SENSOR_PIN  = D3;
static constexpr uint8_t I_OUTDOOR_TEMPHUMID_SENSOR_PIN = D4;
static constexpr uint8_t O_FAN_RELAY_ACTIVATE_PIN       = D5;

static constexpr uint16_t MAX_ANALOG_VALUE = 1023.0;


static constexpr uint8_t OLD = 0;
static constexpr uint8_t CURRENT = 1;


class Log;
extern Log g_log;

class MQTT;
extern MQTT g_mqtt;

class NTP;
extern NTP g_ntp;

class Settings;
extern Settings g_settings;

#endif // _GLOBAL_H_
