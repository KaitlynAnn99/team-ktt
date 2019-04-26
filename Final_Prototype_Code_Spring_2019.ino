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
int outputPin = 4;
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

  //Screen code -- also documented online
  u8g2.begin();
  u8g2.setFont(u8g2_font_logisoso30_tr); // choose a suitable font
  u8g2.clearBuffer();  
  u8g2.setCursor(x,y);
  u8g2.print(60000 * (1 / (double) periodTime), 1); 
  u8g2.drawStr(65, y ,"s/m");
  u8g2.sendBuffer();
     
  inSleep = false;
  wait = false;
}
void screen(){
  int tempX = 65;
  
  u8g2.clearBuffer();  
  u8g2.setCursor(x,y);
  u8g2.print((int)(60000 * (1 / (double) periodTime)), 1);

  u8g2.setCursor(tempX,y);
  u8g2.drawStr(tempX, y ,"s/m");
  u8g2.sendBuffer();
}
 
void loop()
{
  //Code for the arduino in sleep
  if(inSleep == true)
  {
     if(digitalRead(up) == HIGH)
     {
       inSleep = false;
       wait = true;
       u8g2.setPowerSave(0);
       offPeriod = t.after(long(periodTime)-150, turnOn, NULL);
     }
     else {
       LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
     }
  }
  //code the arduino out of sleep
  else{
   
  delay(50);
  if(wait == true)
  {
    if(digitalRead(up) == LOW)
    {
      wait = false; //ensures that a long hold won't cause the tempo trainer to increase indefinitely
    } 
  }
  else if(digitalRead(up) == HIGH  && digitalRead(down) == HIGH)
  { 
    //Put arduino in sleep mode
    inSleep = true;
    u8g2.setPowerSave(1);
    digitalWrite(outputPin, LOW);
    t.stop(onPeriod);
    t.stop(offPeriod);
    delay(1000);
  }
  else if (digitalRead(up)== HIGH && periodTime < 2000){
      //Increase our period time
      periodTime += 20;
      digitalWrite(outputPin, LOW);
      delay(30);
      screen();
  }
  else if (digitalRead(down) == HIGH && periodTime >= 300){
      //decrease our period time
      periodTime -= 20;
      digitalWrite(outputPin, LOW);
      delay(30);
      screen();       
  }
  t.update();
  frequency = 60000 * (1 / (double) periodTime);
  }
  
}
