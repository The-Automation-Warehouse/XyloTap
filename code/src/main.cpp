
#include <Arduino.h>
#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <IntervalTimer.h>

// The keys are CDEFGAHCDEFGAHCD


const uint8_t solenoids[16] = {0, 2, 4, 6, 1, 3, 5, 7, 28, 25, 24, 12, 11, 10, 9, 8};
unsigned long solenoidOnDurations[16] = {16, 16, 16, 18, 16, 14, 16, 16, 13, 14, 14, 15, 16, 16, 16, 16};
unsigned long solenoidOnTimes[16];
bool solenoidStates[16];
const uint8_t leds[16] = {41, 40, 39, 38, 37, 36, 35, 34, 32, 31, 30, 27, 26, 23, 22, 33};

void strikeKey(int key);
void turnOffKey(int key);
void checkSolenoids();

IntervalTimer solenoidTimer;

#define YellowLED 15
#define BlueLED 14

#define UP_BUTTON 20
#define DOWN_BUTTON 21
#define CONFIRM_BUTTON 29

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// SD
File root;
void printDirectory(File dir, int numTabs);


// MCP23017
#define INTA_PIN 16
#define INTB_PIN 17
Adafruit_MCP23X17 mcp;
void handleMCP();

void setup() {

  pinMode(CONFIRM_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  pinMode(YellowLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  digitalWrite(YellowLED, HIGH);
  digitalWrite(BlueLED, LOW);

  Serial.begin(115200);

  for (uint8_t i = 0; i < 16; i++) {
    pinMode(solenoids[i], OUTPUT);
    digitalWrite(solenoids[i], LOW);
    solenoidOnTimes[i] = 0;
    solenoidStates[i] = false;
  }
  for (uint8_t i = 0; i < 16; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
  }

  solenoidTimer.begin(checkSolenoids, 200);


  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(300);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SD Card: ");

  // SD
  if (!SD.begin(BUILTIN_SDCARD)) {
    lcd.print("Error");
  } else {
    lcd.print("OK");
  }

  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  // MCP23017
  if (!mcp.begin_I2C()) {
    Serial.println("MCP Error.");
  }

  pinMode(INTA_PIN, INPUT);
  pinMode(INTB_PIN, INPUT);
  pinMode(7, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(INTA_PIN), handleMCP, FALLING);
  attachInterrupt(digitalPinToInterrupt(INTB_PIN), handleMCP, FALLING);

  mcp.clearInterrupts();
  for (uint8_t i = 0; i < 16; i++) {
    mcp.disableInterruptPin(i);
  }

  for (uint8_t i = 0; i < 16; i++) {
    mcp.pinMode(i, INPUT_PULLUP);
  }

  mcp.setupInterrupts(false, false, LOW);
  
  for (uint8_t i = 0; i < 16; i++) {
    mcp.setupInterruptPin(i, CHANGE);
  }

  Serial.println("Looping...");

  digitalWrite(BlueLED, HIGH);
}

void loop() {

  // Test pattern

  if (digitalRead(CONFIRM_BUTTON) == LOW) {
    // Blink solenoids and leds
    for (uint8_t i = 0; i < 16; i++) {
      strikeKey(i);
      delay(300);
    }
  }

  // Play pattern

  if (digitalRead(DOWN_BUTTON) == LOW) {
    for (uint8_t i = 0; i < 2; i++) {
      strikeKey(0);
      delay(200);
      strikeKey(2);
      delay(100);
      strikeKey(4);
      delay(100);
      strikeKey(5);
      delay(200);
      strikeKey(7);
      delay(100);
      strikeKey(9);
      delay(100);
      strikeKey(7);
      delay(200);
    }
    strikeKey(1);
    delay(400);
    strikeKey(3);
    delay(200);
    strikeKey(14);
    delay(400);
    strikeKey(15);
    delay(400);
    strikeKey(16);
    delay(200);
    strikeKey(10);
    delay(100);
    strikeKey(4);
    delay(100);
    strikeKey(6);
    delay(200);

    for (uint8_t i = 0; i < 2; i++) {
      strikeKey(0);
      delay(200);
      strikeKey(2);
      delay(100);
      strikeKey(4);
      delay(100);
      strikeKey(5);
      delay(200);
      strikeKey(7);
      delay(100);
      strikeKey(9);
      delay(100);
      strikeKey(7);
      delay(200);
    }
  }

}

void handleMCP() {
  int pin = mcp.getLastInterruptPin();
  if (pin == 255) {
    return;
  }

  // If button 14 is pressed, toggle pin 7 and build in LED on Teensy 4.1
  if (pin == 14) {
    digitalWrite(7, !digitalRead(7));
    digitalWrite(LED_BUILTIN, digitalRead(7));
  }
  Serial.print("Interrupt detected on pin: ");
  Serial.println(mcp.getLastInterruptPin());
  mcp.clearInterrupts();  // clear


}


void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}












// Strike keys for a certain amount of time
void strikeKey(int key) {
  digitalWrite(solenoids[key], HIGH);
  digitalWrite(leds[key], LOW);
  solenoidOnTimes[key] = millis();
  solenoidStates[key] = true;
}

void turnOffKey(int key) {
  digitalWrite(solenoids[key], LOW);
  digitalWrite(leds[key], HIGH);
  solenoidStates[key] = false;
}

void checkSolenoids() {
  for (uint8_t i = 0; i < 16; i++) {
    if (solenoidStates[i] && (millis() - solenoidOnTimes[i] > solenoidOnDurations[i])) {
      turnOffKey(i);
    }
  }
}