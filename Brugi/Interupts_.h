#include <avr\interrupt.h>


/*interupt for motorupdate. every 31.5us.
ticker hver gang TIMER1 overflow slår inn. ticker hver gang phase correct PWM trekantpuls
når bunnen.*/
ISR(TIMER1_OVF_vect)
{
	if(!motor_0_update) freq_0_count++;
	if (freq_0_count == motor_0_freq)
	{
		PWM_A_MOTOR0 = pwm_a_motor0;
		PWM_B_MOTOR0 = pwm_b_motor0;
		PWM_C_MOTOR0 = pwm_c_motor0;

		freq_0_count = 0;
		motor_0_update = true;
	}

	if (!motor_1_update) freq_1_count++;
	if (freq_1_count == motor_1_freq)
	{
		PWM_A_MOTOR1 = pwm_a_motor1;
		PWM_B_MOTOR1 = pwm_b_motor1;
		PWM_C_MOTOR1 = pwm_c_motor1;

		freq_1_count = 0;
		motor_1_update = true;
	}

}

