#ifndef BTN_TO_MORSE_H
#define BTN_TO_MOTSE_H
String toCompare[9] = 
{
  ".-",     // A
  "-...",    // B  
  "-.-.",   // C
  "-..",    // D
  ".",      // E
  "..-.",   // F
  "--.",    // G
  "....",   // H
  "..",     // I
}; 

String morseString = "";

bool flag=false;
byte action=0;

static const byte buttonPin = 34;
bool buttonStatePrevious = LOW;

unsigned long pointDuration = 1000;
unsigned long dashDuration = 3000;
unsigned long pressedTime;
unsigned long lastExecution=0;

byte buttonStateLongPress = 0;

const byte intervalButton = 50;

unsigned long previousButtonMillis;
unsigned long buttonPressDuration;

unsigned long currentMillis;

void initButton()
{
  pinMode(buttonPin, INPUT);
}

void readMorseInput(bool state) 
{
  currentMillis = millis();
  
  if(currentMillis - previousButtonMillis > intervalButton) 
  { 
    if (state && !buttonStatePrevious && buttonStateLongPress==0) {
      pressedTime = currentMillis;
      buttonStatePrevious = HIGH;
    }

    buttonPressDuration = currentMillis - pressedTime;

    if (state && buttonStateLongPress<1 && buttonPressDuration >= pointDuration)
    {
      buttonStateLongPress = 1;
      Serial.println("Point");
      lastExecution = currentMillis;
    }

    if (state && buttonStateLongPress<2 && buttonPressDuration >= dashDuration) 
    {
      buttonStateLongPress = 2;
      Serial.println("Dash");
      lastExecution = currentMillis;
    }
      
    if (!state && buttonStatePrevious) 
    {
      switch(buttonStateLongPress)
      {
        case 1: morseString += "."; break;
        case 2: morseString += "-"; break;
        default: morseString += ""; break;
      }


      buttonStatePrevious = LOW;
      buttonStateLongPress = 0;

      //Serial.println("Button released");
      Serial.println("Morse:" + morseString);
    }
    
    if(currentMillis - lastExecution > 10000 && morseString != "")
    {
      Serial.println("Processing input");
      for(byte i = 0; i<9; i++)
      {
        if(morseString == toCompare[i])
        {
          flag = true;
          action = i;
        }
      }
      //Serial.println("Clearing string");
      morseString = "";
    }
    previousButtonMillis = currentMillis;
  }
}
#endif