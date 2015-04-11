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
#define USBconnectedPIN		26
#define USBpulldownPIN		28
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
enum Aimbot_Mode
{ 
	SLEEP_MODE,
	AUTO,
	MANUAL,
}currentMode;

// PWM-in related vars
int lastRCvalCH1 = 0;  // Thro (min = 1052, max = 1912), TH_HOLD = 952
int lastRCvalCH2 = 0;  // L/R (Left = 1916) (RIGHT = 1052)
int lastRCvalCH3 = 0;  // GEAR (1052 = 0, 1912 = 1, ) needs ACRO-MODE
int lastRCvalCH4 = 0;  // ELEV (UP = 1916, DOWN = 1052)

//timing, volatile due to interrupts
volatile unsigned long oldtime1 = 0;
volatile int timepassed1;
volatile unsigned long oldtime2 = 0;
volatile int timepassed2;
volatile unsigned long oldtime3 = 0;
volatile int timepassed3;
volatile unsigned long oldtime4 = 0;
volatile int timepassed4;

// Take picture routine
int lastPictureTime = 0;
bool isDSLR = false;

// Mode/loop related
volatile unsigned long lastPassTime = 0;

// Power check
volatile unsigned long lastPowerCheck = 0;

String inString = "";  // buffer for PC communication

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
communicateWithPC();
}
void communicateWithPC()
{
	if (Serial.available() > 0)
	{
		inString += (char)Serial.read(); // Read to bufferstring

		if (inString.length() >= 5) // All commands are 5 chars long
		{
			if (inString == "setup") // Recieve new settings
			{
				inString = "";
				int i = 0;
				int settings[22];
				while (i <= 21)
				{
					while (Serial.available() < 1){} // wait for next var
					char last = Serial.read();
					if (last == ',') // comma signals next variable
					{
						settings[i] = inString.toInt();
						inString = "";
						i++;
					}
					else inString += last;
				}

				isDSLR = settings[0]; // no casting, a bool is really a uint8 in disguise
				CAM_BTN_DELAY = settings[1];
				CAM_TRIGGER_DELAY = settings[2];
				CAM_FOCUS_DELAY = settings[3];
				LOOP_TIME = settings[4];
				PWR_CHECK_INTERVAL = settings[5];
				xRCmin = settings[6];
				xRCmax = settings[7];
				xRCMAPmin = settings[8];
				xRCMAPmax = settings[9];
				yRCmin = settings[10];
				yRCmax = settings[11];
				yRCMAPmin = settings[12];
				yRCMAPmax = settings[13];
				xVECT_INmin = settings[14];
				xVECT_INmax = settings[15];
				xVECT_OUTmin = settings[16];
				xVECT_OUTmax = settings[17];
				yVECT_INmin = settings[18];
				yVECT_INmax = settings[19];
				yVECT_OUTmin = settings[20];
				yVECT_OUTmax = settings[21];
				inString = "";

			}
			else if (inString == "sendx") // Send current settings back
			{
				inString = "";
				Serial.print(isDSLR, DEC); Serial.print(",");
				Serial.print(CAM_BTN_DELAY, DEC); Serial.print(",");
				Serial.print(CAM_TRIGGER_DELAY, DEC); Serial.print(",");
				Serial.print(CAM_FOCUS_DELAY, DEC); Serial.print(",");
				Serial.print(LOOP_TIME, DEC); Serial.print(",");
				Serial.print(PWR_CHECK_INTERVAL, DEC); Serial.print(",");
				Serial.print(xRCmin, DEC); Serial.print(",");
				Serial.print(xRCmax, DEC); Serial.print(",");
				Serial.print(xRCMAPmin, DEC); Serial.print(",");
				Serial.print(xRCMAPmax, DEC); Serial.print(",");
				Serial.print(yRCmin, DEC); Serial.print(",");
				Serial.print(yRCmax, DEC); Serial.print(",");
				Serial.print(yRCMAPmin, DEC); Serial.print(",");
				Serial.print(yRCMAPmax, DEC); Serial.print(",");
				Serial.print(xVECT_INmin, DEC); Serial.print(",");
				Serial.print(xVECT_INmax, DEC); Serial.print(",");
				Serial.print(xVECT_OUTmin, DEC); Serial.print(",");
				Serial.print(xVECT_OUTmax, DEC); Serial.print(",");
				Serial.print(yVECT_INmin, DEC); Serial.print(",");
				Serial.print(yVECT_INmax, DEC); Serial.print(",");
				Serial.print(yVECT_OUTmin, DEC); Serial.print(",");
				Serial.print(yVECT_OUTmax, DEC); Serial.print(",");
				Serial.println(""); // prints newline so it's more convenient when using debug console
			}
			else
			{
				inString = "";  // Serial might be out of sync, flush bufferstring
			}
			while (Serial.available() > 0)
			{
				Serial.read(); // Flush serial in
			}
		}
	}

}
