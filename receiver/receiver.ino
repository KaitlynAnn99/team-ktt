#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

uint8_t defaultDeviceSequence[2] = {'A', 'A'};
uint8_t sequence[2];

int outputPin = 9;
void setup()
{
    pinMode(outputPin, OUTPUT);
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}


// this function check whether the buffer contains
// the default deveice sequence number
bool checkBuf(uint8_t * buf) {
    if (sizeof(buf) <= 2 * sizeof(uint8_t)) {
        return false;
    }
    return (buf[0] == defaultDeviceSequence[0] && buf[1] == defaultDeviceSequence);
}

int parseInt(uint8_t * buf) {
    int frequency = 0;
    if (checkBuf) {
        if (buf[2] <= '9' && buf[2] >= '0') {
            int index = 2;
            while(buf[index] != '#') {
                frequency = frequency * 10 + (buf[index] - '0');
                index++;
            }
        }
    }
    return frequency;
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {

    }
               
}
