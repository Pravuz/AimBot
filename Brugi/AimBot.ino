#include <Wire\Wire.h>
#define __ESC
#include "Aimbot_Serial.h"
#include "definitions.h"
#include "MPU6050.h"
#include "Timer1.h"
#include "variables.h"
MPU6050 mpu;
#include "fastMathRoutines.h" 
#include "orientationRoutines.h"
#include "BLcontroller.h"

#define bldc1 0.2008929 //360degree/256sinval/7magneticpos
#define bldc2 0.1278409 //360/256/11
#define DIR_MASK 0x80
#define Y_MIN_LIMIT -160
#define Y_MAX_LIMIT 320
#define MOTORPOWER 255 // 0 to 255

char z_Pos = 0, y_Pos = 0;
int16_t z_Pos_Steps = 0, y_Pos_Steps = 0, y_Motor_Signed = 0;
uint8_t y_Motor = 0;
int z_Motor = 0;
bool rc_mode = false, moving = false, ser_updated = false;

enum mode{
	IDLE,
	MANUAL,
	AUTO
}currentMode;

static AimBot_Serial megaSerial(Serial);

void setup()
{
	Serial.begin(BAUDRATE);

	initBlController();
	initMotorStuff();
	motorPowerOff();
	setDefaultParameters();

	// Start I2C and Configure Frequency
	Wire.begin();
	TWSR = 0;                                  // no prescaler => prescaler = 1
	TWBR = ((16000000L / I2C_SPEED) - 16) / 2; // change the I2C clock rate
	TWCR = 1 << TWEN;                            // enable twi module, no interrupt

	// Initialize MPU 
	initResolutionDevider();

	// init I2C and MPU6050
	if (initI2C()) {
		// Init IMU variables
		initIMU();
		// Gyro Offset calibration
		if (config.gyroCal) {
			gyroOffsetCalibration();
		}
	}
	else {
		gimState = (gimStateType)GIM_ERROR;
	}

	initSensorOrientation();
	initPIDs();

	//moving to 0 pos. 
	MoveMotorPosSpeed(motorNumberYaw, y_Motor, 100);
	MoveMotorPosSpeed(motorNumberPitch, z_Motor, 100);
	delay(150);

	//let mega know we're ready
	megaSerial.sendPosReached();
	currentMode = IDLE;
}

/************************/
/* PID Controller       */
/************************/
// PID integer inplementation
//   DTms  ... sample period (ms)
//   DTinv ... sample frequency (Hz), inverse of DT (just to avoid division)
int32_t ComputePID(int32_t DTms, int32_t DTinv, int32_t in, int32_t setPoint, int32_t *errorSum, int32_t *errorOld, int32_t Kp, int16_t Ki, int32_t Kd)
{
	int32_t error = setPoint - in;
	int32_t Ierr;

	Ierr = error * Ki * DTms;
	Ierr = constrain_int32(Ierr, -(int32_t)1000 * 100, (int32_t)1000 * 100);
	*errorSum += Ierr;

	/*Compute PID Output*/
	int32_t out = (Kp * error) + *errorSum + Kd * (error - *errorOld) * DTinv;
	*errorOld = error;

	out = out / 4096 / 8;

	return out;
}

void loop()
{
	if (currentMode == IDLE)
	{
		if (megaSerial.update())
		{
			currentMode = megaSerial.isRCmode() ? MANUAL : AUTO;
			z_Pos = megaSerial.getX();
			y_Pos = megaSerial.getY();

			megaSerial.flush();
			ser_updated = true;
		}
		else delay(50);
	}
	else if (currentMode == AUTO){
		if (megaSerial.update())
		{
			z_Pos = megaSerial.getX();
			y_Pos = megaSerial.getY();

			megaSerial.flush();
			//ser_updated = true;
		}
	}
	else operatingRoutine();
}

