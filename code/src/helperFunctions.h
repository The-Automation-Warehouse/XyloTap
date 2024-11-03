#include <Arduino.h>
#include <Adafruit_MCP23X08.h>
#include <Adafruit_MCP23X17.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SDFat.h>
#include <IntervalTimer.h>

extern const uint8_t solenoids[16];
extern const uint8_t leds[16];
extern uint32_t solenoidOnTimes[16];
extern bool solenoidStates[16];
extern unsigned long solenoidOnDurations[16];

extern Adafruit_MCP23X17 mcp;

void handleMCP();
void checkSolenoids();
void strikeKey(int key);
void midiCallback(midi_event *pev);
int midiNoteToKey(int midiNote);
void testPattern();


// Strike keys for a certain amount of time
void strikeKey(int key) {
  if (key < 0 || key > 15) {
    return;
  }
  // Direct port manipulation for faster I/O
  *portSetRegister(digitalPinToPort(solenoids[key])) = digitalPinToBitMask(solenoids[key]);
  *portClearRegister(digitalPinToPort(leds[key])) = digitalPinToBitMask(leds[key]);
  solenoidOnTimes[key] = millis();
  solenoidStates[key] = true;
}

// Check solenoids and turn off if necessary
void checkSolenoids() {
  unsigned long currentMillis = millis();
  for (uint8_t i = 0; i < 16; i++) {
    if (solenoidStates[i] && (currentMillis - solenoidOnTimes[i] > solenoidOnDurations[i])) {
      // Inline turnOffKey for efficiency
      *portClearRegister(digitalPinToPort(solenoids[i])) = digitalPinToBitMask(solenoids[i]);
      *portSetRegister(digitalPinToPort(leds[i])) = digitalPinToBitMask(leds[i]);
      solenoidStates[i] = false;
    }
  }
}










void midiCallback(midi_event *pev)
// Extracts the note from the MIDI event and strikes the corresponding key
{
  // Check if the entry is a note on event
  if (pev->data[0] != 0x90) {
    return;
  }
  /*
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Note: ");
  lcd.print(pev->data[1]);
  lcd.setCursor(0, 1);
  lcd.print("Key: ");
  lcd.print(note);
  */
 /*
  Serial.println();
  Serial.print("Note: " + String(pev->data[1]));
  Serial.print("  Octave: " + String(pev->data[1] / 12));
  Serial.print("  Key index: " + String(midiNoteToKey(pev->data[1])));
  */

  strikeKey(midiNoteToKey(pev->data[1]));
}


/*

int midiNoteToKey(int midiNote) {
  // Define the mapping from MIDI notes to key notes
  // The keys are CDEFGAHCDEFGAHCD
  // The first key on the xylophone is C4 (middle C) - MIDI note 60
  // The last key is D6 - MIDI note 86

  // Anythign below C4 will be played on the first octave
  // Anything above C6, C#6/Db6, D6 will be played on the last two keys
  // Everything else will be played on the middle octave

  uint8_t key = midiNote % 12;

  // Last two keys (octave C6)
  switch (midiNote)
  {
  case 84:
    return 14;
    break;
  case 85:
    return 14;
    break;
  case 86:
    return 15;
    break;
  default:
    break;
  }

  switch (key)
  {
  case 0:
    key = 0;
    break;
  case 1:
    key = 0;
    break;
  case 2:
    key = 1;
    break;
  case 3:
    key = 1;
    break;
  case 4:
    key = 2;
    break;
  case 5:
    key = 3;
    break;
  case 6:
    key = 3;
    break;
  case 7:
    key = 4;
    break;
  case 8:
    key = 4;
    break;
  case 9: 
    key = 5;
    break;
  case 10:
    key = 5;
    break;
  case 11:
    key = 6;
    break;
  default:
    key = -1;
  }

  // All octaves below and including C4
  if (midiNote < 72) {
    return key;
  }

  // All octaves above and including C6 (except the last two keys)
  if (midiNote > 82) {
    return key + 7;
  }

  return -1;

}


*/



int midiNoteToKey(int midiNote) {
  // Define the mapping from MIDI notes to key notes
  // The keys are CDEFGAHCDEFGAHCD
  // The first key on the xylophone is C4 (middle C) - MIDI note 60
  // The last key is D6 - MIDI note 86

  switch (midiNote)
  {
  case 60:
    return 0;
    break;
  case 61:
    return 0;
    break;
  case 62:
    return 1;
    break;
  case 63:
    return 1;
    break;
  case 64:
    return 2;
    break;
  case 65:
    return 3;
    break;
  case 66:
    return 3;
    break;
  case 67:
    return 4;
    break;
  case 68:
    return 4;
    break;
  case 69:
    return 5;
    break;
  case 70:
    return 5;
    break;
  case 71:
    return 6;
    break;
  case 72:
    return 7;
    break;
  case 73:
    return 7;
    break;
  case 74:
    return 8;
    break;
  case 75:
    return 8;
    break;
  case 76:
    return 9;
    break;
  case 77:
    return 10;
    break;
  case 78:
    return 10;
    break;
  case 79:
    return 11;
    break;
  case 80:
    return 11;
    break;
  case 81:
    return 12;
    break;
  case 82:
    return 13;
    break;
  case 83:
    return 13;
    break;
  case 84:
    return 14;
    break;
  case 85:
    return 14;
    break;
  case 86:
    return 15;
    break;
  default:
    break;
  }

  return -1;

}







void testPattern() {
  // Blink solenoids and leds
  for (uint8_t i = 0; i < 16; i++) {
    strikeKey(i);
    delay(300);
  }
}












void handleMCP() {

  // Get the last interrupt pin
  int pin = mcp.getLastInterruptPin();
  if (pin == 255) {
    return;
  }
  //Serial.println("Interrupt on pin " + String(pin));

  uint16_t pinValues = (mcp.getCapturedInterrupt());

  // Button 12 has problems
  // If the pin is 6 or 8 and there are more than two 0 bits in the entire value, treat it as a button 12 press
  if (pin == 6 || pin == 8) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < 16; i++) {
      if (!(pinValues & (1 << i))) {
        count++;
      }
    }
    if (count > 2) {
      strikeKey(12);
      mcp.clearInterrupts();
      return;
    }
  }

  // If the values aren only 8 bits, pad them with 1s
  if (pinValues < 256) {
    pinValues |= 0xFF00;
  }
  // If the interrupt was on the sencod port, set the first 8 bits to 1
  if (pin > 7) {
    pinValues |= 0x00FF;
  }

  //Serial.println("Pin values: " + String(pinValues, BIN));
  
  // Strike each key with a 0 value
  for (uint8_t i = 0; i < 16; i++) {
    if (!(pinValues & (1 << i))) { // Invert the condition to check for 0 value
      strikeKey(i);
    }
  }

  // Clear interrupts
  mcp.clearInterrupts();
}