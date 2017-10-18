/* More Morse Mayhem
 *  
 *  CSE 132 - Assignment 6
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Siam Abd Al-Ilah
 *  WUSTL Key: siam.abdal-ilah
 *  
 *  and if two are partnered together
 *  
 *  Name: 
 *  WUSTL Key: 
 */
#include"MorseCodes.h"

#define UNIT 1000
#define debounceTime 50
#define pin 13
#define buttonPin 8

// for displaying morse
#define UNIT2 500 
#define morseLed 11

unsigned long ledTime = 0;
unsigned long pressTime = 0; 

bool button = 0;
bool lastButton = 1; //initiated at 1 because of INPUT_PULUP
bool ledState = 0;

//booleans to control printing of space and letters
bool spaceFlag = 0;
bool charFlag = 0;

//buffer to hold dots and dashes
char buff[7];
int bufferCount = 0;

//The following are for convertIncomingCharsToMorseCode()
unsigned long startTime = 0;
unsigned long pauseTime = 0;
unsigned long breakTime = 0;

String queue = "";
int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(morseLed, OUTPUT);
  pressTime = millis();
}


void convertIncomingMorseCodeToChars() {
  button = digitalRead(buttonPin);
  
  //when button pressed
  if (button == 0 && lastButton == 1)
  {
    unsigned long temp = millis() - pressTime;
    if (temp < .66 * UNIT && temp > debounceTime)
      Serial.print("#Too short of a gap between dot/dash!#");
    pressTime = millis();
    lastButton = 0;
  }

  //when button not pressed
  else if (button == 1 && lastButton == 1)
  {
    unsigned long temp = millis() - pressTime;

    if (temp > 7 * UNIT && spaceFlag == 0) //put a space
    {
      Serial.print("#Space#");
      Serial.print(' ');
      spaceFlag = 1;
    }

    else if (millis() - pressTime > 3 * UNIT && charFlag == 0) //end the current letter
    {
      buff[bufferCount] = '\0';
      bufferCount = 0;
      if (buff[0] != '\0')
      {
        char code = morseDecode(buff);
        if (code == 0)
          Serial.print("#Not a valid Morse Code!#");
        else
        {
          Serial.print("#Letter:#");
          Serial.print(code);
        }
      }
      charFlag = 1;
    }
  }

  //button released
  else if (button == 1 && lastButton == 0)
  {
    unsigned long temp = millis() - pressTime;
    if (temp > debounceTime) //bounceCheck
    {
      //reset boolean flags
      spaceFlag = 0;
      charFlag = 0;
      
      if (temp < .66 * UNIT)
        Serial.print("#Too short for a dot! Ignored!#");
        
      else if (temp < 1.33 * UNIT)
      {
        buff[bufferCount] = '.';
        bufferCount++;
        if(bufferCount > 7)
        {
          Serial.print("#Code too long to be valid! Dropping all!#");
          bufferCount = 0;
        }
        else
          Serial.print("#.#"); 
      }
      
      else if (temp < .66 * 3 * UNIT)
        Serial.print("#Too long for a dot, but too short for a dash! Ignored!#");
        
      else if (temp < 1.33 * 3 * UNIT)
      {
        buff[bufferCount] = '-';
        bufferCount++;
        if(bufferCount > 7)
        {
          Serial.print("#Code too long to be valid! Dropping all!#");
          bufferCount = 0;
        }
        else
          Serial.print("#-#");
      }

      else
        Serial.print("#Too long for a dash! Ignored!#");
        
      pressTime = millis();
    }
    lastButton = button;
  }
}

void updateLED() {
  if (millis() - ledTime > UNIT/2)
  {
    ledState = !ledState;
    digitalWrite(pin, ledState);
    ledTime = millis();
  }
}


//Whatever code follows till void loop() is for convertIncomingCharsToMorseCode()
char toUpper(char c) {
  // TODO
  if (c >= 'a' && c <= 'z')
    c = c - (1 << 5);

  return c;
}

void convertIncomingCharsToMorseCode() {
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    //Serial.print(c);
    char* s = morseEncode( c);
    //Serial.println(s);
    if (s[0] != ' ')
      queue = queue + s + 'p'; //introducing p to mark end of a letter
    else 
      queue = queue + s;
  }

  if (millis() - startTime > pauseTime + breakTime)
  {
      if (queue[i] == '\0')
      {
        digitalWrite(morseLed, LOW);
      }

      else if (queue[i] == '.')
      {
        digitalWrite(morseLed, HIGH);
        pauseTime = UNIT2;
        breakTime = UNIT2;
        startTime = millis();
        i++;
      }

      else if (queue[i] == '-')
      {
        digitalWrite(morseLed, HIGH);
        pauseTime = 3 * UNIT2;
        breakTime = UNIT2;
        startTime = millis();
        i++;
      }

      else if (queue[i] == ' ')
      {
        pauseTime = 3 * UNIT2;
        breakTime = 0;
        startTime = millis();
        i++;
      }

      else if (queue[i] == 'p')
      {
        pauseTime = 3 * UNIT2;
        breakTime = 0;
        startTime = millis();
        i++;
      }
  }

  else if (millis() - startTime > pauseTime)
  {
    digitalWrite(morseLed, LOW);
  }
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingMorseCodeToChars()" and "updateLED()"
  updateLED();
  convertIncomingMorseCodeToChars();
  //convertIncomingCharsToMorseCode();

  // Extra credit: Merge in your convertIncomingCharsToMorseCode() to have a 
  // complete encoder/decoder
}
