#include <Arduino.h>
#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>

#define SOLENOID_PIN 10

Adafruit_MCP23X17 mcp;


void setup() {
  Serial.begin(115200);
  pinMode(SOLENOID_PIN, OUTPUT);

   if (!mcp.begin_I2C()) {
    Serial.println("MCP23X17 not found");
    while (1);
  }

  // Set all mcp pins to input_pullup
  for (uint8_t i = 0; i < 16; i++) {
    mcp.pinMode(i, INPUT_PULLUP);
  }
}

void loop() {

  // Read all mcp pins
  for (uint8_t i = 0; i < 16; i++) {
    Serial.print("  Pin ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(mcp.digitalRead(i));
  }
Serial.println();
delay(100);
}

