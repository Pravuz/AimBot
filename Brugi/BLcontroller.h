#include <Arduino.h>
#include <avr\interrupt.h>


/*interupt for motorupdate. every 31.5us.
ticker hver gang TIMER1 overflow slår inn. ticker hver gang phase correct PWM trekantpuls
når bunnen.*/
ISR(TIMER1_OVF_vect)
{
	freqCounter++;
	if (freqCounter == (CC_FACTOR * 1000 / MOTORUPDATE_FREQ))
	{
		freqCounter = 0;

		PWM_A_MOTOR0 = pwm_a_motor0;
		PWM_B_MOTOR0 = pwm_b_motor0;
		PWM_C_MOTOR0 = pwm_c_motor0;

		PWM_A_MOTOR1 = pwm_a_motor1;
		PWM_B_MOTOR1 = pwm_b_motor1;
		PWM_C_MOTOR1 = pwm_c_motor1;

		// update event
		motorUpdate = true;
	}

	if ((freqCounter & 0x01f) == 0) TIMER0_isr_emulation();
}

/*Initialize motorcontroller
Setter pinner og velger frekvens*/
void initBlController()
{
	pinMode(3, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);

#ifdef PWM_8KHZ_FAST
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM10);
	TCCR0B = _BV(CS01);
	TCCR1A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM10);
	TCCR1B = _BV(WGM12) | _BV(CS11);
	TCCR2A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM21) | _BV(WGM20);
	TCCR2B = _BV(CS21);
#endif

#ifdef PWM_32KHZ_PHASE
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);
	TCCR0B = _BV(CS00);
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
	TCCR1B = _BV(CS10);
	TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
	TCCR2B = _BV(CS20);
#endif

#ifdef PWM_4KHZ_PHASE
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);
	TCCR0B = _BV(CS01);
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
	TCCR1B = _BV(CS11);
	TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
	TCCR2B = _BV(CS21);
#endif

	// enable Timer 1 interrupt
	TIMSK1 |= _BV(TOIE1);

	// disable arduino standard timer interrupt
	TIMSK0 &= ~_BV(TOIE1);

	sei();

	// Enable Timer1 Interrupt for Motor Control
	OCR2A = 0;  //11  APIN
	OCR2B = 0;  //D3
	OCR1A = 0;  //D9  CPIN
	OCR1B = 0;  //D10 BPIN
	OCR0A = 0;  //D6
	OCR0B = 0;  //D5 
}

void calcSinusArray()
{
	for (int i = 0; i<N_SIN; i++)
	{
		pwmSinMotor[i] = sin(2.0 * i / N_SIN * 3.14159265) * 127.0;
	}
}

void initMotorStuff()
{
	cli();
	calcSinusArray();
	sei();
}

void MoveMotorPosSpeed(uint8_t motorNumber, int MotorPos, uint16_t maxPWM)
{
	uint16_t posStep;
	int16_t pwm_a;
	int16_t pwm_b;
	int16_t pwm_c;

	// fetch pwm from sinus table
	posStep = MotorPos & 0xff;
	pwm_a = pwmSinMotor[(uint8_t)posStep];
	pwm_b = pwmSinMotor[(uint8_t)(posStep + 85)];
	pwm_c = pwmSinMotor[(uint8_t)(posStep + 170)];

	// apply power factor
	
	pwm_a = maxPWM * pwm_a;
	pwm_a = pwm_a >> 8;
	pwm_a += 128;
		
	pwm_b = maxPWM * pwm_b;
	pwm_b = pwm_b >> 8;
	pwm_b += 128;
		
	pwm_c = maxPWM * pwm_c;
	pwm_c = pwm_c >> 8;
	pwm_c += 128;

	// set motor pwm variables
	if (motorNumber == 0)
	{
		pwm_a_motor0 = (uint8_t)pwm_a;
		pwm_b_motor0 = (uint8_t)pwm_b;
		pwm_c_motor0 = (uint8_t)pwm_c;
	}

	if (motorNumber == 1)
	{
		pwm_a_motor1 = (uint8_t)pwm_a;
		pwm_b_motor1 = (uint8_t)pwm_b;
		pwm_c_motor1 = (uint8_t)pwm_c;
	}
}

void motorPowerOff() 
{
	/*Slår av power og setter farten/pos til 0*/
	MoveMotorPosSpeed(motorNumberPitch, 0, 0);
	MoveMotorPosSpeed(motorNumberYaw, 0, 0);
}