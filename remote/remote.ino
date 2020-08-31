#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <Keypad.h>

RH_ASK driver;
#define MESSAGE_MAX 24

int tempo;
char Channel[3] = "AA"; //TODO: Allow users to change this

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2}; 
byte colPins[COLS] = {9, 8, 7, 6}; //IF NUMPAD DOESN'T WORK TRY SWITCHING THESE

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


// display the current tempo on screen
void screenDisplay(){
  return;
}

// Checks for what has been pressed
char keypadCheck() {
  return;
}
char previous = 0;
char buf[MESSAGE_MAX];
int counter = 0;
// conceptual for writing the main loop
void loop() {
        // TODO after a few iteration, display the tempo on screen
        // TODO Another feature to consider is:
        // displaying the running buffer on screen if it is meaningful
    char customKey = customKeypad.getKey();
     if (customKey) {
        buf[counter] = customKey;
         counter++;
     }
     if (customKey == '#') {
         sendMessage(buf);
         counter = 0;
     }
}

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

bool validateInput(char *inputString) {
    if (strlen(inputString) < 2) {
      return false;
    }
  
    bool letter = true;
    if (inputString[0] == '*') {
      if (strlen(inputString) == 2 && inputString[strlen(inputString) - 1] == '#') {
        return true;
      } else {
        return false;
      }
    } else if (inputString[0] <= '9' && inputString[0] >= '0') {
      letter = false;
    }
  
    if (letter) {
      for (int i = 1; i < strlen(inputString); i++) {
        if (inputString[i] < 'A' || inputString[i] > 'Z') {
          return false;
        }
      }
    } else {
      int tempo = 0;
      for (int i = 0; i < strlen(inputString) - 1; i++) {
        if (inputString[i] <= '9' && inputString[i] >= '0') {
          tempo = tempo * 10 + (inputString[i] - 48);
        } else {
          return false;
        }
      }
      Serial.println(tempo);
    }

    return true;
  }

void sendMessage(char *buf)
{

   // Due to availability of materials, this code is NOT TESTED FOR ACTUAL SENDING (didn't have enough arduinos)
    char msg[MESSAGE_MAX];

    sprintf(msg, "%s%s", Channel, buf);
    Serial.println(validateInput(buf));
    Serial.println(msg);
    /*
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    */
}
