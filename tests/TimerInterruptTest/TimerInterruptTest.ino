#include "SDSUBot.h"

SDSUBot bot;

void setup(){

  bot.initMotion();
  //pinMode(13, OUTPUT);
}

void loop(){

  //digitalWrite(13,!digitalRead(13));
  //delay(1000);
  
  bot.leftMotorSpeed(100);
  //bot.rightMotorSpeed(200);

  delay(5000);

  bot.leftMotorSpeed(0);
  //bot.rightMotorSpeed(0);

  delay(5000);
  //bot.rightMotorBackward();
  //bot.rightMotorSpeed(150);
  bot.leftMotorSpeed(225);

  delay(5000);

  
  
}

