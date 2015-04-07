#define __DEBUG
#define __MEGA
#include "Aimbot_Serial.h"
#include "Aimbot_EEPROM.h"
#include <avr/sleep.h>

// Interrupt numbers for each PWM chanel
#define CHAN1_INTERRUPT		3	// pin 20
#define CHAN2_INTERRUPT		4	// pin 19
#define CHAN3_INTERRUPT		5	// pin 18
#define CHAN4_INTERRUPT		2	// pin 21
#define CHAN1_DIGIN			20	
#define CHAN2_DIGIN			19	
#define CHAN3_DIGIN			18	
#define CHAN4_DIGIN			21	

// Power switching
#define ESC_PWR				2
#define FPV_PWR				4
#define PIX_PWR				3
#define RIG_PWR				5
#define BTN_PWR				A0
#define BAT_VOLTAGE			A1

// Camera (GoPro/DSLR)
int CAM_BTN_DELAY = 100;
int CAM_TRIGGER_DELAY = 500;
int CAM_FOCUS_DELAY = 200;
#define CAM_TRIGGER			6
#define CAM_FOCUS			7

// MISC
int LOOP_TIME = 50; 
int PWR_CHECK_INTERVAL = 1000;

// USB
#define USBconnectedPIN		31
bool USBisConnected = false;

// RC defs
int xRCmin = 1916;
int xRCmax = 1052;
int xRCMAPmin = -10;
int xRCMAPmax = 10;
int yRCmin = 1040;
int yRCmax = 1916;
int yRCMAPmin = -10;
int yRCMAPmax = 10;
int xVECT_INmin = -127;
int xVECT_INmax = 127;
int xVECT_OUTmin = -38;
int xVECT_OUTmax = 38;
int yVECT_INmin = -100;
int yVECT_INmax = 100;
int yVECT_OUTmin = -38;
int yVECT_OUTmax = 38;

bool megaDebug = true;
enum Aimbot_Mode{ //TODO: Make sleep mode?
	AUTO_RC,
	AUTO_NC,
	MANUAL_RC,
	MANUAL_NC,
	SETTINGS
}currentMode;

// PWM-in related vars
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
bool isDSLR = false;

// Mode/loop related
volatile unsigned long lastPassTime = 0;
int count = 0;

// Power check
volatile unsigned long lastPowerCheck = 0;

// Serial interface
static AimBot_Serial m_pixySerial(Serial3);
static AimBot_Serial m_escSerial(Serial2);

void setup()
{
	// Setup serial
	if (megaDebug) Serial.begin(BAUDRATE);	// Usb debug
	if (megaDebug) Serial.println("Setup started");
	Serial2.begin(BAUDRATE); //m_pixySerial begin
	Serial3.begin(BAUDRATE); //m_escSerial begin

	// Initial Mode
	currentMode = MANUAL_NC;

	// Relay setup
	initButtonAndVoltage();

	// RC channels
	pinMode(CHAN1_DIGIN, INPUT); // throttle 
	pinMode(CHAN2_DIGIN, INPUT); // aile 
	pinMode(CHAN3_DIGIN, INPUT); // elev 
	pinMode(CHAN4_DIGIN, INPUT); // rudd 

	// power pins
	pinMode(CAM_TRIGGER, OUTPUT);
	pinMode(CAM_FOCUS, OUTPUT);
	pinMode(ESC_PWR, OUTPUT);
	pinMode(FPV_PWR, OUTPUT);

	//Start mode selector interrupt (on RC channels)
	attachInterrupt(CHAN4_INTERRUPT, calculatePWMch4, CHANGE);
	attachInterrupt(CHAN3_INTERRUPT, calculatePWMch3, CHANGE);
	attachInterrupt(CHAN2_INTERRUPT, calculatePWMch2, CHANGE);
	attachInterrupt(CHAN1_INTERRUPT, calculatePWMch1, CHANGE);

	if (megaDebug) Serial.println("Setup complete");
}

void loop()
{
	if (USBisConnected) // Settings & debug
	{
		communicateWithPC();
	}
	else // normal operation:
	{
		if(checkCameraTrigger()) takePicture(); // Check trigger and take picture if pressed

		long diff = millis() - lastPassTime;
		if (diff > LOOP_TIME)
		{
			// Run update for the current mode
			switch (currentMode)
			{
			case AUTO_RC:
				Mode_Auto();
				break;
			case AUTO_NC:
				Mode_Auto();
				break;
			case MANUAL_RC:
				Mode_Manual_RC();
				break;
			case MANUAL_NC:
				//Mode_Manual_NC();
				break;
			case SETTINGS:
				//SETTINGS()
				break;
			default:
				Mode_Auto();
				break;
			}

#if 0
			//TODO: Make routine to check what our power source is.
			//Power check
			checkButtonAndVoltage(); // OY! fucks everything up when powered from USB!
#endif
			lastPassTime = millis();
		}
	}
	
	USBisConnected = isUSBconnected(); // Check if usb is connected
}

