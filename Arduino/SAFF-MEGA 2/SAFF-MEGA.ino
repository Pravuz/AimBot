#define __DEBUG
#define __MEGA
#include "Aimbot_Serial.h"

// Sleep related
#include <avr/sleep.h>

// Serial header related
AimBot_Serial *escSerial, *pixySerial;

// PWM-in related vars
bool onRC = false;
int rcTimeout = 0;
bool onAuto = true;
int lastRCvalCH1 = 0;
int lastRCvalCH2 = 0;
int lastRCvalCH3 = 0;
int lastRCvalCH4 = 0;
int chan1 = 5;  // Interrupt numbers for each PWM chanel //SONDRE ENDRET
int chan2 = 4; //SONDRE ENDRET
int chan3 = 3; //SONDRE ENDRET
int chan4 = 2; //SONDRE pin 21 ADDED
volatile unsigned long oldtime1 = 0;
volatile unsigned long timepassed1;
volatile unsigned long oldtime2 = 0;
volatile unsigned long timepassed2;
volatile unsigned long oldtime3 = 0;
volatile unsigned long timepassed3;
volatile unsigned long oldtime4 = 0;
volatile unsigned long timepassed4;

// Power switching
int BrugiPwrPIN = 12;
int VideoTrxPwrPIN = 13;
int PixyPwrPIN = 14;

// Take picture routine
# define CAMERA_BTN_DELAY 100
# define CAMERA_PICT_DELAY 500
int lastPictureTime = 0;
int CameraShtrPIN = 6;
int CameraFokuPIN = 11;

// Mode/loop related
volatile unsigned long lastPassTime = 0;
int loopTime = 1000;

// debug console
volatile unsigned long lastDebug = 0;
int debugTime = 1000;

// Power check
volatile unsigned long lastPowerCheck = 0;
int powerCheckTime = 100;

void setup()
{
	// Setup serial
	setup_Serial();

	// Relay setup
	initButtonAndVoltage();

	// interrupt pins int.4-2
	pinMode(chan1, INPUT); // int.5 -- throttle  (chan1)
	pinMode(chan2, INPUT); // aile 4  chan2
	pinMode(chan3, INPUT); // rudo 3   chan3
	pinMode(chan4, INPUT); // Gear //SONDRE added

	// power pins
	pinMode(CameraShtrPIN, OUTPUT);
	pinMode(CameraFokuPIN, OUTPUT);
	pinMode(BrugiPwrPIN, OUTPUT);
	pinMode(VideoTrxPwrPIN, OUTPUT);

	// Start mode selector interrupt
	attachInterrupt(chan3, calculatePWMch3, CHANGE);
	attachInterrupt(chan4, calculatePWMch4, CHANGE);
	Serial.println("started");
}

void loop()
{
	int diff = millis() - lastPassTime;
	if (diff > loopTime)
	{
		// Run update for the current mode
		if (onAuto && onRC) Mode_Auto_RC();
		if (onAuto && !onRC) Mode_Auto_NC();
		if (!onAuto && onRC) Mode_Manual_RC();
		if (!onAuto && !onRC) Mode_Manual_NC();

		// Power check
		checkButtonAndVoltage();

		// RC check
		if (onRC) checkIfRCstillConnected();

		lastPassTime = millis();
	}

	int diffy = millis() - lastDebug;
	if (diffy > debugTime)
	{
		if (onAuto && onRC) Serial.println("Mode_Auto_RC");
		if (onAuto && !onRC) Serial.println("Mode_Auto_NC");
		if (!onAuto && onRC) Serial.println("Mode_Manual_RC");
		if (!onAuto && !onRC) Serial.println("Mode_Manual_NC");

		lastDebug = millis();
	}
}

// Mode selection routines--------------------------------------------------------------------------
void Mode_Auto_RC()
{
	// Auto mode, video feed on
	digitalWrite(PixyPwrPIN, HIGH);		// Turn on Pixy power
	digitalWrite(BrugiPwrPIN, HIGH);	// Turn on Brugi power
	digitalWrite(VideoTrxPwrPIN, HIGH); // Turn on Video transmitter power

	// Avslutt lytting p� PWM
	detachInterrupt(chan1);
	detachInterrupt(chan2);

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

	// Stop listening to RC-PWM 
	detachInterrupt(chan1);
	detachInterrupt(chan2);

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

	// Start lytting p� PWM-RC
	detachInterrupt(chan1);
	detachInterrupt(chan2);
	attachInterrupt(chan2, calculatePWMch2, CHANGE);
	attachInterrupt(chan1, calculatePWMch1, CHANGE);

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
	while (!onAuto && !onRC)
	{
		// All power off
		digitalWrite(PixyPwrPIN, LOW);
		digitalWrite(BrugiPwrPIN, LOW);
		digitalWrite(VideoTrxPwrPIN, LOW);

		// Stop listening to RC-PWM 
		detachInterrupt(chan1);
		detachInterrupt(chan2);

		delay(500);
		//sleepNow();
	}
}

// Helper routines--------------------------------------------------------------------------
void takePicture()
{
	// Check that there is a set time between pictures
	int diff = millis() - lastPictureTime;
	if (diff > CAMERA_PICT_DELAY)
	{
		digitalWrite(CameraFokuPIN, HIGH);
		delay(CAMERA_BTN_DELAY);
		digitalWrite(CameraShtrPIN, HIGH);
		delay(CAMERA_BTN_DELAY);
		digitalWrite(CameraFokuPIN, LOW);
		digitalWrite(CameraShtrPIN, LOW);
		lastPictureTime = millis();
	}
}

