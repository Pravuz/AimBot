// Declarations and info

//#define DEBUG_MODE_ON

#define BAUD_RATE 115200

// Interrupt pins on mega:
// int.0 = 2, int.1 = 3, int.2 = 21, int.3 = 20, int.4 = 19, int.5 = 18

// Sleep related
#include <avr/sleep.h>
int sleepStatus = 0;             // variable to store a request for sleep
int count = 0;                   // counter
// Url for sleep info: http://playground.arduino.cc/Learning/ArduinoSleepCode


// PWM-in related vars
bool onRC = false;
int rcTimeout = 0;
bool onAuto = true;
int lastRCvalCH1 = 0;
int lastRCvalCH2 = 0;
int lastRCvalCH3 = 0;

// Power switching
int CameraShtrPIN = 10;
int CameraFokuPIN = 11;
int BrugiPwrPIN = 12;
int VideoTrxPwrPIN = 13;
int PixyPwrPIN = 14;

// SPI to Pixy (on the ICSP header at the Arduino board)
#include <SPI.h>
int pixyDelayTime = 500;
int manualDelayTime = 10;
int lastPictureTime = 0;
# define CAMERA_BTN_DELAY 100
# define CAMERA_PICT_DELAY 500

// max value for 16bit int = 32767
// 32 767us = 0,032767s og 1/0,032767s=30,51850947599719hz
// max value for 16bit uint = 65535
// could change timepassed to a 16bit uint
// oldtime however gets huge, needs long
volatile unsigned long oldtime1 = 0;
volatile unsigned long timepassed1;
volatile unsigned long oldtime2 = 0;
volatile unsigned long timepassed2;
volatile unsigned long oldtime3 = 0;
volatile unsigned long timepassed3;
volatile unsigned long lastPassTime = 0;

volatile unsigned long lastPowerCheck = 0;
int powerCheckTime = 100;

int chan1 = 5;
int chan2 = 4;
int chan3 = 3;


void setup()
{
	// Relay setup
	initButtonAndVoltage();

	// interrupt pins int.4-2
	pinMode(18, INPUT); // int.5 -- throttle  (chan1)
	pinMode(19, INPUT); // aile 4  chan2
	pinMode(20, INPUT); // elev 3   chan3

	// power pins
	pinMode(CameraShtrPIN, OUTPUT);
	pinMode(CameraFokuPIN, OUTPUT);
	pinMode(BrugiPwrPIN, OUTPUT);
	pinMode(VideoTrxPwrPIN, OUTPUT);

	// Setup serial
	setup_Serial();

#ifdef DEBUG_MODE_ON
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);

	// test leds
	digitalWrite(8, HIGH);
	digitalWrite(9, HIGH);
	digitalWrite(10, HIGH);
	digitalWrite(11, HIGH);
	digitalWrite(12, HIGH);
	delay(3000);
	digitalWrite(8, LOW);
	digitalWrite(9, LOW);
	digitalWrite(10, LOW);
	digitalWrite(11, LOW);
	digitalWrite(12, LOW);
#endif

	// Start mode selector interrupt
	attachInterrupt(chan3, calculatePWMch3, CHANGE);

	// init Pixy
	//initSPI();
}

void loop()
{
	if (onAuto && onRC) Mode_Auto_RC();
	if (onAuto && !onRC) Mode_Auto_NC();
	if (!onAuto && onRC) Mode_Manual_RC();
	if (!onAuto && !onRC) Mode_Manual_NC();
}