void operatingRoutine(){
	if (motorUpdate){
		motorUpdate = false;

		// update IMU data            
		readGyros();   // td = 330us
		updateGyroAttitude(); // td = 176 us
		updateACCAttitude(); // td = 21 us
		getAttiduteAngles(); // td = 372 us

		//only using IMU and PID on z_Motor
		pitchAngleSet = utilLP3_float(qLPPitch, z_Pos, LOWPASS_K_FLOAT(0.03));
		z_Motor = ComputePID(DT_INT_MS, DT_INT_INV, angle[YAW], pitchAngleSet * 1000, &pitchErrorSum, &pitchErrorOld, pitchPIDpar.Kp, pitchPIDpar.Ki, pitchPIDpar.Kd);

		if (enableMotorUpdates) {
			//if (currentMode == AUTO) moveToPos();
			//else if (currentMode == MANUAL) 
			moveWithSpeed();
			MoveMotorPosSpeed(motorNumberYaw, y_Motor, MOTORPOWER);
			MoveMotorPosSpeed(motorNumberPitch, z_Motor, MOTORPOWER);
		}

		switch (count)
		{
		case 1:
			readACCs(); // td = 330us
			break;
		case 2:
			updateACC(); // td = 120us
			break;
		case 3:
			//communicate with MEGA
			if (megaSerial.update())
			{
				//currentMode = megaSerial.isRCmode() ? MANUAL : AUTO; won't change before restart.
				z_Pos = megaSerial.getX();
				y_Pos = megaSerial.getY();

				megaSerial.flush();
				ser_updated = true;
			}
			break;
		case 4:
			// gimbal state transitions, td=56us
			switch (gimState)
			{
			case GIM_IDLE:
				// wait 2 sec to settle ACC, before PID controlerbecomes active 
				stateCount++;
				if (stateCount >= LOOPUPDATE_FREQ / 10 * 1) // 1 sec 
				{
					gimState = (gimStateType)GIM_UNLOCKED;
					stateCount = 0;
				}
				enableMotorUpdates = false;
				setACCtc(0.2);
				disableAccGtest = true;
				break;
			case GIM_UNLOCKED:
				// allow PID controller to settle on ACC position
				stateCount++;
				if (stateCount >= LOOPUPDATE_FREQ / 10 * LOCK_TIME_SEC)
				{
					gimState = (gimStateType)GIM_LOCKED;
					stateCount = 0;
				}
				enableMotorUpdates = true;
				disableAccGtest = true;
				setACCtc(2.0);
				disableAccGtest = true;
				break;
			case GIM_LOCKED:
				// normal operation
				enableMotorUpdates = true;
				disableAccGtest = false;
				setACCtc(config.accTimeConstant);
				break;
			case GIM_ERROR:
				// error state
				enableMotorUpdates = false;
				motorPowerOff();
				break;
			}
#if 1
		case 5:
			//   regular i2c test
			mpu.testConnection();
			break;
		case 6:
			//ACC trace output and led blink in brugi
			count = 0;
			break;
		default:
			break;
#endif
#if 0 //testing running with fewer state steps. 
		case 5:
			//empty 
			//RC-get pitch in brugi
			break;
		case 6:
			//empty
			//RC-get roll in brugi
			break;
		case 7:
			//empty
			//RC-eval in brugi
			break;
		case 8:
			//empty
			//RC-analog inputs in brugi
			break;
		case 9:
			//   regular i2c test
			mpu.testConnection();
			break;
		case 10:
			//ACC trace output and led blink in brugi
			count = 0;
			break;
		default:
			break;
#endif
		}
		count++;
	}
}

void moveToPosNoIMU()
{
	//converting angle to motor steps.
	z_Pos_Steps = z_Pos / bldc2;
	y_Pos_Steps = y_Pos / bldc1;

	while ((z_Pos_Steps != 0) || (y_Pos_Steps != 0))
	{
		if (motorUpdate && z_Pos_Steps != 0)
		{
			motorUpdate = false;
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
			MoveMotorPosSpeed(motorNumberPitch, z_Motor, MOTORPOWER);
			MoveMotorPosSpeed(motorNumberYaw, y_Motor, MOTORPOWER);
		}
	}
	megaSerial.sendPosReached();
}

void moveToPos()
{
	if (ser_updated){
		ser_updated = false;
		moving = true;
		//converting angle to motor steps.
		if (y_Pos) y_Pos_Steps = y_Pos / bldc1;
		if (z_Pos) z_Pos_Steps = z_Pos / bldc2;
		else if (!y_Pos) return;
	}

	if (z_Pos_Steps != 0 || y_Pos_Steps != 0)
	{
		if (z_Pos_Steps < 0) //z_Pos is negative
		{
			z_Pos_Steps++;
		}
		else if (z_Pos_Steps > 0)
		{
			z_Pos_Steps--;
			//z_Motor *= -1;
		}
		else z_Pos = 0;

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
	}
	else if (moving)
	{
		moving = false;
		z_Pos = 0;
		megaSerial.sendPosReached();
	}
}

void moveWithSpeed()
{
	if (!(z_Pos || y_Pos)) return; //returning if both are 0
	if (y_Pos == 1 || y_Pos == -1) y_Pos = 0; //filtering out misreadings when user don't want to move. 

	//if (z_Pos < 0) z_Motor *= -1;

	if ((y_Pos & DIR_MASK) && y_Motor_Signed > Y_MIN_LIMIT){
		y_Motor--;
		y_Motor_Signed--;
	}
	else if (y_Pos && y_Motor_Signed < Y_MAX_LIMIT){
		y_Motor++;
		y_Motor_Signed++;
	}
}