#include <Arduino.h>

#define SOLENOID_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(SOLENOID_PIN, OUTPUT);
}

void loop() {
  Serial.println("Solenoid ON");
  digitalWrite(SOLENOID_PIN, HIGH);
  delay(1000);
  Serial.println("Solenoid OFF");
  digitalWrite(SOLENOID_PIN, LOW);
  delay(1000);
}

