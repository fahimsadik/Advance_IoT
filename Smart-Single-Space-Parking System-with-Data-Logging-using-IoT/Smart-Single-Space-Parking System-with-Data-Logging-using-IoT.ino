#include <WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

const char* ssid = "Wokwi-GUEST"; // write your "wifi name"
const char* pass = ""; // write your "wifi password"
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 2653929;
const char* myWriteAPIKey = "QYJZ9XE6NS32ZLQ1";

const int TRIG_PIN = 12; 
const int ECHO_PIN = 13;
#define ledping 0
#define ledpinr 2

long duration;
int distance;
String status;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);  
  pinMode(ECHO_PIN, INPUT);   
  pinMode(ledping, OUTPUT);
  pinMode(ledpinr,OUTPUT);
  Serial.begin(115200);  //Initialize serial
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(ledping, LOW);
  digitalWrite(ledpinr, LOW);
   duration = pulseIn(ECHO_PIN, HIGH);
  
  distance = duration * 0.0344  / 2;

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
if (distance <200 ) {
    status = "Parking Occupied";
    Serial.println("Parking Occupied");
    digitalWrite(ledpinr, HIGH);
    digitalWrite(ledping, LOW);
  }

  else {
    status = "Parking Available";
    Serial.println("Parking Available");
    digitalWrite(ledping, HIGH);
    digitalWrite(ledpinr, LOW);
    }
 
  ThingSpeak.setField(1, distance);  // Send distance to field 1
  ThingSpeak.setField(2, status);    // Send parking status to field 2

  // Update the channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(20000); 
}
