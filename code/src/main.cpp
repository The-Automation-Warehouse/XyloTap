#include <Arduino.h>
#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SdFat.h>
#include <IntervalTimer.h>
#include <MD_MIDIFile.h>
#include "helperFunctions.h"
#include <iostream>

// The keys are CDEFGAHCDEFGAHCD


const uint8_t solenoids[16] = {0, 2, 4, 6, 1, 3, 5, 7, 28, 25, 24, 12, 11, 10, 9, 8};
unsigned long solenoidOnDurations[16] = {18, 18, 18, 19, 16, 16, 16, 15, 15, 15, 17, 16, 16, 16, 16, 16};
unsigned long solenoidOnTimes[16];
bool solenoidStates[16];
const uint8_t leds[16] = {41, 40, 39, 38, 37, 36, 35, 34, 32, 31, 30, 27, 26, 23, 22, 33};

extern void strikeKey(int key);
extern void turnOffKey(int key);
extern void checkSolenoids();

IntervalTimer solenoidTimer;

#define YellowLED 15
#define BlueLED 14

#define UP_BUTTON 29
#define DOWN_BUTTON 20
#define CONFIRM_BUTTON 21

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
int menuIndex = 0;
bool refreshMenu = true;
String songList[32];

// SDFat

// SDCARD_SS_PIN is defined for the built-in SD on some boards.
#ifndef SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SS;
#else  // SDCARD_SS_PIN
// Assume built-in SD is used.
const uint8_t SD_CS_PIN = SDCARD_SS_PIN;
#endif  // SDCARD_SS_PIN

// Try max SPI clock for an SD. Reduce SPI_CLOCK if errors occur.
#define SPI_CLOCK SD_SCK_MHZ(50)

// Try to select the best SD card configuration.
#if HAS_SDIO_CLASS
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif  ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_CLOCK)
#else  // HAS_SDIO_CLASS
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_CLOCK)
#endif  // HAS_SDIO_CLASS
SdFat SD;
MD_MIDIFile SMF;

extern void midiCallback(midi_event *pev);
extern int midiNoteToKey(int midiNote);
extern void testPattern();
void playSong(String name);
void stopSong();

// MCP23017
#define INTA_PIN 16
#define INTB_PIN 17
Adafruit_MCP23X17 mcp;
extern void handleMCP();


void resetTeensy() {digitalWrite(BlueLED, LOW);  SCB_AIRCR = 0x05FA0004;}

