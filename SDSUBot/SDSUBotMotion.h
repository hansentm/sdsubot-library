#ifndef SDSUBOT_MOTION_H
#define SDSUBOT_MOTION_H

/*
 * Includes
 */

#include "Arduino.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*
 * Defines
 */
 
#define LEFT_MOTOR_DIRECTION  8   //PIND8
#define LEFT_MOTOR_STEP       10  //PIND10
#define RIGHT_MOTOR_DIRECTION 13  //PIND13
#define RIGHT_MOTOR_STEP      12  //PIND12
#define MOTOR_SLEEP           11  //PIND11

#define LEFT_FORWARD          HIGH
#define RIGHT_FORWARD         LOW
#define LEFT_BACKWARD         LOW
#define RIGHT_BACKWARD        HIGH

#define MAX_SPEED_CONSTANT	  285 //max speed. 295 -> 4ms period at 255. 

/*
 *	Motion Class
 */

class Motion{
	
	public:
		Motion();
		
		void init();
		
		void sleep();
		void wake();
		void rightMotorForward();
		void rightMotorBackward();
		void leftMotorForward();
		void leftMotorBackward();
		void leftMotorSpeed(unsigned char speed);
		void rightMotorSpeed(unsigned char speed);
		
		//expose to call from ISR
		void _timerInterrupt();
		
	private:
		void _timerInit();
		void _timerStop();
		void _timerRestart();
		void _stop_start_Check();
	
		unsigned int _Lcount;
		unsigned int _Rcount;
		unsigned int _Lspeed;
		unsigned int _Rspeed;
		
		bool _sleeping;
		
		char _tempSREG; //stores status register during interrupts
		
};

extern Motion BotMotion;

#endif