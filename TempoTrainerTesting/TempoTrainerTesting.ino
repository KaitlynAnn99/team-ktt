#include <RadioHead.h>
#include <RHCRC.h>
#include <RHDatagram.h>
#include <RHEncryptedDriver.h>
#include <RHGenericDriver.h>
#include <RHGenericSPI.h>
#include <RHHardwareSPI.h>
#include <RHMesh.h>
#include <RHNRFSPIDriver.h>
#include <RHReliableDatagram.h>
#include <RHRouter.h>
#include <RHSoftwareSPI.h>
#include <RHSPIDriver.h>
#include <RHTcpProtocol.h>
#include <RH_ASK.h>
#include <RH_CC110.h>
#include <RH_E32.h>
#include <RH_MRF89.h>
#include <RH_NRF24.h>
#include <RH_NRF51.h>
#include <RH_NRF905.h>
#include <RH_RF22.h>
#include <RH_RF24.h>
#include <RH_RF69.h>
#include <RH_RF95.h>
#include <RH_Serial.h>
#include <RH_TCP.h>

/*  KTT - Keep the Tempo
 *  DCK - Deaf Kids Code
 *  Kaitlyn, Midori, Shawn
 *  
 *  **TEMPO TRAINER 2.0**
 *  
 *  Last Updated on: 46 April 2019
 * // ________________________________________________________________*/


 
#include "Timer.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include "LowPower.h"
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

Timer t;
int outputPin = 9;
int up = 6;
int down = 5;
long periodTime; 
int offPeriod;
int onPeriod;
int x;
int y;
double frequency;
bool inSleep;
bool wait;


void turnOff(void *point)
{
  /* This code turns the arduino OFF for the period time */
  digitalWrite(outputPin, LOW);
  offPeriod = t.after(long(periodTime)-150, turnOn, NULL);  
}

void turnOn(void *point)
{
  /* This code turns the arduino ON for 150 milliseconds to blink */
  digitalWrite(outputPin, HIGH);
  onPeriod = t.after(150, turnOff, NULL);  
}

void setup()
{
  /* All pins need to be set to Inputs, outputs, or input_pullups (interrupts) */
  pinMode(outputPin, OUTPUT);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT_PULLUP);
  // initialization
  periodTime = 1000;
  x = 0;
  y = 30;
  
  //This timer library is documented online as Timer.h. Basically it takes a call back function and will execute it after the set amount of time
  offPeriod = t.after(long(periodTime)-150, turnOn, NULL); 
  Serial.begin(9600);
     
  inSleep = false;
  wait = false;
}
 
void loop()
{

  t.update();
  frequency = 60000 * (1 / (double) periodTime);
  }
  
}
