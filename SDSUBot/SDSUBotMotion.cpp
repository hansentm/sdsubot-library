#ifndef SDSUBOT_MOTION_CPP
#define SDSUBOT_MOTION_CPP

#include "SDSUBotMotion.h"

Motion BotMotion;

Motion::Motion(){
	
	//preinit values
	this->_Lcount = 0;
	this->_Lspeed = 0;
	this->_Rcount = 0;
	this->_Rspeed = 0;
	this->_sleeping = true;
	
}

void Motion::init(){
	
	//set the motor controls to outputs
	pinMode(LEFT_MOTOR_DIRECTION, OUTPUT);  //DirL
	pinMode(LEFT_MOTOR_STEP, OUTPUT); //StepL
	pinMode(MOTOR_SLEEP, OUTPUT); //Sleep
	pinMode(RIGHT_MOTOR_STEP, OUTPUT); //StepR
	pinMode(RIGHT_MOTOR_DIRECTION, OUTPUT); //DirR

	//set the direction to forward
	this->leftMotorForward();
	this->rightMotorForward();

	//initially set driver output to low
	digitalWrite(LEFT_MOTOR_STEP, LOW);
	digitalWrite(RIGHT_MOTOR_STEP, LOW);
	
	//set up a timer and interrupts
	this->_timerInit();

	//wake up the motor drivers
	this->wake();
	
}

void Motion::sleep(){
	
	//sleep the motor drivers to conserve battery energy
	digitalWrite(MOTOR_SLEEP, LOW);
	this->_timerStop();
	this->_sleeping = true;
	
}

void Motion::wake(){
	
	//wake up the motor drivers
	digitalWrite(MOTOR_SLEEP, HIGH);
	this->_timerRestart();
	this->_sleeping = false;
	
}

void Motion::rightMotorForward(){
	
	digitalWrite(RIGHT_MOTOR_DIRECTION, RIGHT_FORWARD);
	
}

void Motion::rightMotorBackward(){
	
	digitalWrite(RIGHT_MOTOR_DIRECTION, RIGHT_BACKWARD);
	
}

void Motion::leftMotorForward(){
	
	digitalWrite(LEFT_MOTOR_DIRECTION, LEFT_FORWARD);
	
}

void Motion::leftMotorBackward(){
	
	digitalWrite(RIGHT_MOTOR_DIRECTION, LEFT_BACKWARD);
	
}

void Motion::leftMotorSpeed(unsigned char speed){
	
	this->_Lcount = 0; //reset count
	
	//map speed to a 50microsecond count value. 1 = 14.7ms, 255 = 2ms period
	if(speed == 0){
		this->_Lspeed = 0;
	}else{
		this->_Lspeed = MAX_SPEED_CONSTANT - speed; 
	}
	
	this->_stop_start_Check();
}

void Motion::rightMotorSpeed(unsigned char speed){
	
	this->_Rcount = 0; //reset count
	
	//map speed to a 50microsecond count value. 1 = 14.7ms, 255 = 2ms period
	if(speed == 0){
		this->_Rspeed = 0;
	}else{
		this->_Rspeed = MAX_SPEED_CONSTANT - speed; 
	}
	
	this->_stop_start_Check();
}

void Motion::_stop_start_Check(){
	/*
	* Automatically sleeps the robot drivers if not moving to conserve power
	*/
	
	if(this->_sleeping){
		
		if(this->_Lspeed || this->_Rspeed)
			this->wake();
		
	}else{
		
		if((this->_Lspeed == 0) && (this->_Rspeed == 0)){
			delay(50); //delay so the robot can stop and not roll
			this->sleep();
		}
		
	}
	
}


/********************************************************************
* Private Timer Functions
********************************************************************/

//define speed constants
#define _TIMER_CYCLES 0x0320 // = 0d800 = 50 microseconds per interrupt
#define _TCCR1A_VAL 0b00000010 //set WGM11 = 1 (WGM13:10 = 0b1110 -> Fast PWM Mode 14 -> TOP=ICR1, interrupt at TOP))
#define _TCCR1B_VAL	0b00011001 //clock div by 1 (16MHz); WGM13:12 = 0b11 (Mode 14 with TCCR1A)

ISR(TIMER1_OVF_vect){
	BotMotion._timerInterrupt();
}

//timer1 interrupt service routine
void Motion::_timerInterrupt(){ 
	
	//increment and toggle pins
	if(this->_Lspeed > 0){
		this->_Lcount++;
		if(this->_Lcount == this->_Lspeed){
			this->_Lcount = 0;
			digitalWrite(LEFT_MOTOR_STEP,!digitalRead(LEFT_MOTOR_STEP));
		}
	}

	//increment and toggle pins
	if(this->_Rspeed > 0){
		this->_Rcount++;
		if(this->_Rcount == this->_Rspeed){
			this->_Rcount = 0;
			digitalWrite(RIGHT_MOTOR_STEP,!digitalRead(RIGHT_MOTOR_STEP));
		}
	}
	
}

void Motion::_timerInit(){
	
	//store status register, turn off interrupts
	_tempSREG = SREG;
	cli();
	
	//set interrupt period to 50 microseconds
	ICR1 = _TIMER_CYCLES;
	
	TCCR1A = _TCCR1A_VAL; //set WGM11 = 1 (WGM13:10 = 0b1110 -> Fast PWM Mode 14 -> TOP=ICR1, interrupt at TOP))
	TCCR1B = _TCCR1B_VAL; //no clock prescaling (timer1 frequency = 16MHz)
	
	//set interrupt on overflow
	TIMSK1 = 0x01;
	
	//restore SREG. this will restore interrupts if enabled
	SREG = _tempSREG;
	
}

void Motion::_timerStop(){
	
	TCCR1B = 0x00; //turn off clock
	
}

void Motion::_timerRestart(){
	
	//store status register, turn off interrupts
	_tempSREG = SREG;
	cli();
	
	TCNT1 = 0; //reset counter
	this->_Lcount = 0;
	this->_Rcount = 0;
	
	//start clock
	TCCR1B = _TCCR1B_VAL;
	
	SREG = _tempSREG;
	
}

#endif