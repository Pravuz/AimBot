#include "BLcontroller.h"
#include "Interupts_.h"
#include <Wire\Wire.h>
#define __ESC
#include "Aimbot_Serial.h"

#define bldc1 360/12/256
#define bldc2 360/24/256


uint8_t z_axe = 0, y_axe = 0;
int16_t z_Pos = 0, y_Pos = 0; //Verdier som kommer inn serielt fra MEGA
int16_t z_Pos_Steps = 0, y_Pos_Steps = 0;

boolean RCin = true;
boolean crib = false;
boolean box = false;


AimBot_Serial *megaSerial;

void setup()
{

	*megaSerial = AimBot_Serial();

	initBlController();
	
	initMotorStuff();

	motorPowerOff();

	sei();
}


void loop()
{

	megaSerial->serialUpdate();
	

	z_Pos = megaSerial->getX();
	y_Pos = megaSerial->getY();

	z_Pos_Steps = z_Pos / bldc2;
	y_Pos_Steps = y_Pos / bldc1;
		
	//gj�r utregninger og flytter motorene
	
	while (z_Pos!=0 & y_Pos!=0)
	{
		if (motorUpdate)
		{
			motorUpdate = false;
			
			if (y_Pos_Steps != 0)
			{
				if (y_Pos_Steps > 0)
				{
					--y_Pos_Steps;
				}
				else if (y_Pos_Steps < 0)
				{
					++y_Pos_Steps;
				}
			}

			if (z_Pos_Steps != 0)
			{
				if (z_Pos_Steps > 0)
				{
					--z_Pos_Steps;
				}
				else if (z_Pos_Steps < 0)
				{
					++z_Pos_Steps;
				}
			}
		}
		MoveMotorPosSpeed(motorNumberPitch, z_Pos_Steps, 180);
		MoveMotorPosSpeed(motorNumberYaw, y_Pos_Steps, 180);
	}
	
	megaSerial->sendPosReached();
	

	//if (motorUpdate)
	//{
	//	motorUpdate = false;

	//	//Verdi i x og z, omdreining i grader, mottatt serielt.
	//	//Verdien blir brukt til nedtelling for pwm-moduleringen.
	//			
	//	if (crib)
	//	{
	//		if (y_Pos_Steps > 0)
	//		{
	//			--y_Pos_Steps;
	//		}
	//		else if (y_Pos_Steps < 0)
	//		{
	//			++y_Pos_Steps;
	//		}
	//		else
	//		{
	//			crib = false;
	//		}
	//	}

	//	if (box)
	//	{
	//		if (z_Pos_Steps > 0)
	//		{
	//			--z_Pos_Steps;
	//		}
	//		else if (z_Pos_Steps < 0)
	//		{
	//			++z_Pos_Steps;
	//		}
	//		else
	//		{
	//			box = false;
	//		}
	//	}

	//	MoveMotorPosSpeed(motorNumberPitch, z_Pos_Steps, 180);
	//	MoveMotorPosSpeed(motorNumberYaw, y_Pos_Steps, 180);

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*MoveMotorPosSpeed(motorNumberPitch, y_axe, 180);
		MoveMotorPosSpeed(motorNumberYaw, z_axe, 180);
		if (updown)
		{
			++z_axe;
			 updown = false;
		}
		else
		{
			updown = true;
		}*/
	//}

	//int32_t computePID(int16_t accValue, int16_t Kp, int16_t Ki, int16_t Kd)
	//{
	//	/*error = Setpoint - accValue
	//	output = Kp * error*/
	//
	//	//return output;
	//}

}
