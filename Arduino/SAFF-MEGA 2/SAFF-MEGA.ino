#define __DEBUG
#define __MEGA
#include "Aimbot_Serial.h"
#include <avr/sleep.h>

// Interrupt numbers for each PWM chanel
#define CHAN1_INTERRUPT		5	// pin 18
#define CHAN2_INTERRUPT		4	// pin 19
#define CHAN3_INTERRUPT		3	// pin 20
#define CHAN4_INTERRUPT		2	// pin 21
#define CHAN1_DIGIN			18	
#define CHAN2_DIGIN			19	
#define CHAN3_DIGIN			20	
#define CHAN4_DIGIN			21	

// Power switching
#define ESC_PWR				2
#define FPV_PWR				4
#define PIX_PWR				3
#define RIG_PWR				5
#define BTN_PWR				A0
#define BAT_VOLTAGE			A1

// Camera (GoPro/DSLR)
#define CAM_BTN_DELAY		100
#define CAM_TRIGGER_DELAY	500
#define CAM_TRIGGER			6
#define CAM_FOCUS			7

// MISC
#define LOOP_TIME			100
#define PWR_CHECK_INTERVAL	1000

// PWM-in related vars
enum Aimbot_Mode{ //TODO: Make sleep mode?
	AUTO_RC,
	AUTO_NC,
	MANUAL_RC,
	MANUAL_NC
}currentMode;

// Serial interface
AimBot_Serial *m_aimSerial;
 
int lastRCvalCH1 = 0;  // Thro (min = 1052, max = 1912), TH_HOLD = 952
int lastRCvalCH2 = 0;  // L/R (Left = 1916) (RIGHT = 1052)
int lastRCvalCH3 = 0;  // GEAR (1052 = 0, 1912 = 1, ) needs ACRO-MODE
int lastRCvalCH4 = 0;  // ELEV (UP = 1916, DOWN = 1052)

//timing 
volatile unsigned long oldtime1 = 0;
volatile unsigned long timepassed1;
volatile unsigned long oldtime2 = 0;
volatile unsigned long timepassed2;
volatile unsigned long oldtime3 = 0;
volatile unsigned long timepassed3;
volatile unsigned long oldtime4 = 0;
volatile unsigned long timepassed4;

// Take picture routine
int lastPictureTime = 0;

// Mode/loop related
volatile unsigned long lastPassTime = 0;
int count = 0;

// Power check
volatile unsigned long lastPowerCheck = 0;

void setup()
{
	// Initial Mode
	currentMode = AUTO_NC;

	// Setup serial
	setup_Serial();

	// Relay setup
	initButtonAndVoltage();

	// interrupt pins int.4-2
	pinMode(CHAN1_DIGIN, INPUT); // int.5 -- throttle  (CHAN1_INTERRUPT)
	pinMode(CHAN2_DIGIN, INPUT); // aile 4  CHAN2_INTERRUPT
	pinMode(CHAN3_DIGIN, INPUT); // elev 3   CHAN3_INTERRUPT
	pinMode(CHAN4_DIGIN, INPUT);

	// power pins
	pinMode(CAM_TRIGGER, OUTPUT);
	pinMode(CAM_FOCUS, OUTPUT);
	pinMode(ESC_PWR, OUTPUT);
	pinMode(FPV_PWR, OUTPUT);

	//Start mode selector interrupt
	attachInterrupt(CHAN4_INTERRUPT, calculatePWMch4, CHANGE);
	attachInterrupt(CHAN3_INTERRUPT, calculatePWMch3, CHANGE);
	attachInterrupt(CHAN2_INTERRUPT, calculatePWMch2, CHANGE);
	attachInterrupt(CHAN1_INTERRUPT, calculatePWMch1, CHANGE);
}

