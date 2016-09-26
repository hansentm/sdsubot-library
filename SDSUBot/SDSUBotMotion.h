#ifndef SDSUBOT_MOTION_H
#define SDSUBOT_MOTION_H

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
		
	private:
		unsigned char _Lspeed;
		unsigned char _Rspeed;
		
		
};


#endif