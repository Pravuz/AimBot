
// Define Brushless PWM Mode, uncomment ONE setting
//Oppdateringsfrekvensen for PWM
#define PWM_32KHZ_PHASE  // Resolution 8 bit for PWM
//#define PWM_8KHZ_FAST    // Resolution 8 bit for PWM
//#define PWM_4KHZ_PHASE   // Resolution 8 bit for PWM
//#define NO_PWM_LOOP

#define _INLINE_		__attribute__( ( always_inline ) ) inline
#define _NO_INLINE_		__attribute__( ( noinline ) )

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

// MPU Address Settings
#define MPU6050_ADDRESS_AD0_LOW     0x68 // default for InvenSense evaluation board
#define MPU6050_ADDRESS_AD0_HIGH    0x69 // Drotek MPU breakout board
#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_HIGH

// Do not change for now
#define MPU6050_GYRO_FS MPU6050_GYRO_FS_250  // +-250,500,1000,2000 deg/s
#define MPU6050_DLPF_BW MPU6050_DLPF_BW_256  // 5,10,20,42,98,188,256 Hz

#define interrupts() sei()
#define noInterrupts() cli()

#define I2C_SPEED 800000L   //800kHz ultra fast mode
#define POUT_FREQ 25      // rate of ACC print output in Hz, 25 Hz is default
#define TRACE_OUT_FREQ 10 // rate of Trace Outoput in Hz, 10Hz is default 
#define LOCK_TIME_SEC 5   // gimbal fast lock time at startup 


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

#define motorNumberPitch 0
#define motorNumberYaw 1

#define MOTORUPDATE_FREQ 1000                // in Hz, 1000 is default
#define LOOPUPDATE_FREQ MOTORUPDATE_FREQ     // loop control sample rate equals motor update rate
#define DT_FLOAT (1.0/LOOPUPDATE_FREQ*1.024) // loop controller sample period dT
#define DT_INT_MS (1000/MOTORUPDATE_FREQ)    // dT, integer, (ms)
#define DT_INT_INV (MOTORUPDATE_FREQ)        // dT, integer, inverse, (Hz)

#define LOWPASS_K_FLOAT(TAU) (DT_FLOAT/(TAU+DT_FLOAT))