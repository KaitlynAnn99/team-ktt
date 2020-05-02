#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
#define MESSAGE_MAX 24

int tempo;
char Channel[2];


// display the current tempo on screen
void screenDisplay();

// Checks for what has been pressed
char keypadCheck()

// conceptual for writing the main loop
int main() {
    char previous = '';
    int counter = 0;
    char buf[MESSAGE_MAX];
    while (true) {
        // TODO after a few iteration, display the tempo on screen
        // TODO Another feature to consider is:
        // displaying the running buffer on screen if it is meaningful

        char current = keypadCheck();
        if (current != previous) {
            buf[counter] = current;
            counter++;
            previous = current;
        }
        if (current == '#') {
            sendMessage(buf);
            counter = 0;
            previous = '';
        }

    }
}

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void sendMessage(char * buf) {
  char message[MESSAGE_MAX];
  sprintf(message, "%s%s#", Channel, buf);
  SPI.transfer(message, strlen(message) + 1);
}

void loop()
{
    const char *msg = "Hello World!";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
}
