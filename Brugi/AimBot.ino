#include "BLcontroller.h"
#include "Interupts_.h"
#include <Wire\Wire.h>
#define __ESC
#include "Aimbot_Serial.h"

#define bldc1 0.1171875
#define bldc2 0.05859375
#define DIR_MASK 0x80
#define Y_MIN_LIMIT -160
#define Y_MAX_LIMIT 320
#define MOTORPOWER 255 // 0 to 255
#define MOTOR_0_DEFAULT_FREQ 128
#define MOTOR_1_DEFAULT_FREQ 64
#define MOTOR_0_MIN_FREQ 192
#define MOTOR_1_MIN_FREQ 96
#define MOTOR_0_MAX_FREQ 256
#define MOTOR_1_MAX_FREQ 256

char z_Pos = 0, y_Pos = 0;
int16_t z_Pos_Steps = 0, y_Pos_Steps = 0, y_Motor_Signed = 0;
uint8_t z_Motor = 0, y_Motor = 0;
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
	delay(250);
	megaSerial.sendPosReached();
#endif
}

void loop()
{
	if (megaSerial.update()){
		rc_mode = megaSerial.isRCmode();
		z_Pos = megaSerial.getX();
		y_Pos = megaSerial.getY();

		if (!rc_mode) moveToPos();
		else 
		{
			motor_0_freq = MOTOR_0_DEFAULT_FREQ;
			motor_1_freq = MOTOR_1_DEFAULT_FREQ;
		}
		megaSerial.flush();
	}
	//when in RC-mode, we want to continually move regardless of the success of serial update. 
	if (rc_mode) moveWithSpeed();
}

void moveToPos(){

	//converting angle to motor steps.
	z_Pos_Steps = z_Pos != 0 ? z_Pos / bldc2 : z_Pos_Steps = 0; //todo: OPTIMALISER.
	y_Pos_Steps = y_Pos != 0 ? y_Pos / bldc1 : y_Pos_Steps = 0;

	int16_t z_pos_origin = z_Pos_Steps;
	int16_t y_pos_origin = y_Pos_Steps;

	while ((z_Pos_Steps != 0) || (y_Pos_Steps != 0))
	{
		if (motor_0_update && z_Pos_Steps != 0)
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
			setMotorFreq(z_pos_origin, z_Pos_Steps, motorNumberPitch);
			motor_0_update = false;
			MoveMotorPosSpeed(motorNumberPitch, z_Motor, MOTORPOWER);
		}
		if (motor_1_update && y_Pos_Steps != 0)
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
			setMotorFreq(y_pos_origin, y_Pos_Steps, motorNumberYaw);
			motor_1_update = false;
			MoveMotorPosSpeed(motorNumberYaw, y_Motor, MOTORPOWER);
		}
	}
	megaSerial.sendPosReached();
}

void moveWithSpeed(){

	if ((z_Pos >= -1 && z_Pos <= 1)) z_Pos = 0;
	if ((y_Pos >= -1 && y_Pos <= 1)) y_Pos = 0;
	//if (!(z_Pos | y_Pos)) return; // z and y is 0, nothing to do

	if (motor_0_update){
		motor_0_update = false;
		if (z_Pos & DIR_MASK) z_Motor--;
		else if (z_Pos) z_Motor++;
		MoveMotorPosSpeed(motorNumberPitch, z_Motor, MOTORPOWER);
	}

	if (motor_1_update){
		motor_1_update = false;
		if ((y_Pos & DIR_MASK) && y_Motor_Signed > Y_MIN_LIMIT){
			y_Motor--;
			y_Motor_Signed--;
		}
		else if (y_Pos && y_Motor_Signed < Y_MAX_LIMIT){
			y_Motor++;
			y_Motor_Signed++;
		}
		MoveMotorPosSpeed(motorNumberYaw, y_Motor, MOTORPOWER);
	}
}

void setMotorFreq(int16_t &origin, int16_t &progress, uint8_t motorNumber){
	switch (motorNumber)
	{
	case motorNumberPitch:
		motor_0_freq = origin > 0 ? map(progress, 0, origin, MOTOR_0_MIN_FREQ, MOTOR_0_MAX_FREQ) : map(progress, origin, 0, MOTOR_0_MIN_FREQ, MOTOR_0_MAX_FREQ);
		break;
	case motorNumberYaw:
		motor_1_freq = origin > 0 ? map(progress, 0, origin, MOTOR_1_MIN_FREQ, MOTOR_1_MAX_FREQ) : map(progress, origin, 0, MOTOR_1_MIN_FREQ, MOTOR_1_MAX_FREQ);
		break;
	default:
		break;
	}
}