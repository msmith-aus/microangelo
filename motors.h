#include <stdint.h>
// #include <wiringPi.h>
// #include <ncurses.h>

// #define MS0_1 8 
// #define MS1_1 9 
// #define MS2_1 7 
// #define MS0_2 0 
// #define MS1_2 2
// #define MS2_2 3 

// // Use the command gpio readall to get WPi pin values

// #define MOTOR_X_STEP 29  
// #define MOTOR_Y_STEP 25

// #define MOTOR_X_DIR 28 
// #define MOTOR_Y_DIR 24 

// #define LOGIC_X 29
// #define LOGIC_Y 30

// #define ENABLE_X 27
// #define ENABLE_Y 23

//// PICO PINS ////
#define MOTOR_X_EN  13
#define MOTOR_X_M0  12
#define MOTOR_X_M1  11
#define MOTOR_X_M2  10
#define MOTOR_X_STEP  9
#define MOTOR_X_DIR  8
#define X_POS  0

#define MOTOR_Y_EN  28
#define MOTOR_Y_M0  27
#define MOTOR_Y_M1  26
#define MOTOR_Y_M2  22
#define MOTOR_Y_STEP  21
#define MOTOR_Y_DIR  20
#define Y_POS  0

#define MOTOR_Z_EN  2
#define MOTOR_Z_M0  3
#define MOTOR_Z_M1  4
#define MOTOR_Z_M2  5
#define MOTOR_Z_STEP  6
#define MOTOR_Z_DIR  7

#define STEPS_PER_REV 400
#define LEAD_SCREW_PITCH 1 // 1mm
#define LINEAR_STEP 0.0025 // 0.0025mm translational movement


#define FORWARD 1
#define BACKWARD 0

#define STEP_DELAY 100 //How long we are keeping the step pin high (us)
#define SPEED 2000 // Standard speed our motors will run (us) i.e 2000us / step




// Struct to store a motor state //
typedef struct {
	int dirPin;
	int step;
	int enable;
} Motor;

// Struct to store a servo state //
typedef struct {
	int state;

} Servo;


void drive_motor(Motor* motor, int speed, int dir, int steps); 


