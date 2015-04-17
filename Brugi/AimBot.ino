#include "BLcontroller.h"
#include "Interupts_.h"
//#include "definitions.h"
#include <Wire\Wire.h>
#define __ESC
#include "Aimbot_Serial.h"

#define bldc1 0.1171875
#define bldc2 0.05859375
#define DIR_MASK 0x80
#define SPEED_FACTOR 40
#define Y_MIN_LIMIT -250
#define Y_MAX_LIMIT 150

char z_Pos = 0, y_Pos = 0; //Verdier som kommer inn serielt fra MEGA
char last_z_Pos = 0, last_y_Pos = 0;
int16_t z_Pos_Steps = 0, y_Pos_Steps = 0, y_Motor_Signed = 0;
uint8_t z_Motor = 0, y_Motor = 0;
int8_t z_count, y_count;
bool rc_mode = false;

static AimBot_Serial megaSerial(Serial);

void setup()
{
	Serial.begin(BAUDRATE);

	initBlController();

	initMotorStuff();

	motorPowerOff();

	sei();

#if 1
	//moving to 0 pos. 
	MoveMotorPosSpeed(motorNumberYaw, y_Motor, 100);
	MoveMotorPosSpeed(motorNumberPitch, z_Motor, 100);
#endif
}

void loop()
{
	if (megaSerial.update()){
		rc_mode = megaSerial.isRCmode();
		z_Pos = megaSerial.getX();
		y_Pos = megaSerial.getY();

		if (!z_Pos) z_count = 0;
		if (!y_Pos) y_count = 0;

		lowPassFilter();

		if (!rc_mode) moveToPos();
	}

	if (rc_mode) moveWithSpeed();

	megaSerial.flush();
}

void lowPassFilter()
{
	z_Pos = (0.5*z_Pos) + (0.5*last_z_Pos);
	y_Pos = (0.5*y_Pos) + (0.5*last_y_Pos);
	last_y_Pos = y_Pos;
	last_z_Pos = z_Pos;
}

void moveToPos(){
	z_count = 0;
	y_count = 0;
	
	if (!(z_Pos  | y_Pos)) return; // z and y is 0, nothing to do

	//converting angle to motor steps.
	z_Pos_Steps = z_Pos / bldc2; //todo: OPTIMALISER.
	y_Pos_Steps = y_Pos / bldc1;

	while ((z_Pos_Steps!=0) || (y_Pos_Steps!=0))
	{
		if (motorUpdate)
		{
			motorUpdate = false;

			if (y_Pos_Steps != 0)
			{
				if (y_Pos_Steps > 0)
				{
					if (y_Motor_Signed > Y_MIN_LIMIT){
						y_Motor--;
						y_Motor_Signed--;
						y_Pos_Steps--;
					}
					else y_Pos_Steps = 0;
				}
				else if (y_Pos_Steps < 0)
				{
					if (y_Motor_Signed < Y_MAX_LIMIT){
						y_Motor++;
						y_Motor_Signed++;
						y_Pos_Steps++;
					}
					else y_Pos_Steps = 0;
				}
				MoveMotorPosSpeed(motorNumberYaw, y_Motor, 255);
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
			}
		}		
	}
	if (z_Pos_Steps == 0 && y_Pos_Steps == 0) megaSerial.sendPosReached();
}

void moveWithSpeed(){

	if (motorUpdate){
		motorUpdate = false;
		
		if(z_Pos > 1 || z_Pos < -1) z_count += z_Pos;
		if(y_Pos > 1 || y_Pos < -1) y_count += y_Pos;

		if (z_count >= SPEED_FACTOR || z_count <= -SPEED_FACTOR){
			z_count = 0;
			if (z_Pos & DIR_MASK) z_Motor--;
			else z_Motor++;
			MoveMotorPosSpeed(motorNumberPitch, z_Motor, 255);
		}

		if (y_count >= SPEED_FACTOR || y_count <= -SPEED_FACTOR){
			y_count = 0;
			if ((y_Pos & DIR_MASK) && y_Motor_Signed > Y_MIN_LIMIT){
				y_Motor--;
				y_Motor_Signed--;
			}
			else if (y_Motor_Signed < Y_MAX_LIMIT){
				y_Motor++;
				y_Motor_Signed++;
			}
			MoveMotorPosSpeed(motorNumberYaw, y_Motor, 255);
		}
	}
}
