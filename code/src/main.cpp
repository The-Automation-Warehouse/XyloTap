
#include <Arduino.h>
#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>

#define BUTTON_PIN 3   // MCP23XXX pin used for interrupt

#define INT_PIN 3      // microcontroller pin attached to INTA/B

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

  mcp.clearInterrupts();
  
  // configure MCU pin that will read INTA/B state
  pinMode(INT_PIN, INPUT_PULLUP);

  mcp.setupInterrupts(true, true, LOW);

  // configure button pin for input with pull up
  mcp.pinMode(BUTTON_PIN, INPUT_PULLUP);

  // enable interrupt on button_pin
  mcp.setupInterruptPin(BUTTON_PIN, LOW);
  mcp.clearInterrupts();

  Serial.println("Looping...");
}

void loop() {
  if (!digitalRead(INT_PIN)) {
    Serial.print("Interrupt detected on pin: ");
    Serial.println(mcp.getLastInterruptPin());
    Serial.print("Pin states at time of interrupt: 0b");
    Serial.println(mcp.getCapturedInterrupt(), 2);

  }
}