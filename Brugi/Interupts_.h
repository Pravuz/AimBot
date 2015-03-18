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

