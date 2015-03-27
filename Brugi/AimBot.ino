#include "BLcontroller.h"
#include "Interupts_.h"
//#include "definitions.h"
#include <Wire\Wire.h>
#define __ESC
#include "Aimbot_Serial.h"

#define bldc1 360/12/256
#define bldc2 360/24/256

float z_Float = 0, y_Float = 0;

uint8_t z_axe = 0, y_axe = 0;
int16_t z_Pos = 0, y_Pos = 0; //Verdier som kommer inn serielt fra MEGA
int16_t z_Pos_Steps = 0, y_Pos_Steps = 0;
uint8_t z_Motor = 0, y_Motor = 0;

boolean RCin = true;
boolean crib = false;
boolean box = false;


AimBot_Serial *megaSerial;

void setup()
{

	*megaSerial = AimBot_Serial(&Serial);

	initBlController();
	
	initMotorStuff();

	motorPowerOff();

	sei();
}


void loop()
{

	megaSerial->update();

	RCin = megaSerial->isRCmode();

	z_Pos = megaSerial->getX();
	y_Pos = megaSerial->getY();

	/*if (RCin)
	{
		z_Float += z_Pos*0.1;
		y_Float += y_Pos*0.1;

		z_Pos = z_Float;
		y_Pos = y_Float;
	}
	else if (!RCin)
	{
		z_Float = 1;
		y_Float = 0;
	}*/
	
	z_Pos++;
	z_Pos_Steps = z_Pos / bldc2;
	y_Pos_Steps = y_Pos / bldc1;
		
	//gjør utregninger og flytter motorene
	
	while (z_Pos_Steps!=0 || y_Pos_Steps!=0)
	{
		if (motorUpdate)
		{
			motorUpdate = false;
			
			if (y_Pos_Steps != 0)
			{
				if (y_Pos_Steps > 0)
				{
					--y_Pos_Steps;
					--y_Motor;
				}
				else if (y_Pos_Steps < 0)
				{
					++y_Pos_Steps;
					++y_Motor;
				}
			}

			if (z_Pos_Steps != 0)
			{
				if (z_Pos_Steps > 0)
				{
					--z_Pos_Steps;
					--z_Motor;
				}
				else if (z_Pos_Steps < 0)
				{
					++z_Pos_Steps;
					++z_Motor;
				}
			}
		}
		MoveMotorPosSpeed(motorNumberPitch, z_Motor, 180);
		MoveMotorPosSpeed(motorNumberYaw, y_Motor, 180);
	}
	if (z_Pos == 0 && y_Pos == 0)
	{
		megaSerial->sendPosReached();
	}
	

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
