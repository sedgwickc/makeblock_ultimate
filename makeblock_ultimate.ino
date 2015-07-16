/*************************************************************************
* File Name          : TestSlaveBluetoothBySoftSerial.ino
* Author             : Steve
* Updated            : Evan
* Version            : V1.0.1
* Date               : 5/17/2013
* Description        : Example for Makeblock Electronic modules of Me -  
                       Bluetooth. The module can only be connected to the 
                       port 3, 4, 5, 6 of Me - Base Shield.
* License            : CC-BY-SA 3.0
* Copyright (C) 2013 Maker Works Technology Co., Ltd. All right reserved.
* http://www.makeblock.cc/
**************************************************************************/
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define DELAY 40 // needed to smooth movements of motors

/*
Blue module can only be connected to port 3, 4, 5, 6 of base shield.
*/
MeBluetooth bluetooth(PORT_5);
MeDCMotor motorGripper(PORT_2);
MeDCMotor motorArm(PORT_1);
MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);
MeRGBLed led(PORT_6);

uint8_t motorSpeed = 125;
uint8_t gripSpeed = 175;
uint8_t armSpeed = 125;
int ledCount = 15;
float j,f,k;

void setup()
{
    Serial.begin(115200);
    bluetooth.begin(115200);
    led.setNumber(ledCount);
}

void loop()
{
    char inDat;
    char outDat;
    if(bluetooth.available())
    {
        inDat = bluetooth.read();
        switch( inDat ) {
          case 'F':
            motorLeft.run(motorSpeed); // value: between -255 and 255.
            motorRight.run(motorSpeed); // value: between -255 and 255.
            delay(DELAY);
            break;
          
          case 'B':
            motorLeft.run(-motorSpeed); // value: between -255 and 255.
            motorRight.run(-motorSpeed); // value: between -255 and 255.
            delay(DELAY);
            break;
          
          case 'R':
            motorLeft.run(-motorSpeed); // value: between -255 and 255.
            motorRight.run(motorSpeed); // value: between -255 and 255.
            delay(DELAY);
            break;
          
          case 'L':
            motorLeft.run(motorSpeed); // value: between -255 and 255.
            motorRight.run(-motorSpeed); // value: between -255 and 255.
            delay(DELAY);
            break;
            
          case 'S':
            motorLeft.stop();
            motorRight.stop();
            delay(DELAY);
            break;
            
          case 'O':
            motorGripper.run(gripSpeed);
            delay(DELAY);
            break;
            
          case 'C':
            motorGripper.run(-gripSpeed);
            delay(DELAY);
            break;
            
          case 'U':
            motorArm.run(armSpeed);
            delay(DELAY);
            break;
            
          case 'D':
            motorArm.run(-armSpeed);
            delay(DELAY);
            break;
            
          default:
            char undef[3] = {'U', 'N', 'D' };
            for( int i = 0; i <=3; i++ )
            {
              bluetooth.write(undef[i]);
            }
            break;
        }
    }
    else
    {
      motorArm.stop();
      motorGripper.stop();
      motorLeft.stop();
      motorRight.stop();
    }
    
    color_loop();

}

void color_loop()
{  
  for (uint8_t t = 0; t < ledCount; t++)
  {
    uint8_t red =   64*(1+sin(t/2.0 + j/4.0       ));
    uint8_t green = 64*(1+sin(t/1.0 + f/9.0  + 2.1));
    uint8_t blue =  64*(1+sin(t/3.0 + k/14.0 + 4.2));
    led.setColorAt(t, red,green,blue);
  }
  led.show();
  j+=random(1,6)/6.0;
  f+=random(1,6)/6.0;
  k+=random(1,6)/6.0;
}

