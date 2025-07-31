#include <ESP32BLEKeyboard.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>
#include <EEPROM.h>
#include <SD.h>

// OLED display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Joystick pins
#define VRX A0
#define VRY D2
#define SW  D3

// Bluetooth HID
#include <BleKeyboard.h>
BleKeyboard bleKeyboard;

// IR setup
#define IR_RECEIVE_PIN D5
#define IR_SEND_PIN D6
IRrecv irrecv(IR_RECEIVE_PIN);
IRsend irsend(IR_SEND_PIN);
decode_results results;

// Menu navigation
int currentMenu = 0;
int currentSubMenu = 0;
bool inSubMenu = false;
bool inApp = false;

String mainMenu[] = {"IR", "RF", "WiFi", "USB", "Bluetooth"};
String irMenu[] = {"Scan and Store", "Blast", "IR List", "Exit"};
String rfMenu[] = {"Scan", "Sniffing", "Blocking", "Emulating", "Exit"};
String wifiMenu[] = {"Scan", "Attacks", "Repeater", "Exit"};
String usbMenu[] = {"BadUSB Payloads", "USB Killer Format", "Exit"};
String bluetoothMenu[] = {"BLE HID Keyboard", "Bluetooth Extender", "Bluetooth Attack", "Exit"};

#define MAX_CODES 10
String savedCodes[MAX_CODES];
int savedCodeCount = 0;

// SD Card setup
#define SD_CS 5

// Setup
void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.display();
  
  pinMode(SW, INPUT_PULLUP);

  irrecv.enableIRIn();
  irsend.begin();

  welcomeScreen();
  drawMenu();

  // Initialize SD card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card initialization failed!");
    return;
  }
  Serial.println("SD Card initialized.");
}

// Loop
void loop() {
  int xValue = analogRead(VRX);
  bool yValue = digitalRead(VRY);
  bool buttonPressed = !digitalRead(SW);

  if (inApp) {
    if (buttonPressed) {
      inApp = false;
      drawMenu();
      delay(300);
    }
    return;
  }

  if (xValue < 300) {
    moveMenu(-1);
  } else if (xValue > 700) {
    moveMenu(1);
  }

  if (buttonPressed) {
    selectMenu();
    delay(300);
  }
}

// Navigation and Menu Functions
void moveMenu(int direction) {
  if (!inSubMenu) {
    currentMenu += direction;
    if (currentMenu < 0) currentMenu = 4;  // Main menu options are 5 items
    if (currentMenu > 4) currentMenu = 0;
  } else {
    switch (currentMenu) {
      case 0: currentSubMenu += direction; if (currentSubMenu < 0) currentSubMenu = 2; if (currentSubMenu > 2) currentSubMenu = 0; break;
      case 1: currentSubMenu += direction; if (currentSubMenu < 0) currentSubMenu = 4; if (currentSubMenu > 4) currentSubMenu = 0; break;
      case 2: currentSubMenu += direction; if (currentSubMenu < 0) currentSubMenu = 3; if (currentSubMenu > 3) currentSubMenu = 0; break;
      case 3: currentSubMenu += direction; if (currentSubMenu < 0) currentSubMenu = 2; if (currentSubMenu > 2) currentSubMenu = 0; break;
      case 4: currentSubMenu += direction; if (currentSubMenu < 0) currentSubMenu = 3; if (currentSubMenu > 3) currentSubMenu = 0; break;
    }
  }
  drawMenu();
}

void selectMenu() {
  if (!inSubMenu) {
    inSubMenu = true;
    currentSubMenu = 0;
  } else {
    bool exitSelected = false;
    switch (currentMenu) {
      case 0: exitSelected = (currentSubMenu == 3); break;
      case 1: exitSelected = (currentSubMenu == 4); break;
      case 2: exitSelected = (currentSubMenu == 3); break;
      case 3: exitSelected = (currentSubMenu == 2); break;
      case 4: exitSelected = (currentSubMenu == 3); break;
    }
    if (exitSelected) {
      inSubMenu = false;
    } else {
      runApp(currentMenu, currentSubMenu);
    }
  }
  drawMenu();
}

void drawMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  if (!inSubMenu) {
    display.println(F("Main Menu"));
    for (int i = 0; i < 5; i++) {
      if (i == currentMenu) display.print("> ");
      else display.print("  ");
      display.println(mainMenu[i]);
    }
  } else {
    switch (currentMenu) {
      case 0: drawSubMenu(irMenu, 4); break;
      case 1: drawSubMenu(rfMenu, 5); break;
      case 2: drawSubMenu(wifiMenu, 4); break;
      case 3: drawSubMenu(usbMenu, 3); break;
      case 4: drawSubMenu(bluetoothMenu, 4); break;
    }
  }
  display.display();
}

void drawSubMenu(String menu[], int size) {
  display.println(mainMenu[currentMenu]);
  for (int i = 0; i < size; i++) {
    if (i == currentSubMenu) display.print("> ");
    else display.print("  ");
    display.println(menu[i]);
  }
}

// IR Functions
void scanIR() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Waiting IR...");
  display.display();

  unsigned long start = millis();
  while (millis() - start < 5000) {
    if (irrecv.decode(&results)) {
      String code = resultToHexidecimal(&results);
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("IR Code:");
      display.println(code);

      if (savedCodeCount < MAX_CODES) {
        savedCodes[savedCodeCount++] = code;
      }

      display.display();
      delay(2000);
      irrecv.resume();
      break;
    }
    yield();
  }
}

void blastIR() {
  if (savedCodeCount == 0) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("No IR codes.");
    display.display();
    delay(2000);
    return;
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Blasting Code:");
  display.println(savedCodes[0]);
  display.display();

  uint32_t code = strtoul(savedCodes[0].c_str(), NULL, 16);
  irsend.sendNEC(code, 32);

  delay(2000);
}

void irList() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("IR Code List:");
  for (int i = 0; i < savedCodeCount; i++) {
    display.println(savedCodes[i]);
  }
  display.display();
  delay(3000);
}

// Bluetooth Functions
void startBluetoothHID() {
  BLEDevice::init("FlipperZero BLE HID");

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x1812));
  pService->start();

  bleKeyboard.begin();

  while (!bleKeyboard.isConnected()) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Bluetooth HID");
    display.println("Waiting for connection...");
    display.display();
    delay(1000);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Bluetooth HID");
  display.println("Connected!");
  display.display();
  delay(2000);
}

void startBluetoothExtender() {
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->start(5, false);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Bluetooth Extender");
  display.println("Scanning devices...");
  display.display();

  delay(5000);
}

void startBluetoothAttack() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Bluetooth Attack");
  display.println("Running...");
  display.display();
  delay(5000);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Attack Complete!");
  display.display();
  delay(2000);
}

// Run selected app
void runApp(int menuIndex, int subMenuIndex) {
  switch (menuIndex) {
    case 0: 
      switch (subMenuIndex) {
        case 0: scanIR(); break;
        case 1: blastIR(); break;
        case 2: irList(); break;
        default: break;
      }
      break;
    case 1: break;  // RF Code goes here
    case 2: break;  // Wi-Fi Code goes here
    case 3: break;  // USB Code goes here
    case 4: 
      switch (subMenuIndex) {
        case 0: startBluetoothHID(); break;
        case 1: startBluetoothExtender(); break;
        case 2: startBluetoothAttack(); break;
        default: break;
      }
      break;
    default: break;
  }
}
