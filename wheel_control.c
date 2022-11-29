//------------------------------------------------------------------------------
//
//  Description: This file contains all of the functions that control the wheel
//      movement and state machines for coordnadte movement.
//
//  Tobias Desotelle
//  September 20 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//-------------------------------------------------------------------------
#include "macros.h"
// use state machine for setting movement and delays.

extern volatile unsigned short motor_control_bits;
extern volatile unsigned short timer_bits;
unsigned int right_speed;
unsigned int left_speed;
extern unsigned short line_detection;
unsigned char state;
unsigned char check_state;
PIDController pid;
char right_wheel_state;//Right and left wheel controller
char left_wheel_state;
#define IDLE		(0x00)
#define Configure_wheel (0x01)
#define Forward_start	(0x02)
#define Reverse_stare	(0x03)
#define Forward_adjust	(0x04)
#define Reverse_adjust	(0x05)
#define Intiate_stop	(0x06)
#define Stop_hold	(0x07)

void right_wheel_statemachine(){
  switch(right_wheel_state){
  case IDLE:
    if(motor_control_bits & R_MOTOR_STATE)right_wheel_state = Configure_wheel;
    break;
  case Configure_wheel:
    //set_speed(8000);
    if(!(motor_control_bits & R_MOTOR_DIR))right_wheel_state = Reverse_adjust;
    else right_wheel_state =  Forward_adjust;
    break;
  case Forward_adjust:
    RIGHT_FORWARD_SPEED = right_speed;
    if(RIGHT_FORWARD_SPEED == 0 || !(motor_control_bits & R_MOTOR_STATE))right_wheel_state = Intiate_stop;
    else if( motor_control_bits & R_MOTOR_DIR_CHANGED){
      right_wheel_state = Intiate_stop;
      motor_control_bits &= ~R_MOTOR_DIR_CHANGED;
    }
    break;
  case Reverse_adjust:
    RIGHT_REVERSE_SPEED = right_speed;
    if(RIGHT_REVERSE_SPEED == 0 || !(motor_control_bits & R_MOTOR_STATE))right_wheel_state = Intiate_stop;
    else if( motor_control_bits & R_MOTOR_DIR_CHANGED){
      right_wheel_state = Intiate_stop;
      motor_control_bits &= ~R_MOTOR_DIR_CHANGED;
    }
    break;
  case Intiate_stop:
    RIGHT_FORWARD_SPEED = 0;
    RIGHT_REVERSE_SPEED = 0;
    motor_control_bits &= ~R_MOTOR_STATE;
    TB2CCTL0 |= CCIE;
    right_wheel_state = Stop_hold;
  case Stop_hold:
    if(timer_bits & Change_wheel_state)right_wheel_state = IDLE; //BUG here or something
    break;
  default:
    right_wheel_state = IDLE;
    break;
  }
  
}
void left_wheel_statemachine(){
  switch(left_wheel_state){
  case IDLE:
    if(motor_control_bits & R_MOTOR_STATE)left_wheel_state = Configure_wheel;
    break;
  case Configure_wheel:
    //set_speed(8000);
    if(!(motor_control_bits & L_MOTOR_DIR))left_wheel_state =  Reverse_adjust;
    else left_wheel_state = Forward_adjust;
    break;
  case Forward_adjust:
    LEFT_FORWARD_SPEED = left_speed;
    if(LEFT_FORWARD_SPEED == 0 || !(motor_control_bits & L_MOTOR_STATE))left_wheel_state = Intiate_stop;
    else if( motor_control_bits & L_MOTOR_DIR_CHANGED){
      left_wheel_state = Intiate_stop;
      motor_control_bits &= ~L_MOTOR_DIR_CHANGED;
    }
    break;
  case Reverse_adjust:
    LEFT_REVERSE_SPEED = left_speed;
    if(LEFT_REVERSE_SPEED == 0 || !(motor_control_bits & L_MOTOR_STATE))left_wheel_state = Intiate_stop;
    else if( motor_control_bits & L_MOTOR_DIR_CHANGED){
      left_wheel_state = Intiate_stop;
      motor_control_bits &= ~L_MOTOR_DIR_CHANGED;
    }
    break;
  case Intiate_stop:
    LEFT_FORWARD_SPEED = 0;
    LEFT_REVERSE_SPEED = 0;
    motor_control_bits &= ~L_MOTOR_STATE;
    TB2CCTL0 |= CCIE;
    left_wheel_state = Stop_hold;
  case Stop_hold:
    if(timer_bits & Change_wheel_state)left_wheel_state = IDLE;
    break;
  default:
    left_wheel_state = IDLE;
    break;
  }
  
}
void move(unsigned short movement_bits){
  motor_control_bits = movement_bits; 
  if((motor_control_bits & R_MOTOR_DIR) != (movement_bits & R_MOTOR_DIR)) motor_control_bits |= R_MOTOR_DIR_CHANGED;
  if((motor_control_bits & L_MOTOR_DIR) != (movement_bits & L_MOTOR_DIR)) motor_control_bits |= L_MOTOR_DIR_CHANGED;
  //else 
  left_wheel_statemachine();
  right_wheel_statemachine();
}
void set_speed(unsigned int speed){
  right_speed=speed;
  left_speed=speed;
}
void set_right_speed(unsigned int speed){
  right_speed=speed;
}
void set_left_speed(unsigned int speed){
  left_speed=speed;
}
void enable_ramp_to(unsigned int setpoint){
  if(setpoint>BACKLIGHT)ramp_up_to(setpoint);
  
}
void ramp_up_to(unsigned int setpoint){
  //enable timer 1 to increase pwm value
  TB1CCTL0 &= ~CCIFG; // CCR0 enable interrupt
  TB1CCTL0 |= CCIE; // CCR0 enable interrupt
  //speed=setpoint;
}
void stop(){
  set_speed(0);
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}
void Wheels_Process(void){
  //------------------------------------------------------
  process_detectors();
  switch(state){
  case IDLE: // IDLE
    stop();
    set_speed(BASE_SPEED);
    idle_case(START);
    break; 
  case START: 
    move(FORWARD);
    do_for(&state,IDLE,100);
    search(LINE_FOUND);
    break;
  case LINE_FOUND: 
    stop();
    do_for(&state,BACK_UP,50);
    //P6OUT |=GRN_LED;
    break;
  case BACK_UP: 
    move(FORWARD);
    do_for(&state,ALIGN,10);
    break;
  case ALIGN: //Spin until both sensor read strong 
    set_speed(BASE_SPEED);
    move(CW);
    if(line_detection>=0X44){
      state = PID;
      PIDController_Init(&pid);
    }
    //check_state=START;
    do_for(&state,IDLE,1000);
    break;
  case PID : // Adjust Reverse
    move(FORWARD);
    pid_control();
    do_for(&state,IDLE,1000);
    break;  
  case Stop: // Look for End of Stop Time
    break; 
  default:
    state = IDLE;
    break;
  }
}
void pid_control(){
  //Want to update pid loop and set output
  int Motor_offset = PIDController_Update(&pid,0,measurment());
  set_left_speed(BASE_SPEED-(unsigned int)Motor_offset);
  set_right_speed(BASE_SPEED+(unsigned int)Motor_offset);
  
}
void pid_test(){
  
  
}

