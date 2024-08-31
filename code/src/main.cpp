
#include <Arduino.h>
#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>


#define INTA_PIN 2
#define INTB_PIN 3


Adafruit_MCP23X17 mcp;

void handleMCP();

void setup() {
  Serial.begin(115200);


  if (!mcp.begin_I2C()) {
    Serial.println("Error.");
    while (1);
  }

  pinMode(INTA_PIN, INPUT);
  pinMode(INTB_PIN, INPUT);

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
}

void loop() {
}

void handleMCP() {
  int pin = mcp.getLastInterruptPin();
  if (pin == 255) {
    return;
  }
  Serial.print("Interrupt detected on pin: ");
  Serial.println(mcp.getLastInterruptPin());
  mcp.clearInterrupts();  // clear


}