
// Define Brushless PWM Mode, uncomment ONE setting
//Oppdateringsfrekvensen for PWM
#define PWM_32KHZ_PHASE  // Resolution 8 bit for PWM
//#define PWM_8KHZ_FAST    // Resolution 8 bit for PWM
//#define PWM_4KHZ_PHASE   // Resolution 8 bit for PWM
//#define NO_PWM_LOOP


// the prescaler is set so that timer0 ticks every 64 clock cycles, and the
// the overflow handler is called every 256 ticks.
#define MICROSECONDS_PER_TIMER1_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

// the whole number of milliseconds per timer0 overflow
#define MILLIS_INC_T1 (MICROSECONDS_PER_TIMER1_OVERFLOW / 1000)

#ifdef PWM_32KHZ_PHASE
#define CC_FACTOR 32
#endif
#ifdef PWM_4KHZ_PHASE
#define CC_FACTOR 4
#endif
#ifdef PWM_8KHZ_FAST
#define CC_FACTOR 8
#endif
#ifdef NO_PWM_LOOP
#define CC_FACTOR 1
#endif

#define interrupts() sei()
#define noInterrupts() cli()

// Hardware Abstraction for Motor connectors,
// DO NOT CHANGE UNLESS YOU KNOW WHAT YOU ARE DOING !!!
//aktivering av pwm(OCR = Output Compare Register)
#define PWM_A_MOTOR1 OCR2A
#define PWM_B_MOTOR1 OCR1B
#define PWM_C_MOTOR1 OCR1A

#define PWM_A_MOTOR0 OCR0A
#define PWM_B_MOTOR0 OCR0B
#define PWM_C_MOTOR0 OCR2B

#define N_SIN 256

uint8_t pwm_a_motor0 = 128;
uint8_t pwm_b_motor0 = 128;
uint8_t pwm_c_motor0 = 128;

uint8_t pwm_a_motor1 = 128;
uint8_t pwm_b_motor1 = 128;
uint8_t pwm_c_motor1 = 128;

int8_t pwmSinMotor[N_SIN];

#define motorNumberPitch 0
#define motorNumberYaw 1

uint16_t freq_1_count = 0; 
uint16_t freq_0_count = 0;
volatile uint8_t pinState;
volatile uint16_t motor_0_freq = 256;
volatile uint16_t motor_1_freq = 96;
volatile bool motor_0_update = false;
volatile bool motor_1_update = false;

#if 0
#define MOTORUPDATE_FREQ 1000                // in Hz, 1000 is default
//volatile uint16_t MOTORUPDATE_FREQ_0 = 500, MOTORUPDATE_FREQ_1 = 1000;
#define LOOPUPDATE_FREQ MOTORUPDATE_FREQ     // loop control sample rate equals motor update rate
#define DT_FLOAT (1.0/LOOPUPDATE_FREQ*1.024) // loop controller sample period dT
#define DT_INT_MS (1000/MOTORUPDATE_FREQ)    // dT, integer, (ms)
#define DT_INT_INV (MOTORUPDATE_FREQ)        // dT, integer, inverse, (Hz)

#define LOWPASS_K_FLOAT(TAU) (DT_FLOAT/(TAU+DT_FLOAT))
#endif