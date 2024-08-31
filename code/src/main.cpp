

/*
#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>

#define BUTTON_PIN 13   // MCP23XXX pin used for interrupt

#define INT_PIN 2      // microcontroller pin attached to INTA/B



Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(115200);
  //while (!Serial);
  Serial.println("MCP23xxx Interrupt Test!");

  // uncomment appropriate mcp.begin
  if (!mcp.begin_I2C()) {
  //if (!mcp.begin_SPI(CS_PIN)) {
    Serial.println("Error.");
    while (1);
  }

  // configure MCU pin that will read INTA/B state
  pinMode(INT_PIN, INPUT);

  // OPTIONAL - call this to override defaults
  // mirror INTA/B so only one wire required
  // active drive so INTA/B will not be floating
  // INTA/B will be signaled with a LOW
  mcp.setupInterrupts(true, false, LOW);

  // configure button pin for input with pull up
  mcp.pinMode(BUTTON_PIN, INPUT_PULLUP);

  // enable interrupt on button_pin
  mcp.setupInterruptPin(BUTTON_PIN, LOW);

  Serial.println("Looping...");
}

void loop() {
  if (!digitalRead(INT_PIN)) {
    Serial.print("Interrupt detected on pin: ");
    Serial.println(mcp.getLastInterruptPin());
    Serial.print("Pin states at time of interrupt: 0b");
    Serial.println(mcp.getCapturedInterrupt(), 2);
    delay(250);  // debounce
    // NOTE: If using DEFVAL, INT clears only if interrupt
    // condition does not exist.
    // See Fig 1-7 in datasheet.
    mcp.clearInterrupts();  // clear
  }
}

*/




//
//    FILE: MCP23017_digitalRead.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MCP23017 library
//     URL: https://github.com/RobTillaart/MCP23017_RT


#include <Arduino.h>
#include <Wire.h>
#include "MCP23017.h"

#define INTA_PIN 2
#define INTB_PIN 3

MCP23017 mcp(0x20);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MCP23017_LIB_VERSION: ");
  Serial.println(MCP23017_LIB_VERSION);

  pinMode(INTA_PIN, INPUT);
  pinMode(INTB_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(INTA_PIN), []() {
    Serial.println("INTA");
    Serial.println(mcp.getInterruptFlagRegister(), BIN);
  }, FALLING);
  attachInterrupt(digitalPinToInterrupt(INTB_PIN), []() {
    Serial.println("INTB");
    Serial.println(mcp.getInterruptFlagRegister(), BIN);
  }, FALLING);

  Wire.begin();
  mcp.begin();

  mcp.mirrorInterrupts(false);

  // Set all pins as INPUT_PULLUP
  mcp.pinMode16(0xFFFF);

  // Enable interrupt on all pins
  mcp.enableInterrupt16(0xFFFF, FALLING);

  Serial.println(mcp.getInterruptFlagRegister(), BIN);

}


void loop()
{
}


//  -- END OF FILE --