// Mode selection routines--------------------------------------------------------------------------

void Mode_Auto()
{
	if (!m_pixySerial.update()) return; // update failed, nothing more to do, returning

	char x = getVECTx(m_pixySerial.getX());
	char y = getVECTy(m_pixySerial.getY());

	if (x != 0 || y != 0)
	{
		m_pixySerial.pixyCmd(PIXY_STOP); // Stop pixy while moving
		m_escSerial.sendXY(x, y, VECTOR); // Send to Brugi if any movement

		// Wait for Brugi feedback (brugi in position)
		while (Serial2.available() < 1);

		takePicture(); // Arrived at destination, take picture

		//flush both serials, reset
		m_pixySerial.flush();
		m_escSerial.flush();

		m_pixySerial.pixyCmd(PIXY_START); // Start pixy again
	}
}

void Mode_Manual_RC()
{
	char x = getRCx();
	char y = getRCy();
	if (x != 0 || y != 0)
	{
		// Send to Brugi if any movement
		m_escSerial.sendXY(x, y, MOV_XY);
	}
}
#if 0 // no longer used.
void Mode_Manual_NC()
{
}
#endif
// Helper routines--------------------------------------------------------------------------
bool checkCameraTrigger()
{
	// check if trigger is pressed
	if (lastRCvalCH4 > 1500) return true;
	else return false;
}

void takePicture()
{
	if (isDSLR) // DSLR's require focus before trigger
	{
		// Check that there is a set time between pictures
		int diff = millis() - lastPictureTime;
		if (diff > CAM_TRIGGER_DELAY)
		{
			digitalWrite(CAM_FOCUS, HIGH);
			delay(CAM_FOCUS_DELAY);
			digitalWrite(CAM_FOCUS, LOW);
			digitalWrite(CAM_TRIGGER, HIGH);
			delay(CAM_BTN_DELAY);
			digitalWrite(CAM_TRIGGER, LOW);
			lastPictureTime = millis();
		}
	}
	else
	{
		int diff = millis() - lastPictureTime;
		if (diff > CAM_TRIGGER_DELAY)
		{
			digitalWrite(CAM_TRIGGER, HIGH);
			delay(CAM_BTN_DELAY);
			digitalWrite(CAM_TRIGGER, LOW);
			lastPictureTime = millis();
		}
	}
}

char getRCx()
{
	// Map RC vals to degrees, X
	return (char)map(lastRCvalCH2, xRCmin, xRCmax, xRCMAPmin, xRCMAPmax);
}
char getRCy()
{
	// Map RC vals to degrees, Y
	return (char)map(lastRCvalCH4, yRCmin, yRCmax, yRCMAPmin, yRCMAPmax);
}

char getVECTx(char x)
{
	// Map pixy pixel-vector to degrees, X
	if (x == 0) return 0;
	return (char)map(x, xVECT_INmin, xVECT_INmax, xVECT_OUTmin, xVECT_OUTmax);
}
char getVECTy(char y)
{
	// Map pixy pixel-vector to degrees, Y
	if (y == 0) return 0;
	return (char)map(y, yVECT_INmin, yVECT_INmax, yVECT_OUTmin, yVECT_OUTmax);
}

void calculatePWMch1() // Throttle 1
{
	timepassed1 = micros() - oldtime1;
	oldtime1 = micros();

	if (timepassed1 > 900 && timepassed1 < 2100) lastRCvalCH1 = timepassed1;
}
void calculatePWMch2() // Throttle 2
{
	timepassed2 = micros() - oldtime2;
	oldtime2 = micros();

	if (timepassed2 > 900 && timepassed2 < 2100) lastRCvalCH2 = timepassed2;
}
void calculatePWMch3() // Mode selector
{
	// Mode select uses ORX flap gyro switch with 3 modes
	timepassed3 = micros() - oldtime3;
	oldtime3 = micros();

	if (timepassed3 < 2100 && timepassed3 > 900) 
	{
		lastRCvalCH3 = timepassed3;
		if (timepassed3 > 1800){
			if (currentMode != AUTO_RC && megaDebug) Serial.println("Mode is now set to Auto_RC");
			if (currentMode != AUTO_RC)
			{
				// Auto mode, video feed on
				digitalWrite(PIX_PWR, HIGH); // Turn on Pixy power
				digitalWrite(ESC_PWR, HIGH); // Turn on Brugi power
				digitalWrite(FPV_PWR, HIGH); // Turn on Video transmitter power
			}
			currentMode = AUTO_RC;
		}
		else if (timepassed3 > 1200)  {
			if (currentMode != AUTO_NC && megaDebug) Serial.println("Mode is now set to Auto_NC");
			if (currentMode != AUTO_NC)
			{
				// Auto, no video feed
				digitalWrite(PIX_PWR, HIGH);
				digitalWrite(ESC_PWR, HIGH);
				digitalWrite(FPV_PWR, LOW);
			}
			currentMode = AUTO_NC;
		}
		else {
			if (currentMode != MANUAL_RC && megaDebug) Serial.println("Mode is now set to Manual_RC");
			if (currentMode != MANUAL_RC){
				// Manual, no pixy feed
				digitalWrite(PIX_PWR, LOW);
				digitalWrite(ESC_PWR, HIGH);
				digitalWrite(FPV_PWR, HIGH);
			}
			currentMode = MANUAL_RC;
		}
	}
}
void calculatePWMch4() // Camera trigger
{
	timepassed4 = micros() - oldtime4;
	oldtime4 = micros();

	if (timepassed4 > 900 && timepassed4 < 2100) lastRCvalCH4 = timepassed4;
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
#if 0 //enable before release, fix power source detect first. 
	if (analogRead(BAT_VOLTAGE) < 900)
	{
		// bat low, power off
		delay(1000);
		digitalWrite(RIG_PWR, LOW);
		delay(1000);
	}
#endif
}

