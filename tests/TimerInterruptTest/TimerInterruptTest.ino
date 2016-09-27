#include "SDSUBot.h"

SDSUBot bot;

void setup(){

  bot.initMotion();

}

void loop(){

  bot.rightMotorForward();
  bot.leftMotorSpeed(255);
  bot.rightMotorSpeed(255);

  delay(5000);

  bot.leftMotorSpeed(0);
  bot.rightMotorSpeed(0);

  delay(5000);
  bot.rightMotorBackward();
  bot.rightMotorSpeed(150);
  bot.leftMotorSpeed(225);

  delay(5000);

}

