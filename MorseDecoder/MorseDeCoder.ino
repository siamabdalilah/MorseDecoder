#include"MorseCodes.h"

void setup() {
  Serial.begin(9600);
}


void convertIncomingMorseCodeToChars() {
}

void updateLED() {
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingMorseCodeToChars()" and "updateLED()"
  updateLED();
  convertIncomingMorseCodeToChars();

  // Extra credit: Merge in your convertIncomingCharsToMorseCode() to have a 
  // complete encoder/decoder
}