bool isUSBconnected()
{
	return digitalRead(USBconnectedPIN);
}

void communicateWithPC()
{
	// TODO: Add pc-communication stuff here
	// update variables etc

}

void saveSettingsToEEPROM()
{
	// Saves all settings to EEPROM
	int i = 0;
	EEPROMWriteBool(i, isDSLR); i++;
	EEPROMWriteInt16(i, CAM_BTN_DELAY); i++; i++;
	EEPROMWriteInt16(i, CAM_TRIGGER_DELAY); i++; i++;
	EEPROMWriteInt16(i, CAM_FOCUS_DELAY); i++; i++;
	EEPROMWriteInt16(i, LOOP_TIME); i++; i++;
	EEPROMWriteInt16(i, PWR_CHECK_INTERVAL); i++; i++;
	EEPROMWriteInt16(i, xRCmin); i++; i++;
	EEPROMWriteInt16(i, xRCmax); i++; i++;
	EEPROMWriteInt16(i, xRCMAPmin); i++; i++;
	EEPROMWriteInt16(i, xRCMAPmax); i++; i++;
	EEPROMWriteInt16(i, yRCmin); i++; i++;
	EEPROMWriteInt16(i, yRCmax); i++; i++;
	EEPROMWriteInt16(i, yRCMAPmin); i++; i++;
	EEPROMWriteInt16(i, yRCMAPmax); i++; i++;
	EEPROMWriteInt16(i, xVECT_INmin); i++; i++;
	EEPROMWriteInt16(i, xVECT_INmax); i++; i++;
	EEPROMWriteInt16(i, xVECT_OUTmin); i++; i++;
	EEPROMWriteInt16(i, xVECT_OUTmax); i++; i++;
	EEPROMWriteInt16(i, yVECT_INmin); i++; i++;
	EEPROMWriteInt16(i, yVECT_INmax); i++; i++;
	EEPROMWriteInt16(i, yVECT_OUTmin); i++; i++;
	EEPROMWriteInt16(i, yVECT_OUTmax); i++; i++;
}

void loadSettingsFromEEPROM()
{
	int i = 0;
	bool isdslr = EEPROMReadBool(i); i++;
	int CAM_BTN_DELAY = EEPROMReadInt16(i); i++; i++;
	int CAM_TRIGGER_DELAY = EEPROMReadInt16(i); i++; i++;
	int CAM_FOCUS_DELAY = EEPROMReadInt16(i); i++; i++;
	int LOOP_TIME = EEPROMReadInt16(i); i++; i++;
	int PWR_CHECK_INTERVAL = EEPROMReadInt16(i); i++; i++;
	int xRCmin = EEPROMReadInt16(i); i++; i++;
	int xRCmax = EEPROMReadInt16(i); i++; i++;
	int xRCMAPmin = EEPROMReadInt16(i); i++; i++;
	int xRCMAPmax = EEPROMReadInt16(i); i++; i++;
	int yRCmin = EEPROMReadInt16(i); i++; i++;
	int yRCmax = EEPROMReadInt16(i); i++; i++;
	int yRCMAPmin = EEPROMReadInt16(i); i++; i++;
	int yRCMAPmax = EEPROMReadInt16(i); i++; i++;
	int xVECT_INmin = EEPROMReadInt16(i); i++; i++;
	int xVECT_INmax = EEPROMReadInt16(i); i++; i++;
	int xVECT_OUTmin = EEPROMReadInt16(i); i++; i++;
	int xVECT_OUTmax = EEPROMReadInt16(i); i++; i++;
	int yVECT_INmin = EEPROMReadInt16(i); i++; i++;
	int yVECT_INmax = EEPROMReadInt16(i); i++; i++;
	int yVECT_OUTmin = EEPROMReadInt16(i); i++; i++;
	int yVECT_OUTmax = EEPROMReadInt16(i); i++; i++;
}