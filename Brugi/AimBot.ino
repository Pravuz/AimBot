#include "BLcontroller.h"
#include "Interupts_.h"
#include <Wire\Wire.h>

uint8_t z_axe = 0, y_axe = 0;
int16_t z_Pos = 0, y_Pos = 0; //Verdier som kommer inn serielt fra MEGA
int16_t z_Pos_Steps = 0, y_Pos_Steps = 0;

boolean updown = true;
boolean crib = false;
boolean box = false;




void setup()
{
	Serial.begin(115200);
	delay(5000);
	
	Serial.println("Init BLcontroller");
	initBlController();
	
	Serial.println("Init Motorstuff");
	initMotorStuff();

	motorPowerOff();

	sei();
}



void loop()
{
	if (Serial.available() > 0 && (z_Pos == 0 || y_Pos == 0))
	{
		if (z_Pos == 0) 
		{ 
			z_Pos = 0; 
			z_Pos_Steps = map(z_Pos, -37.5, 37.5, -320, 320);
			crib = true;
		} //Hent Veriene fra serielbufferen.
		if (y_Pos == 0) 
		{ 
			y_Pos = 0; 
			y_Pos_Steps = map(z_Pos, -37.5, 37.5, -320, 320);
			box = true;
		}
	}

	if (motorUpdate)
	{
		motorUpdate = false;

		//Verdi i x og z, omdreining i grader, mottatt serielt.
		//Verdien blir brukt til nedtelling for pwm-moduleringen.
				
		if (crib)
		{
			if (y_Pos_Steps > 0)
			{
				--y_Pos_Steps;
			}
			else if (y_Pos_Steps < 0)
			{
				++y_Pos_Steps;
			}
			else
			{
				crib = false;
			}
		}

		if (box)
		{
			if (z_Pos_Steps > 0)
			{
				--z_Pos_Steps;
			}
			else if (z_Pos_Steps < 0)
			{
				++z_Pos_Steps;
			}
			else
			{
				crib = false;
			}
		}

		MoveMotorPosSpeed(motorNumberPitch, z_Pos_Steps, 180);
		MoveMotorPosSpeed(motorNumberYaw, y_Pos_Steps, 180);

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
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

	//int32_t computePID(int16_t accValue, int16_t Kp, int16_t Ki, int16_t Kd)
	//{
	//	/*error = Setpoint - accValue
	//	output = Kp * error*/
	//
	//	//return output;
	//}

}
