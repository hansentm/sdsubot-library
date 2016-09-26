#ifndef SDSUBOT_H
#define SDSUBOT_H

/*
 * Includes
 */

#include <Arduino.h>
#include "SDSUBotMotion.h"

/*
 * Main SDSUBot class. Will expose all other functionality from subclasses
 */

class SDSUBot{
	
	public:
		/*
		* SDSUBot Constructor. Right now does not need to do anything.
		*/
		SDSUBot();
		
		//motor functions
		void initMotion();
		void sleep();
		void wake();
		void rightMotorForward();
		void rightMotorBackward();
		void leftMotorForward();
		void leftMotorBackward();
		void leftMotorSpeed(unsigned char speed);
		void rightMotorSpeed(unsigned char speed);
		
		
	private:
		Motion _bot_motion;
};

#endif