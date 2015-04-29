#include "BLcontroller.h"
#include "Interupts_.h"
//#include "definitions.h"
#include <Wire\Wire.h>
#define __ESC
#include "Aimbot_Serial.h"

#define bldc1 0.1171875
#define bldc2 0.05859375
#define DIR_MASK 0x80
#define SPEED_FACTOR 30
#define SPEED_FACTOR_PIXY 20
#define Y_MIN_LIMIT -160
#define Y_MAX_LIMIT 320
#define MOTORPOWER 100 // 0 to 255
#define MOTORPOWER_HOLD 150

char z_Pos = 0, y_Pos = 0;
int16_t z_Pos_Steps = 0, y_Pos_Steps = 0, y_Motor_Signed = 0;
uint8_t z_Motor = 0, y_Motor = 0;
int8_t z_count, y_count;

// Low-pass filter
float last_z_Pos = 0, last_y_Pos = 0;
#define LAST_TO_NEW_RATIO 0.9  //ex 0.7 gives: 0.7 old and 0.3 new


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
	delay(250);
	MoveMotorPosSpeed(motorNumberYaw, y_Motor, MOTORPOWER_HOLD);
	MoveMotorPosSpeed(motorNumberPitch, z_Motor, MOTORPOWER_HOLD);
	megaSerial.sendPosReached();
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

		//lowPassFilter();

		if (!rc_mode) moveToPos();
		megaSerial.flush();
	}
	if (rc_mode) moveWithSpeed();
}

void lowPassFilter()
{
	last_z_Pos = ((1 - LAST_TO_NEW_RATIO)*z_Pos) + (LAST_TO_NEW_RATIO*last_z_Pos);
	last_y_Pos = ((1 - LAST_TO_NEW_RATIO)*y_Pos) + (LAST_TO_NEW_RATIO*last_y_Pos);
	y_Pos = last_y_Pos;
	z_Pos = last_z_Pos;
}

void moveToPos(){
	z_count = 0;
	y_count = 0;

	//if (!(z_Pos | y_Pos)) return; // z and y is 0, nothing to do

	//converting angle to motor steps.
	z_Pos_Steps = z_Pos / bldc2; //todo: OPTIMALISER.
	y_Pos_Steps = y_Pos / bldc1;

	int16_t z_Origin = z_Pos_Steps, y_Origin = y_Pos_Steps;

#if 0
	uint16_t y_skipCount = 0, z_skipCount = 0;
	uint8_t generalSpeedFactor = 0;
#endif
	while ((z_Pos_Steps != 0) || (y_Pos_Steps != 0))
	{
#if 0
		if (motorUpdate)
		{
			motorUpdate = false;
#endif
#if 0
			/* The speed of the motorcontroller is constant, updating once every 31.5 microseconds. 
			we want to slow this down, using generalSpeedFactor in the following way. 
			*/
			if (generalSpeedFactor) {
				generalSpeedFactor--;
				continue; //skips this iteration, waiting for the next time motorUpdate is set. 
			}
			else generalSpeedFactor = 4;
#endif
#if 0
			//when we are closing in on our position, we want to slow down gradually
			if (!y_skipCount && abs(y_Pos_Steps) < SPEED_FACTOR_PIXY/2) y_skipCount = SPEED_FACTOR_PIXY/2 - abs(y_Pos_Steps);
			if(y_skipCount) y_skipCount--;
			if (!z_skipCount && abs(z_Pos_Steps) < SPEED_FACTOR_PIXY) z_skipCount = SPEED_FACTOR_PIXY - abs(y_Pos_Steps);
			if(z_skipCount) z_skipCount--;


			if (!y_skipCount && y_Pos_Steps != 0)
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
				MoveMotorPosSpeed(motorNumberYaw, y_Motor, MOTORPOWER);
			}
			if (!z_skipCount && z_Pos_Steps != 0)
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
				MoveMotorPosSpeed(motorNumberPitch, z_Motor, MOTORPOWER);
			}
		}
	}
#endif
#if 1
		if (motorUpdate_0)
		{
			motorUpdate_0 = false;
			if (z_Pos_Steps != 0)
			{
				if (z_Pos_Steps > 0)
				{
					MOTORUPDATE_FREQ_0 = map(z_Pos_Steps, 0, z_Origin, 100, 500);
					--z_Pos_Steps;
					--z_Motor;
				}
				else if (z_Pos_Steps < 0)
				{
					MOTORUPDATE_FREQ_0 = map(z_Pos_Steps, z_Origin, 0, 100, 500);
					++z_Pos_Steps;
					++z_Motor;
				}
				MoveMotorPosSpeed(motorNumberPitch, z_Motor, MOTORPOWER);
			}
		}
		if (motorUpdate_1)
		{
			motorUpdate_1 = false;
			if (y_Pos_Steps != 0)
			{
				if (y_Pos_Steps > 0)
				{
					MOTORUPDATE_FREQ_1 = map(y_Pos_Steps, 0, y_Origin, 500, 1000);
					if (y_Motor_Signed > Y_MIN_LIMIT){
						y_Motor--;
						y_Motor_Signed--;
						y_Pos_Steps--;
					}
					else y_Pos_Steps = 0;
				}
				else if (y_Pos_Steps < 0)
				{
					MOTORUPDATE_FREQ_1 = map(y_Pos_Steps, y_Origin, 0, 500, 1000);
					if (y_Motor_Signed < Y_MAX_LIMIT){
						y_Motor++;
						y_Motor_Signed++;
						y_Pos_Steps++;
					}
					else y_Pos_Steps = 0;
				}
				MoveMotorPosSpeed(motorNumberYaw, y_Motor, MOTORPOWER);
			}
		}
	}
#endif
#if 0
	MoveMotorPosSpeed(motorNumberYaw, y_Motor, MOTORPOWER_HOLD);
	MoveMotorPosSpeed(motorNumberPitch, z_Motor, MOTORPOWER_HOLD);
	delay(250);
#endif
	megaSerial.sendPosReached();
}

void moveWithSpeed(){

	if (motorUpdate){
		motorUpdate = false;

		if (z_Pos > 1 || z_Pos < -1) z_count += z_Pos;
		if (y_Pos > 1 || y_Pos < -1) y_count += y_Pos;

		if (z_count >= SPEED_FACTOR || z_count <= -SPEED_FACTOR){
#if 1
			if (z_count > 0) z_count -= SPEED_FACTOR;
			if (z_count < 0) z_count += SPEED_FACTOR;
#endif
			//z_count = 0;
			if (z_Pos & DIR_MASK) z_Motor--;
			else z_Motor++;
			MoveMotorPosSpeed(motorNumberPitch, z_Motor, MOTORPOWER_HOLD);
		}

		if (y_count >= SPEED_FACTOR || y_count <= -SPEED_FACTOR){
#if 1
			if (y_count > 0) y_count -= SPEED_FACTOR;
			if (y_count < 0) y_count += SPEED_FACTOR;
#endif
			//y_count = 0;
			if ((y_Pos & DIR_MASK) && y_Motor_Signed > Y_MIN_LIMIT){
				y_Motor--;
				y_Motor_Signed--;
			}
			else if (y_Motor_Signed < Y_MAX_LIMIT){
				y_Motor++;
				y_Motor_Signed++;
			}
			MoveMotorPosSpeed(motorNumberYaw, y_Motor, MOTORPOWER_HOLD);
		}
	}
}