void setup() {

  Serial.begin(115200);
  Serial.println("Initializing...");

  pinMode(CONFIRM_BUTTON, INPUT_PULLUP);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  pinMode(YellowLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  digitalWrite(YellowLED, HIGH);
  digitalWrite(BlueLED, LOW);

  for (uint8_t i = 0; i < 16; i++) {
    digitalWrite(BlueLED, HIGH);
    pinMode(solenoids[i], OUTPUT);
    digitalWrite(solenoids[i], LOW);
    solenoidOnTimes[i] = 0;
    solenoidStates[i] = false;
    delay(50);
    digitalWrite(BlueLED, LOW);
    delay(50);
  }
  for (uint8_t i = 0; i < 16; i++) {
    digitalWrite(BlueLED, HIGH);
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
    delay(50);
    digitalWrite(BlueLED, LOW);
    delay(50);
  }

  Serial.println("Solenoids ready.");

  solenoidTimer.begin(checkSolenoids, 500);

  Serial.println("Timer running.");


  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(300);

  // SD
  if (!SD.begin(SD_CONFIG)) {
    Serial.println("SD Error.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SD Error.");
    while (1) {
      if (digitalRead(CONFIRM_BUTTON) == LOW) {
        resetTeensy();
      }
    }
  } else {
    Serial.println("SD Card OK.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SD Card OK.");
  }


  // MCP23017
  if (!mcp.begin_I2C()) {
    Serial.println("MCP Error.");
    while (1) {
      if (digitalRead(CONFIRM_BUTTON) == LOW) {
        resetTeensy();
      }
    }
  } else {
    Serial.println("MCP Initialized.");
  }

  pinMode(INTA_PIN, INPUT_PULLUP);
  pinMode(INTB_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(INTA_PIN), handleMCP, FALLING);
  attachInterrupt(digitalPinToInterrupt(INTB_PIN), handleMCP, FALLING);

  Serial.println("MCP Interrupts attached.");

  mcp.clearInterrupts();
  for (uint8_t i = 0; i < 16; i++) {
    mcp.disableInterruptPin(i);
  }

  Serial.println("MCP Interrupts disabled.");

  for (uint8_t i = 0; i < 16; i++) {
    mcp.pinMode(i, INPUT_PULLUP);
  }

  mcp.setupInterrupts(false, false, LOW);
  
  for (uint8_t i = 0; i < 16; i++) {
    mcp.setupInterruptPin(i, CHANGE);
  }

  Serial.println("MCP Interrupts enabled.");

  // MIDI
  SMF.begin(&SD);
  SMF.setMidiHandler(midiCallback);
  SMF.looping(false);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("XyloTap ready!");
  delay(500);

  Serial.println("Looping...");

  digitalWrite(BlueLED, HIGH);
}

void loop() {

  // Show a menu consisting of the list of songs from the SD card
  // The user can scroll through the list using the UP and DOWN buttons
  // The user can select a song using the CONFIRM button

  // If a song is selected, play the song
  // If the song is playing, the user can stop the song by clicking the CONFIRM button

  Serial.println("Test pattern.");
  testPattern();

  Serial.println("Menu loop.");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select a song:");
  lcd.setCursor(0, 1);
  // Load the songs from the SD card to the songList array
  FsFile dir = SD.open("/");
  int songCount = 0;
  while (true) {
    SdFile entry;
    if (!entry.openNext(&dir, O_RDONLY)) {
        break;
    }
    if (!entry) {
      break;
    }
    if (entry.isDirectory()) {
      continue;
    }
    char name[32];
    entry.getName(name, 32);
    songList[songCount] = String(name);
    songCount++;
    entry.close();
  }

  // Print the song list to the serial monitor
  for (int i = 0; i < songCount; i++) {
    Serial.println(songList[i]);
  }

  while (true) {
    if (digitalRead(UP_BUTTON) == LOW) {
      menuIndex--;
      if (menuIndex < 0) {
        menuIndex = songCount - 1;
      }
      refreshMenu = true;
    }
    if (digitalRead(DOWN_BUTTON) == LOW) {
      menuIndex++;
      if (menuIndex >= songCount) {
        menuIndex = 0;
      }
      refreshMenu = true;
    }
    if (digitalRead(CONFIRM_BUTTON) == LOW) {
      playSong(songList[menuIndex]);
      break;
    }
    if (refreshMenu) {
      lcd.setCursor(0, 1);
      // Clear the line before printing the song name
      lcd.print("                ");
      lcd.setCursor(0, 1);
      // Remove the .mid or .MID extension from the song name
      String songName = songList[menuIndex];
      songName.replace(".mid", "");
      songName.replace(".MID", "");
      lcd.print(songName);
      refreshMenu = false;
      Serial.println("Menu refreshed.");
      delay(300);
    }
  }


}









void playSong(String name) {
  SMF.setFilename(name.c_str());
    int err = SMF.load(name.c_str());
    if (err != 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Error loading file.");
      Serial.println("Error loading file.");
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Now playing: ");
      lcd.setCursor(0, 1);
      String songName = SMF.getFilename();
      songName.replace(".mid", "");
      songName.replace(".MID", "");
      lcd.print(songName);
      Serial.println("Now playing: " + songName);
    }
    // Wait for the button to be released
    delay(1000);
    while (digitalRead(CONFIRM_BUTTON) == LOW) {}

    attachInterrupt(digitalPinToInterrupt(CONFIRM_BUTTON), stopSong, FALLING);
    while (SMF.isEOF() == false && SMF.isPaused() == false) {
      // Play the MIDI file
      SMF.getNextEvent();
    }
    detachInterrupt(digitalPinToInterrupt(CONFIRM_BUTTON));
    Serial.println("Song ended.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Song ended.");
    refreshMenu = true;
    SMF.close();
    SMF.pause(false);
    SMF.looping(false);
    // Wait for the button to be released
    delay(1000);
    while (digitalRead(CONFIRM_BUTTON) == LOW) {}
}



void stopSong() {
  refreshMenu = true;
  SMF.pause(true);
  Serial.println("Interrupted.");
}







