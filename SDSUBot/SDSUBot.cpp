#ifndef SDSUBOT_CPP
#define SDSUBOT_CPP

#include "SDSUBot.h"

SDSUBot::SDSUBot(){
	
}


/***********************************************************
* MOTOR FUNCTION WRAPPERS
***********************************************************/
void SDSUBot::initMotion(){
	BotMotion.init();
}

void SDSUBot::sleep(){
	BotMotion.sleep();
}

void SDSUBot::wake(){
	BotMotion.wake();
}

void SDSUBot::rightMotorForward(){
	BotMotion.rightMotorForward();
}

void SDSUBot::rightMotorBackward(){
	BotMotion.rightMotorBackward();
}

void SDSUBot::leftMotorForward(){
	BotMotion.leftMotorForward();
}

void SDSUBot::leftMotorBackward(){
	BotMotion.leftMotorBackward();
}

void SDSUBot::leftMotorSpeed(unsigned char speed){
	BotMotion.leftMotorSpeed(speed);
}

void SDSUBot::rightMotorSpeed(unsigned char speed){
	BotMotion.rightMotorSpeed(speed);
}



#endif