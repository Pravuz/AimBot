/*************************/
/* Config Structure      */
/*************************/

struct config_t
{
  uint8_t configSet;
  int32_t gyroPitchKp; 
  int32_t gyroPitchKi;   
  int32_t gyroPitchKd;
  int16_t accTimeConstant;
  int16_t angleOffsetPitch;   // angle offset, deg*100
  int16_t angleOffsetRoll;

  bool enableGyro;           // enable gyro attitude update
  bool enableACC;            // enable acc attitude update
  bool axisReverseZ;
  bool axisSwapXY;
  
  int8_t altSwAccTime;       // switch alternate Acc time: -1=always on, 0=off, 1=auxSW1, 2=auxSW2
  int16_t accTimeConstant2;  // alternate constant
  
  bool gyroCal;              // gyro calibration at startup 
  int16_t  gyrOffsetX;       // gyyro calibration offsets
  int16_t  gyrOffsetY;
  int16_t  gyrOffsetZ;
  
  int16_t  accOffsetX;       // acc calibration offsets
  int16_t  accOffsetY;
  int16_t  accOffsetZ;
  
  uint8_t crc8;
} config;

void setDefaultParameters()
{
  config.configSet = 0;
  config.gyroPitchKp = 70;
  config.gyroPitchKi = 6000;
  config.gyroPitchKd = 6250;
  config.accTimeConstant = 7;
  config.angleOffsetPitch = 0;
  config.angleOffsetRoll = 0;
  config.enableGyro=true;
  config.enableACC=true;
  config.axisReverseZ=true;
  config.axisSwapXY=false;
  config.altSwAccTime=0;
  config.accTimeConstant2 = 2;
  config.gyroCal = true;
  config.gyrOffsetX = 0;       // gyyro calibration offset
  config.gyrOffsetY = 0;
  config.gyrOffsetZ = 0;
  config.accOffsetX = 0;       // acc calibration offset
  config.accOffsetY = 0;
  config.accOffsetZ = 0;
  config.crc8 = 0;  
}

typedef struct PIDdata {
  int32_t   Kp, Ki, Kd;
} PIDdata_t;

PIDdata_t pitchPIDpar;

void initPIDs(void)
{
  pitchPIDpar.Kp = config.gyroPitchKp/10;
  pitchPIDpar.Ki = config.gyroPitchKi/1000;
  pitchPIDpar.Kd = config.gyroPitchKd/10/250;  // divide by 250 to keep compatibility to previous version
}

static int32_t pitchErrorSum = 0;
static int32_t pitchErrorOld = 0;

bool motorUpdate = false;
bool enableMotorUpdates = false;

// CRC definitions
#define POLYNOMIAL 0xD8  /* 11011 followed by 0's */
typedef uint8_t crc;

// motor drive

int8_t pwmSinMotor[256];

uint8_t freqCounter = 0;

uint8_t pwm_a_motor0 = 128;
uint8_t pwm_b_motor0 = 128;
uint8_t pwm_c_motor0 = 128;

uint8_t pwm_a_motor1 = 128;
uint8_t pwm_b_motor1 = 128;
uint8_t pwm_c_motor1 = 128;

// Variables for MPU6050
float gyroPitch;
float gyroRoll; //in deg/s

float resolutionDevider;
int16_t x_val;
int16_t y_val;
int16_t z_val;
static float pitchAngleSet = 0;
static float qLPPitch[3] = {0,0,0};

int count=0;

// Gimbal State
enum gimStateType {
 GIM_IDLE=0,      // no PID
 GIM_UNLOCKED,    // PID on, fast ACC
 GIM_LOCKED,      // PID on, slow ACC
 GIM_ERROR        // error condition
};

gimStateType gimState = (gimStateType)GIM_IDLE;
int stateCount = 0;

//*************************************
//
//  IMU
//
//*************************************
enum axisDef {
  ROLL,
  PITCH,
  YAW
};

typedef struct fp_vector {
  float X;
  float Y;
  float Z;
} t_fp_vector_def;

typedef union {
  float   A[3];
  t_fp_vector_def V;
} t_fp_vector;

//********************
// sensor orientation
//********************
typedef struct sensorAxisDef {
  char idx;
  int  dir;
} t_sensorAxisDef;

typedef struct sensorOrientationDef {
  t_sensorAxisDef Gyro[3];
  t_sensorAxisDef Acc[3];
} t_sensorOrientationDef;

t_sensorOrientationDef sensorDef = { 
    {{0, 1}, {1, 1}, {2, 1}},    // Gyro
    {{0, 1}, {1, 1}, {2, 1}}     // Acc
  };


static float gyroScale=0;

static int16_t gyroADC[3];
static int16_t accADC[3];

static t_fp_vector EstG;

static float accLPF[3] = {0.0,0.0,0.0};
static float accMag = 0;
static bool disableAccGtest = false;

static float AccComplFilterConst = 0;  // filter constant for complementary filter

static int16_t acc_25deg = 25;      //** TODO: check

static int32_t angle[2]    = {0,0};  // absolute angle inclination in multiple of 0.01 degree    180 deg = 18000

//static float angleOffsetRoll_f = 0;
static float angleOffsetPitch_f = 0;

static int32_t angleOffsetRoll = 0;
static int32_t angleOffsetPitch = 0;
