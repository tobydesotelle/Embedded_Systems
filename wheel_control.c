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
unsigned int right_speed;
unsigned int left_speed;
extern unsigned short line_detection;
extern unsigned char state;
unsigned char check_state;
PIDController pid;

/*
//#define R_MOTOR_STATE       (0x01)// 0 = off / 1 = on
//#define L_MOTOR_STATE       (0x02)// 0 = off / 1 = on
//#define R_MOTOR_DIR         (0x04)// 0 = forward / 1 = reverse
//#define L_MOTOR_DIR         (0x08)// 0 = forward / 1 = reverse
//#define R_MOTOR_DIR_CHANGED (0X10)// will be set if direction changed and safey flag not met
//#define R_MOTOR_DIR_CHANGED (0X20)// will be set if direction changed and safey flag not met
//#define R_MOTOR_SPD_CHANGED (0X40)//
//#define L_MOTOR_SPD_CHANGED (0X80)
Things needed delay when changing wheels
wheel selection
Timed wheel movement for consistancy


simple movement i.e.(forwards, backwards, CW, CCW)


*/
void move(unsigned short movement_bits){
  changed_check(movement_bits);//checks if motor direction has changed
  delay_motor();//delay if motor direction has changed
  process_wheels(movement_bits);//send move command if motor direction has changed or speed has changed
}
void changed_check(unsigned short movement_bits){
    if((motor_control_bits&0x0f)==movement_bits){//if the movement is the same
    //this is if the movement doesn't change the direction
  }
  else{//if a wheel has changed direction
    if(((motor_control_bits&R_MOTOR_DIR)!=(movement_bits&R_MOTOR_DIR))){
      motor_control_bits |= R_MOTOR_DIR_CHANGED ;
    }
    if(((motor_control_bits&L_MOTOR_DIR)!=(movement_bits&L_MOTOR_DIR))){
      motor_control_bits |= L_MOTOR_DIR_CHANGED ;
    }
  }
  
}
void delay_motor(){
  if(motor_control_bits&R_MOTOR_DIR_CHANGED||motor_control_bits&L_MOTOR_DIR_CHANGED){
    //start a timer
    if(motor_control_bits&R_MOTOR_DIR_CHANGED){
      motor_control_bits &= ~R_MOTOR_STATE;
      motor_control_bits &= ~R_MOTOR_DIR_CHANGED;
      RIGHT_FORWARD_SPEED = WHEEL_OFF;
      RIGHT_REVERSE_SPEED = WHEEL_OFF;
    }
    if(motor_control_bits&L_MOTOR_DIR_CHANGED){
      motor_control_bits &= ~L_MOTOR_STATE;
      motor_control_bits &= ~L_MOTOR_DIR_CHANGED;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      LEFT_REVERSE_SPEED = WHEEL_OFF;
    }
    if(TB0CCTL2!=CCIE){
      TB0CCR2 += TB0CCR2_INTERVAL;
      TB0CCTL2 &= ~CCIFG;//enable wheel delay timer
      TB0CCTL2 |= CCIE;
    }
  }
}
void process_wheels(unsigned short movement_bits){
  motor_control_bits &= 0x00;
  motor_control_bits |= movement_bits;
  if((motor_control_bits&WHEELS_ON==WHEELS_ON)/*&&(motor_control_bits&!WHEELS_DIR_CHANGED)*/){  
    switch((motor_control_bits&DIR_MASK)){//>>2
    case PIVOT_F_L:
      RIGHT_FORWARD_SPEED = right_speed;
      LEFT_FORWARD_SPEED = WHEEL_OFF;
      break;
    case BOTH_FORWARD:
      RIGHT_FORWARD_SPEED = right_speed;
      LEFT_FORWARD_SPEED = left_speed;
      break;
    case CCW:
      RIGHT_FORWARD_SPEED = right_speed;
      LEFT_REVERSE_SPEED = left_speed;
      break;
    case BOTH_REVERSE:
      RIGHT_REVERSE_SPEED = right_speed;
      LEFT_REVERSE_SPEED = left_speed;
      break;
    case CW:
      LEFT_FORWARD_SPEED = right_speed;
      RIGHT_REVERSE_SPEED = left_speed;
      break;
    default:
      stop();
      break;
    }
  }
}
void speed_change();
void direction_change(); //if direction change rise flag and start a timer 
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
  float Motor_offset = PIDController_Update(&pid,0.0f,measurment());
  set_left_speed(BASE_SPEED+(unsigned int)Motor_offset);
  set_right_speed(BASE_SPEED-(unsigned int)Motor_offset);
  
}

