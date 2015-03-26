#define __DEBUG
#define __MEGA
#include "Aimbot_Serial.h"

// Sleep related
#include <avr/sleep.h>

// Serial header related
AimBot_Serial *escSerial, *pixySerial;

// PWM-in related vars
int mode = 3;

int lastRCvalCH1 = 0;  // Thro (min = 1052, max = 1912), TH_HOLD = 952
int lastRCvalCH2 = 0;  // L/R (Left = 1916) (RIGHT = 1052)
int lastRCvalCH3 = 0;  // GEAR (1052 = 0, 1912 = 1, ) needs ACRO-MODE
int lastRCvalCH4 = 0;  // ELEV (UP = 1916, DOWN = 1052)
#define chan1 5  // Interrupt numbers for each PWM chanel
#define chan2 4
#define chan3 3
#define chan4 2  // pin 21
volatile unsigned long oldtime1 = 0;
volatile unsigned long timepassed1;
volatile unsigned long oldtime2 = 0;
volatile unsigned long timepassed2;
volatile unsigned long oldtime3 = 0;
volatile unsigned long timepassed3;
volatile unsigned long oldtime4 = 0;
volatile unsigned long timepassed4;

// Power switching
int BrugiPwrPIN = 2;
int VideoTrxPwrPIN = 4;
int PixyPwrPIN = 3;

#define onOffPower 5
#define batVolt A1
#define powerButton A0

// Take picture routine
# define CAMERA_BTN_DELAY 100
# define CAMERA_PICT_DELAY 500
int lastPictureTime = 0;
int CameraShtrPIN = 10;
int CameraFokuPIN = 11;

// Mode/loop related
volatile unsigned long lastPassTime = 0;
#define loopTime 100
int count = 0;

// Power check
volatile unsigned long lastPowerCheck = 0;
#define powerCheckTime 1000

void setup()
{
	// Setup serial
	setup_Serial();

	// Relay setup
	initButtonAndVoltage();

	// interrupt pins int.4-2
	pinMode(18, INPUT); // int.5 -- throttle  (chan1)
	pinMode(19, INPUT); // aile 4  chan2
	pinMode(20, INPUT); // elev 3   chan3
	pinMode(21, INPUT);

	// power pins
	pinMode(CameraShtrPIN, OUTPUT);
	pinMode(CameraFokuPIN, OUTPUT);
	pinMode(BrugiPwrPIN, OUTPUT);
	pinMode(VideoTrxPwrPIN, OUTPUT);

	//Start mode selector interrupt
	attachInterrupt(chan4, calculatePWMch4, CHANGE);
	attachInterrupt(chan3, calculatePWMch3, CHANGE);
	attachInterrupt(chan2, calculatePWMch2, CHANGE);
	attachInterrupt(chan1, calculatePWMch1, CHANGE);
}

void loop()
{
	long diff = millis() - lastPassTime;
	if (diff > loopTime)
	{
		// Run update for the current mode
		if (mode == 1) Mode_Auto_RC();
		if (mode == 2) Mode_Auto_NC();
		if (mode == 3) Mode_Manual_RC();
		if (mode == 4) Mode_Manual_NC();

		Serial.println("Loop");
		Serial.println(mode);
		//Serial.println(lastRCvalCH1);
		//Serial.println(lastRCvalCH2);
		//Serial.println(lastRCvalCH3);
		//Serial.println(lastRCvalCH4);
		//Serial.println(count);
		//count++;
		//if (count > 1000)count = 0;
#if 0
		//Power check
		checkButtonAndVoltage(); // OY! fucks everything up when powered from USB!
#endif
		lastPassTime = millis();
	}
}

// Mode selection routines--------------------------------------------------------------------------
void Mode_Auto_RC()
{
	// Auto mode, video feed on
	digitalWrite(PixyPwrPIN, HIGH);		// Turn on Pixy power
	digitalWrite(BrugiPwrPIN, HIGH);	// Turn on Brugi power
	digitalWrite(VideoTrxPwrPIN, HIGH); // Turn on Video transmitter power

	//Get vector from pixy, pass it to Brugi
	pixySerial->serialUpdate();

	char x = getVECTx(pixySerial->getX());
	char y = getVECTy(pixySerial->getY());

	if (x != 0 || y != 0)
	{
		pixySerial->stopPixy(); // Stop pixy while moving
		escSerial->sendVect(x, y); // Send to Brugi if any movement

		while (Serial2.available() < 1)
		{
			// Wait for Brugi feedback (brugi in position)
		}
		takePicture(); // Arrived at destination, take picture
		pixySerial->startPixy(); // Start pixy again
		while (Serial2.available() > 0)
		{
			// Expecting one char, read buffer to end regardless
			Serial2.read();
		}
	}
}

void Mode_Auto_NC()
{
	// Auto, no video feed
	digitalWrite(PixyPwrPIN, HIGH);
	digitalWrite(BrugiPwrPIN, HIGH);
	digitalWrite(VideoTrxPwrPIN, LOW);

	pixySerial->serialUpdate();

	char x = getVECTx(pixySerial->getX());
	char y = getVECTy(pixySerial->getY());

	if (x != 0 || y != 0)
	{
		pixySerial->stopPixy(); // Stop pixy while moving
		escSerial->sendVect(x, y); // Send to Brugi if any movement

		while (Serial2.available() < 1)
		{
			// Wait for Brugi feedback (brugi in position)
		}
		takePicture(); // Arrived at destination, take picture
		pixySerial->startPixy(); // Start pixy again
		while (Serial2.available() > 0) //flush brugi serial
		{
			// Expecting one char, read buffer to end regardless
			Serial2.read();
		}
	}
}