void loop()
{
	long diff = millis() - lastPassTime;
	if (diff > LOOP_TIME)
	{
		// Run update for the current mode
		switch (currentMode)
		{
		case AUTO_RC:
			Mode_Auto_RC();
			break;
		case AUTO_NC:
			Mode_Auto_NC();
			break;
		case MANUAL_RC:
			Mode_Manual_RC();
			break;
		case MANUAL_NC:
			Mode_Manual_NC();
			break;
		default:
			Mode_Auto_NC();
			break;
		}

		Serial.println("Loop");
		//Serial.println(lastRCvalCH1);
		//Serial.println(lastRCvalCH2);
		//Serial.println(lastRCvalCH3);
		//Serial.println(lastRCvalCH4);
		//Serial.println(count);
		//count++;
		//if (count > 1000)count = 0;
		
#if 0
		//TODO: Make routine to check what our power source is.
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
	digitalWrite(PIX_PWR, HIGH); // Turn on Pixy power
	digitalWrite(ESC_PWR, HIGH); // Turn on Brugi power
	digitalWrite(FPV_PWR, HIGH); // Turn on Video transmitter power

	//Get vector from pixy, pass it to Brugi
	m_aimSerial->serialUpdate();

	char x = getVECTx(m_aimSerial->getX());
	char y = getVECTy(m_aimSerial->getY());

	if (x != 0 || y != 0)
	{
		m_aimSerial->stopPixy(); // Stop pixy while moving
		m_aimSerial->sendVect(x, y); // Send to Brugi if any movement

		while (Serial2.available() < 1)
		{
			// Wait for Brugi feedback (brugi in position)
		}
		takePicture(); // Arrived at destination, take picture
		m_aimSerial->flushBuf();
		m_aimSerial->startPixy(); // Start pixy again
	}
}

void Mode_Auto_NC()
{
	// Auto, no video feed
	digitalWrite(PIX_PWR, HIGH);
	digitalWrite(ESC_PWR, HIGH);
	digitalWrite(FPV_PWR, LOW);

	m_aimSerial->serialUpdate();

	char x = getVECTx(m_aimSerial->getX());
	char y = getVECTy(m_aimSerial->getY());

	if (x != 0 || y != 0)
	{
		m_aimSerial->stopPixy(); // Stop pixy while moving
		m_aimSerial->sendVect(x, y); // Send to Brugi if any movement

		while (Serial2.available() < 1)
		{
			// Wait for Brugi feedback (brugi in position)
		}
		takePicture(); // Arrived at destination, take picture
		m_aimSerial->startPixy(); // Start pixy again
		while (Serial2.available() > 0) //flush brugi serial
		{
			// Expecting one char, read buffer to end regardless
			Serial2.read();
		}
	}
}

void Mode_Manual_RC()
{
	digitalWrite(PIX_PWR, LOW);
	digitalWrite(ESC_PWR, HIGH);
	digitalWrite(FPV_PWR, HIGH);

	char x = getRCx();
	char y = getRCy();
	if (x != 0 || y != 0)
	{
		// Send to Brugi if any movement
		m_aimSerial->sendRCxy(x, y);
	}
}

void Mode_Manual_NC()
{
	// All power off
	digitalWrite(PIX_PWR, LOW);
	digitalWrite(ESC_PWR, LOW);
	digitalWrite(FPV_PWR, LOW);
}

// Helper routines--------------------------------------------------------------------------
void takePicture()
{
	// Check that there is a set time between pictures
	int diff = millis() - lastPictureTime;
	if (diff > CAM_TRIGGER_DELAY)
	{
		digitalWrite(CAM_TRIGGER, HIGH);
		delay(CAM_BTN_DELAY);
		digitalWrite(CAM_TRIGGER, LOW);
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
	*m_aimSerial = AimBot_Serial();
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
		if (timepassed3 > 2000) currentMode = AUTO_RC;
		else if (timepassed3 > 1600) currentMode = AUTO_NC;
		else if (timepassed3 > 1200) currentMode = MANUAL_RC;
		else currentMode = MANUAL_NC;

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
	pinMode(RIG_PWR, OUTPUT);
	digitalWrite(RIG_PWR, HIGH);
	pinMode(BTN_PWR, INPUT);
	pinMode(BAT_VOLTAGE, INPUT);

}

void checkButtonAndVoltage()
{
	long diff = millis() - lastPowerCheck;
	if (diff > PWR_CHECK_INTERVAL) // check every 100ms or so
	{
		if (analogRead(BTN_PWR) > 140)
		{
			delay(1000);
			if (analogRead(BTN_PWR) > 140)
			{
				// power button pressed, power off
				delay(3000);
				digitalWrite(RIG_PWR, LOW);
				delay(1000);
			}
		}

		if (analogRead(BAT_VOLTAGE) < 900)
		{
			// bat low, power off
			delay(1000);
			digitalWrite(RIG_PWR, LOW);
			delay(1000);
		}
	}
}