void checkIfRCstillConnected()
{
	// Check if RC is still connected
	rcTimeout++;
	if (rcTimeout > 1000)
	{
		onRC = false;
	}
}

int xRCmin = 1000;
int xRCmax = 2000;
int xRCMAPmin = -10;
int xRCMAPmax = 10;
int yRCmin = 1000;
int yRCmax = 2000;
int yRCMAPmin = -10;
int yRCMAPmax = 10;
char getRCx()
{
	// Map RC vals to degrees, X
	//return (char)map(lastRCvalCH1, 1000, 2000, 0, 100);
	return (char)map(lastRCvalCH1, xRCmin, xRCmax, xRCMAPmin, xRCMAPmax);
}
char getRCy()
{
	// Map RC vals to degrees, Y
	//return (char)map(lastRCvalCH2, 1000, 2000, 0, 100);
	return (char)map(lastRCvalCH2, yRCmin, yRCmax, yRCMAPmin, yRCMAPmax);
}

int xVECT_INmin = -127;
int xVECT_INmax = 127;
int xVECT_OUTmin = -38;
int xVECT_OUTmax = 38;
int yVECT_INmin = -100;
int yVECT_INmax = 100;
int yVECT_OUTmin = -38;
int yVECT_OUTmax = 38;
char getVECTx(char x)
{
	if (x == 0)return 0;
	else
	{
		// Map pixy pixel-vector to degrees, X
		return (char)map(x, xVECT_INmin, xVECT_INmax, xVECT_OUTmin, xVECT_OUTmax);
	}
}
char getVECTy(char y)
{
	if (y == 0)return 0;
	else
	{
		// Map pixy pixel-vector to degrees, Y
		return (char)map(y, yVECT_INmin, yVECT_INmax, yVECT_OUTmin, yVECT_OUTmax);
	}
}

void setup_Serial()
{
	Serial.begin(BAUDRATE);	// Usb debug
	//Serial.println("started");
	//Serial2.begin(BAUDRATE);
	//Serial3.begin(BAUDRATE);
	*escSerial = AimBot_Serial(&Serial2);
	*pixySerial = AimBot_Serial(&Serial3);
}

void wakeUpNow()        // here the interrupt is handled after wakeup
{
	// execute code here after wake-up before returning to the loop() function
	//setup_Serial();
}

void sleepNow()         // here we put the arduino to sleep
{
	/* Now is the time to set the sleep mode. In the Atmega8 datasheet
	* http://www.atmel.com/dyn/resources/prod_documents/doc2486.pdf on page 35
	* The 5 different modes are:
	*     SLEEP_MODE_IDLE         -the least power savings
	*     SLEEP_MODE_ADC
	*     SLEEP_MODE_PWR_SAVE
	*     SLEEP_MODE_STANDBY
	*     SLEEP_MODE_PWR_DOWN     -the most power savings
	*/
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here

	sleep_enable();          // enables the sleep bit in the mcucr register

	// Detach other interrupts on int.4 and attach wakeUpNow
	detachInterrupt(chan3);  // int.4 = pin 19 //SONDRE Endret fra 3 til 20
	attachInterrupt(chan3, wakeUpNow, HIGH); //SONDRE Endret fra 3 til 20

	sleep_cpu(); ////SONDRE sleep_mode() gj�r sleep_enable, sleep_cpu, sleep_disable, s� siden enable og disable blir gjort over og under, trengs bare cpu her?
	//sleep_mode();            // here the device is actually put to sleep
	// THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

	sleep_disable();         // first thing after waking from sleep

	detachInterrupt(chan3);      // disables interrupt 4 on pin 19 so wakeUpNow is only run once //SONDRE Endret fra 3 til 20

	// Start mode selector interrupt gets attached again
	attachInterrupt(chan3, calculatePWMch3, CHANGE); //SONDRE Endret fra 3 til 20
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
		if (timepassed3 > 1800)
		{
			onAuto = true;
		}
		else
		{
			onAuto = false;
		}
		rcTimeout = 0;
		onRC = true;
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
	pinMode(5, OUTPUT); //SONDRE endret fra 7 til 5
	digitalWrite(5, HIGH); //SONDRE endret fra 7 til 5
	pinMode(A0, INPUT);
	pinMode(A1, INPUT); //SONDRE endret fra 5 til 1

}

void checkButtonAndVoltage()
{
	int diff = millis() - lastPowerCheck;
	if (diff > powerCheckTime) // check every 100ms or so
	{

#if 0
		//testing
		String s = "ch1: ";
		s = s + lastRCvalCH1;
		s = s + " ch2:";
		s = s + lastRCvalCH2;
		s = s + " ch3: ";
		s = s + lastRCvalCH3;
		Serial.println(s);
#endif

		if (analogRead(0) > 140)
		{
			delay(1000);
			if (analogRead(0) > 140)
			{
				// power button pressed, power off
				delay(3000);
				digitalWrite(5, LOW); //SONDRE endret fra 7 til 5
				delay(1000);
			}
		}

		if (analogRead(1) < 900) //SONDRE endret fra 5 til 1
		{
			// bat low, power off
			delay(1000);
			digitalWrite(5, LOW); //SONDRE endret fra 7 til 5
			delay(1000);
		}
	}
}