void Mode_Manual_RC()
{
	digitalWrite(PixyPwrPIN, LOW);
	digitalWrite(BrugiPwrPIN, HIGH);
	digitalWrite(VideoTrxPwrPIN, HIGH);

	char x = getRCx();
	char y = getRCy();
	if (x != 0 || y != 0)
	{
		// Send to Brugi if any movement
		escSerial->sendRCxy(x, y);
	}
}

void Mode_Manual_NC()
{
	// All power off
	digitalWrite(PixyPwrPIN, LOW);
	digitalWrite(BrugiPwrPIN, LOW);
	digitalWrite(VideoTrxPwrPIN, LOW);
}

// Helper routines--------------------------------------------------------------------------
void takePicture()
{
	// Check that there is a set time between pictures
	int diff = millis() - lastPictureTime;
	if (diff > CAMERA_PICT_DELAY)
	{
		digitalWrite(CameraShtrPIN, HIGH);
		delay(CAMERA_BTN_DELAY);
		digitalWrite(CameraShtrPIN, LOW);
		lastPictureTime = millis();
	}
	// TODO: add fokuPin for compability with DSLR's
}


#define xRCmin 1916
#define xRCmax 1052
#define xRCMAPmin -10
#define xRCMAPmax 10
#define yRCmin 1040
#define yRCmax 1916
#define yRCMAPmin -10
#define yRCMAPmax 10
char getRCx()
{
	// Map RC vals to degrees, X
	//return (char)map(lastRCvalCH1, 1000, 2000, 0, 100);
	//int lastRCvalCH2 = 0;  // L/R (Left = 1916) (RIGHT = 1052)
	return (char)map(lastRCvalCH2, xRCmin, xRCmax, xRCMAPmin, xRCMAPmax);
}
char getRCy()
{
	// Map RC vals to degrees, Y
	//return (char)map(lastRCvalCH2, 1000, 2000, 0, 100);
	//int lastRCvalCH4 = 0;  // ELEV (UP = 1916, DOWN = 1052)
	return (char)map(lastRCvalCH4, yRCmin, yRCmax, yRCMAPmin, yRCMAPmax);
}

#define xVECT_INmin -127
#define xVECT_INmax 127
#define xVECT_OUTmin -38
#define xVECT_OUTmax 38
#define yVECT_INmin -100
#define yVECT_INmax 100
#define yVECT_OUTmin -38
#define yVECT_OUTmax 38
char getVECTx(char x)
{
	// Map pixy pixel-vector to degrees, X
	if (x == 0) return 0;
	else return (char)map(x, xVECT_INmin, xVECT_INmax, xVECT_OUTmin, xVECT_OUTmax);
}
char getVECTy(char y)
{
	// Map pixy pixel-vector to degrees, Y
	if (y == 0) return 0;
	else return (char)map(y, yVECT_INmin, yVECT_INmax, yVECT_OUTmin, yVECT_OUTmax);
}

void setup_Serial()
{
	Serial.begin(BAUDRATE);	// Usb debug
	*escSerial = AimBot_Serial();
	*pixySerial = AimBot_Serial();
}



void calculatePWMch1() // Throttle 1
{
	timepassed1 = micros() - oldtime1;
	oldtime1 = micros();

	if (timepassed1 > 900 && timepassed1 < 2100)
	{
		lastRCvalCH1 = timepassed1;
	}
}
void calculatePWMch2() // Throttle 2
{
	timepassed2 = micros() - oldtime2;
	oldtime2 = micros();

	if (timepassed2 > 900 && timepassed2 < 2100)
	{
		lastRCvalCH2 = timepassed2;
	}
}
void calculatePWMch3() // Mode selector
{
	timepassed3 = micros() - oldtime3;
	oldtime3 = micros();

	if (timepassed3 < 2500 && timepassed3 > 900)
	{
		lastRCvalCH3 = timepassed3;
		if (timepassed3 > 2000)
		{
			mode = 1;
		}
		else if (timepassed3 > 1600)
		{
			mode = 3;
		}
		else if (timepassed3 > 1200)
		{
			mode = 3;
		}
		else
		{
			mode = 4;
		}
	}
}
void calculatePWMch4() // Camera trigger
{
	timepassed4 = micros() - oldtime4;
	oldtime4 = micros();

	if (timepassed4 > 900 && timepassed4 < 2100)
	{
		lastRCvalCH4 = timepassed4;
	}
}

void initButtonAndVoltage()
{
	pinMode(onOffPower, OUTPUT);
	digitalWrite(onOffPower, HIGH);
	pinMode(powerButton, INPUT);
	pinMode(batVolt, INPUT);

}

void checkButtonAndVoltage()
{
	long diff = millis() - lastPowerCheck;
	if (diff > powerCheckTime) // check every 100ms or so
	{
		if (analogRead(powerButton) > 140)
		{
			delay(1000);
			if (analogRead(powerButton) > 140)
			{
				// power button pressed, power off
				delay(3000);
				digitalWrite(onOffPower, LOW);
				delay(1000);
			}
		}

		if (analogRead(batVolt) < 900)
		{
			// bat low, power off
			delay(1000);
			digitalWrite(onOffPower, LOW);
			delay(1000);
		}
	}
}