// Mode selection routines--------------------------------------------------------------------------
void Mode_Auto_RC()
{
	// Auto mode, video feed on
	digitalWrite(PixyPwrPIN, HIGH);		// Turn on Pixy power
	digitalWrite(BrugiPwrPIN, HIGH);	// Turn on Brugi power
	digitalWrite(VideoTrxPwrPIN, HIGH); // Turn on Video transmitter power

	// Avslutt lytting på PWM
	detachInterrupt(chan1);
	detachInterrupt(chan2);

	Serial.println("Mode_Auto_RC");

	while (onAuto && onRC)
	{
#ifdef DEBUG_MODE_ON
		digitalWrite(8, HIGH);
		digitalWrite(9, LOW);
		digitalWrite(10, LOW);
		digitalWrite(11, LOW);
		
#endif

#if 0		
		//Get vector from pixy, pass it to Brugi
		int diff = millis() - lastPassTime;
		if (diff > pixyDelayTime)
		{
			uint16_t x = getWord();
			uint16_t y = getWord();
			if (x != 0 || y != 0)
			{
				// Send to Brugi if any movement
				Serial1.print("X");
				Serial1.print(x);
				Serial1.print(",");
				Serial1.print("Y");
				Serial1.print(y);
				Serial1.print(",");
			}
			lastPassTime = millis();

			while (Serial1.available() < 1)
			{
				// Wait for Brugi feedback
			}
			takePicture(); // Arrived at destination, take picture
			while (Serial1.available() > 0)
			{
				// Expecting one char, read buffer to end regardless
				Serial1.read();
			}
		}
#endif
		// Check if RC is still connected
		delay(1);
		rcTimeout++;
		if (rcTimeout > 1000)
		{
			onRC = false;
		}
		

		// Power check
		checkButtonAndVoltage();

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

	Serial.println("Mode_Auto_NC");

	while (onAuto && !onRC) // 
	{
#ifdef DEBUG_MODE_ON
		digitalWrite(8, LOW);
		digitalWrite(9, HIGH);
		digitalWrite(10, LOW);
		digitalWrite(11, LOW);
		
#endif

#if 0		
		//Get vector from pixy, pass it to Brugi
		int diff = millis() - lastPassTime;
		if (diff > pixyDelayTime)
		{
			uint16_t x = getWord();
			uint16_t y = getWord();
			if (x != 0 || y != 0)
			{
				// Send to Brugi if any movement
				Serial1.print("X");
				Serial1.print(x);
				Serial1.print(",");
				Serial1.print("Y");
				Serial1.print(y);
				Serial1.print(",");
			}
			lastPassTime = millis();

			while (Serial1.available() < 1)
			{
				// Wait for Brugi feedback
			}
			takePicture(); // Arrived at destination, take picture
			while (Serial1.available() > 0)
			{
				// Expecting one char, read buffer to end regardless
				Serial1.read();
			}
		}

#endif
		// Power check
		checkButtonAndVoltage();
	}
}

void Mode_Manual_RC()
{
	digitalWrite(PixyPwrPIN, LOW);
	digitalWrite(BrugiPwrPIN, HIGH);
	digitalWrite(VideoTrxPwrPIN, HIGH);

	// Start lytting på PWM-RC
	attachInterrupt(chan2, calculatePWMch2, CHANGE);
	attachInterrupt(chan1, calculatePWMch1, CHANGE);


	Serial.println("Mode_Manual_RC");
	while (!onAuto && onRC)
	{
#ifdef DEBUG_MODE_ON
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		digitalWrite(10, HIGH);
		digitalWrite(11, LOW);
		
#endif

#if 0		
		int diff = millis() - lastPassTime;
		if (diff > manualDelayTime)
		{
			uint16_t x = lastRCvalCH1;
			uint16_t y = lastRCvalCH2;
			if (x != 0 || y != 0)
			{
				// Send to Brugi if any movement
				Serial1.print("X");
				Serial1.print(x);
				Serial1.print(",");
				Serial1.print("Y");
				Serial1.print(y);
				Serial1.print(",");
			}
			lastPassTime = millis();
		}

#endif

		// Check if RC is still connected
		delay(1);
		rcTimeout++;
		if (rcTimeout > 1000)
		{
			onRC = false;
		}


		// Power check
		checkButtonAndVoltage();

	}

}

void Mode_Manual_NC()
{
	Serial.println("Mode_Manual_NC");
	while (!onAuto && !onRC)
	{
#ifdef DEBUG_MODE_ON
		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		digitalWrite(10, LOW);
		digitalWrite(11, HIGH);
		delay(500);
		digitalWrite(8, HIGH);
		digitalWrite(9, HIGH);
		digitalWrite(10, HIGH);
		digitalWrite(11, HIGH);
		
#endif
		// All power off
		digitalWrite(PixyPwrPIN, LOW);
		digitalWrite(BrugiPwrPIN, LOW);
		digitalWrite(VideoTrxPwrPIN, LOW);

		// Stop listening to RC-PWM 
		detachInterrupt(chan1);
		detachInterrupt(chan2);

		delay(500);
		sleepNow();


		// Power check  (needs to wake with interrupt to work)
		//checkButtonAndVoltage();

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

void setup_Serial()
{
	Serial.begin(BAUD_RATE);		// Usb
	// Serial1.begin(BAUD_RATE);	// Brugi (can't use serial1 with current interrupt pins setup)
}

void wakeUpNow()        // here the interrupt is handled after wakeup
{
	// execute code here after wake-up before returning to the loop() function
	Serial.begin(BAUD_RATE);
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
	detachInterrupt(chan3);  // int.4 = pin 19
	attachInterrupt(chan3, wakeUpNow, HIGH);

	sleep_mode();            // here the device is actually put to sleep
	// THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP

	sleep_disable();         // first thing after waking from sleep

	detachInterrupt(chan3);      // disables interrupt 4 on pin 19 so wakeUpNow is only run once

	// Start mode selector interrupt gets attached again
	attachInterrupt(chan3, calculatePWMch3, CHANGE);
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

uint16_t getWord()
{
	// Request register on position 0
	// do it twice and reorder the bits to get a 16bit int
	uint16_t w;
	uint8_t c;

	w = SPI.transfer(0);
	w <<= 8;
	c = SPI.transfer(0);
	w |= c;

	return w;
}

void initButtonAndVoltage()
{
	pinMode(7, OUTPUT);
	digitalWrite(7, HIGH);
	pinMode(A0, INPUT);
	pinMode(A5, INPUT);

}

void checkButtonAndVoltage()
{
	int diff = millis() - lastPowerCheck;
	if (diff > powerCheckTime) // check every 100ms or so
	{


	
#if 1
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
#ifdef DEBUG_MODE_ON
				Serial.println("button off");
#endif
				digitalWrite(7, LOW);
				delay(1000);
			}
		}

		if (analogRead(5) < 900)
		{
			// bat low, power off
			delay(1000);
#ifdef DEBUG_MODE_ON
			Serial.println("low voltage off");
#endif
			digitalWrite(7, LOW);
			delay(1000);
		}
	}
}