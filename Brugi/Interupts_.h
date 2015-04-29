#include <avr\interrupt.h>




void TIMER0_isr_emulation(void) {

	unsigned long m = timer1_millis;

	m += MILLIS_INC_T1;
	timer1_millis = m;

}



/*interupt for motorupdate. every 31.5us.
ticker hver gang TIMER1 overflow slår inn. ticker hver gang phase correct PWM trekantpuls 
når bunnen.*/
ISR(TIMER1_OVF_vect)
{

	if (!rc_mode)
	{

		freqCounter_0++;
		freqCounter_1++;
		if (freqCounter_0 >= (CC_FACTOR * 1000 / MOTORUPDATE_FREQ_0))
		{
			freqCounter_0 = 0;

			PWM_A_MOTOR0 = pwm_a_motor0;
			PWM_B_MOTOR0 = pwm_b_motor0;
			PWM_C_MOTOR0 = pwm_c_motor0;

			// update event
			motorUpdate_0 = true;
		}

		if (freqCounter_1 >= (CC_FACTOR * 1000 / MOTORUPDATE_FREQ_1))
		{
			freqCounter_1 = 0;

			PWM_A_MOTOR1 = pwm_a_motor1;
			PWM_B_MOTOR1 = pwm_b_motor1;
			PWM_C_MOTOR1 = pwm_c_motor1;

			// update event
			motorUpdate_1 = true;
		}

		// care for standard timers every 1 ms
		if ((freqCounter_0 & 0x01f) == 0) {
			TIMER0_isr_emulation();
		}
	}
	else
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

		// care for standard timers every 1 ms
		if ((freqCounter & 0x01f) == 0) {
			TIMER0_isr_emulation();
		}
	}
}



//unsigned long microsT1() {
//
//	unsigned long m;
//
//	uint8_t oldSREG = SREG;
//	uint8_t f;
//
//	cli();
//	m = timer1_millis;
//	f = (freqCounter & 0x01f) << 3;
//	SREG = oldSREG;
//
//	return ((m << 8) + f) * (64 / clockCyclesPerMicrosecond());
//}

