#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define RELAY1_PIN 0    // GPIO0
#define RELAY2_PIN 2    // GPIO2
#define SWITCH_PIN 3    // GPIO3 (RX pin on ESP-01)

const char* ssid = "Mr. Great Guy";
const char* password = "fahim25j2002";

const char* APP_KEY = "1279c102-2eec-4e0e-a161-386dd81e009d";
const char* APP_SECRET = "88a3a61f-0d53-435a-8c56-0719e87a8e94-e9e2bef2-a78f-4423-842f-f6d53db93dcb";
const char* device1_ID = "67fd545fdc4a25d5c3af97ce";
const char* device2_ID = "67fd5487bddfc53e33d772f6";

bool relay1State = false;
bool relay2State = false;

unsigned long lastSwitchToggle = 0;
bool lastSwitchState = HIGH;

void saveStatesToEEPROM() {
  EEPROM.write(0, relay1State);
  EEPROM.write(1, relay2State);
  EEPROM.commit();
}

void loadStatesFromEEPROM() {
  relay1State = EEPROM.read(0);
  relay2State = EEPROM.read(1);
}

void applyRelayStates() {
  digitalWrite(RELAY1_PIN, relay1State ? LOW : HIGH);
  digitalWrite(RELAY2_PIN, relay2State ? LOW : HIGH);
}

void toggleRelays() {
  relay1State = !relay1State;
  relay2State = !relay2State;
  applyRelayStates();
  saveStatesToEEPROM();

  // Update Sinric App
  SinricProSwitch &mySwitch1 = SinricPro[device1_ID];
  SinricProSwitch &mySwitch2 = SinricPro[device2_ID];
  mySwitch1.sendPowerStateEvent(relay1State);
  mySwitch2.sendPowerStateEvent(relay2State);
}

bool onPowerState1(const String &deviceId, bool &state) {
  relay1State = state;
  applyRelayStates();
  saveStatesToEEPROM();
  Serial.printf("Relay 1 turned %s\n", state ? "ON" : "OFF");
  return true;
}

bool onPowerState2(const String &deviceId, bool &state) {
  relay2State = state;
  applyRelayStates();
  saveStatesToEEPROM();
  Serial.printf("Relay 2 turned %s\n", state ? "ON" : "OFF");
  return true;
}

void setupWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");
}

void checkSwitch() {
  bool currentSwitchState = digitalRead(SWITCH_PIN);
  if (currentSwitchState == LOW && lastSwitchState == HIGH && (millis() - lastSwitchToggle) > 300) {
    toggleRelays();
    lastSwitchToggle = millis();
  }
  lastSwitchState = currentSwitchState;
}

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);  // Button to GND

  EEPROM.begin(512);
  loadStatesFromEEPROM();
  applyRelayStates();

  setupWiFi();

  SinricProSwitch &mySwitch1 = SinricPro[device1_ID];
  SinricProSwitch &mySwitch2 = SinricPro[device2_ID];
  mySwitch1.onPowerState(onPowerState1);
  mySwitch2.onPowerState(onPowerState2);

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);  // optional, handled via EEPROM too
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setupWiFi(); // Retry if WiFi lost
  }

  SinricPro.handle();
  checkSwitch();
}
