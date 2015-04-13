#include "BLcontroller.h"
#include "Interupts_.h"
//#include "definitions.h"
#include <Wire\Wire.h>
#define __ESC
#include "Aimbot_Serial.h"

#define bldc1 0.1171875
#define bldc2 0.05859375

float z_Float = 0, y_Float = 0;

uint8_t z_axe = 0, y_axe = 0;
int16_t z_Pos = 0, y_Pos = 0; //Verdier som kommer inn serielt fra MEGA
int16_t z_Pos_Steps = 0, y_Pos_Steps = 0;
uint8_t z_Motor = 0, y_Motor = 0;

boolean RCin = true;
boolean crib = false;
boolean box = false;


static AimBot_Serial megaSerial(Serial);

void setup()
{
	Serial.begin(BAUDRATE);

	initBlController();
	
	initMotorStuff();

	motorPowerOff();

	sei();
}


void loop()
{
	if (!(megaSerial.update())) return; //no new instructions, so nothing more to do. 

	z_Pos = (int16_t)megaSerial.getX();
	y_Pos = (int16_t)megaSerial.getY();

	if (megaSerial.isRCmode())
	{
		z_Float += z_Pos*0.1; //todo: factor here should be setting
		y_Float += y_Pos*0.1;

		z_Pos = z_Float;
		y_Pos = y_Float;
	}
	else
	{
		z_Float = 0;
		y_Float = 0;
	}

	//converting angle to motor steps.
	z_Pos_Steps = (int16_t) ((float)(z_Pos / bldc2)); //todo: bldc1/2 should be setting.
	y_Pos_Steps = (int16_t) ((float)(y_Pos / bldc1));

	//do calcs and move motors
	while ((z_Pos_Steps!=0) || (y_Pos_Steps!=0))
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
				MoveMotorPosSpeed(motorNumberYaw, y_Motor, 255);
				y_Float = 0;
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
				MoveMotorPosSpeed(motorNumberPitch, z_Motor, 255);
				z_Float = 0;
			}
		}		
	}
	if (z_Pos_Steps == 0 && y_Pos_Steps == 0)
	{
		megaSerial.sendPosReached();
	}
#if 0

	if (motorUpdate)
	{
		motorUpdate = false;

		//Verdi i x og z, omdreining i grader, mottatt serielt.
		//Verdien blir brukt til nedtelling for pwm-moduleringen.

		++z_Pos_Steps;
		--y_Pos_Steps;

		MoveMotorPosSpeed(motorNumberPitch, z_Pos_Steps, 255);
		MoveMotorPosSpeed(motorNumberYaw, y_Pos_Steps, 255);
	}

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
	}

	int32_t computePID(int16_t accValue, int16_t Kp, int16_t Ki, int16_t Kd)
	{
		/*error = Setpoint - accValue
		output = Kp * error*/
	
		//return output;
	}
#endif
}
