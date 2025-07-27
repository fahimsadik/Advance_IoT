# ESP8266 SinricPro Smart Switch
This project uses an ESP8266 to create a smart switch that can be integrated with smart home platforms like Alexa or Google Assistant via the SinricPro service. The code controls two relays and a switch, allowing you to turn devices on or off remotely. It uses the 

SinricPro and SinricProSwitch libraries to provide this functionality.

# Components Needed
ESP8266 board (e.g., NodeMCU)

2 or 3-channel Relay Module

A push button (optional)

Jumper wires

Circuit Connections

Relay 1: Connect the relay's control pin to GPIO0 on the ESP8266.


Relay 2: Connect the relay's control pin to GPIO2 on the ESP8266.


Switch: Connect the switch to GPIO3 on the ESP8266.

# Libraries Used
ESP8266WiFi.h

EEPROM.h

SinricPro.h

SinricProSwitch.h

# Code Description
The 

setup() function connects the ESP8266 to your Wi-Fi network using the provided ssid and password. It then initializes the SinricPro service with your unique 

APP_KEY and APP_SECRET. The code defines pins for two relays (RELAY1_PIN, RELAY2_PIN) and one switch (SWITCH_PIN) and sets their initial states. The loop() function handles the SinricPro client, keeping it connected and processing commands from your smart home assistant.

Note: You will need to replace the placeholder Wi-Fi credentials, APP_KEY, and APP_SECRET with your own details from your SinricPro account.
