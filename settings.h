#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#ifdef TESTING
# include "testing.h"
#else
# include <DNSServer.h>
# include <EEPROM.h>
# include <ESP8266WebServer.h>
#endif

#include "global.h"


void handleNotFound();
void handleSetupRoot();

class Settings
{
public:
  static constexpr const char* SETUP_SSID = "sensor-setup";
  static constexpr byte  EEPROM_INITIALIZED_MARKER = 0xF2; //Just a magic number. CHange when EEPROM data format is incompatibly changed

  static constexpr byte MAX_SSID_LENGTH            = 32;
  static constexpr byte MAX_PASSWORD_LENGTH        = 64;
  static constexpr byte MAX_MQTT_SERVERNAME_LENGTH = 64;
  static constexpr byte MAX_MQTT_SERVERPORT_LENGTH =  5;
  static constexpr byte MAX_MQTT_SENSORID_LENGTH   = 32;
  static constexpr byte MAX_MQTT_USERNAME_LENGTH   = 32;
  static constexpr byte MAX_MQTT_PASSWORD_LENGTH   = 32;

  static constexpr uint16_t MQTT_DEFAULT_PORT = 1883;

  static constexpr float        DEFAULT_CONF_HUMIDITY_DIFF_TRIGGER_VALUE = 5.0f;  //[-100.0 - 100.0]
  static constexpr float        DEFAULT_CONF_POWER_FAN_CUTOFF_VALUE      = 12.5f; //[0.0 - 15.0]
  static constexpr const char*  DEFAULT_SENSORID = "/Dehumidifer/Sensor1/";

public:
  Settings();
  void enable();
  void readPersistentString(char* s, int max_length, int& adr);
  void readPersistentByte(uint8_t& b, int& adr);
  void readPersistentParams();
  void writePersistentString(const char* s, size_t max_length, int& adr);
  void writePersistentByte(uint8_t b, int& adr);
  void writePersistentParams(const char* ssid, const char* password);
  void handleNotFound();
  void handleSetupRoot();
  void activateSetupAP();
  bool activateWifi();
  void processNetwork(bool setup_mode);

public:
  std::shared_ptr<ESP8266WebServer> server;

  //For SETUP_SSID AP
  DNSServer dnsServer;
  static constexpr const byte DNS_PORT = 53;
  std::shared_ptr<IPAddress> apIP;

  char ssid_param[MAX_SSID_LENGTH+1];
  char password_param[MAX_PASSWORD_LENGTH+1];
  char mqtt_servername_param[MAX_MQTT_SERVERNAME_LENGTH+1];
  uint16_t mqtt_serverport_param = MQTT_DEFAULT_PORT;
  char mqtt_sensorid_param[MAX_MQTT_SENSORID_LENGTH+1];
  char mqtt_username_param[MAX_MQTT_USERNAME_LENGTH+1];
  char mqtt_password_param[MAX_MQTT_PASSWORD_LENGTH+1];

  float conf_humidity_diff_trigger_value;
  float conf_power_fan_cutoff_value;
};

#endif // _SETTINGS_H_
