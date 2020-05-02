#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

uint8_t defaultDeviceSequence[2] = {'A', 'A'};
uint8_t sequence[2];
bool inSleep = false;

int outputPin = 9;
void setup()
{
    pinMode(outputPin, OUTPUT);
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}


void powerOff();
void powerOn();

int receiveMessage(char * message) {
    char seqFirst = message[0];
    char seqSecond = message[1];

    // sequence matches the receiver sequence 
    if (checkBuf(message)) {
        if (checkInt(message)) {
            return parseInt(message);
        } else if (checkOnOff(message)) {
            return 0;
        }
        
    } else {
        return -1;
    }
}


// this function check whether the buffer contains
// the default deveice sequence number
bool checkBuf(uint8_t * buf) {
    if (sizeof(buf) <= 2 * sizeof(uint8_t)) {
        return false;
    }
    return (buf[0] == defaultDeviceSequence[0] && buf[1] == defaultDeviceSequence[1]);
}

bool checkOnOff(uint8_t * buf) {
    return buf[2] == '*';
}

bool checkInt(uint8_t * buf) {
    if (buf[2] <= '9' && buf[2] >= '0') {
        return true;
    }
    return false;
}

int parseInt(uint8_t * buf) {
    int res = 0;
    int index = 2;
    while(index < 12 && buf[index] != '#') {
        res = res * 10 + (buf[index] - '0');
        index++;
    }
    return res;
}

// void loop()
// {
//     uint8_t buf[12];
//     uint8_t buflen = sizeof(buf);

//     if (driver.recv(buf, &buflen)) // Non-blocking
//     {
//         if (checkBuf(buf)) {
//             if (checkInt(buf)) {
//                 frequency = parseInt(buf);
//             }
//             else if (checkOnOff(buf)) {
//                 inSleep = !inSleep;
//             }
//         }
//     }
               
// }
