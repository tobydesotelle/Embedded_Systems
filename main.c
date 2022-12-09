/*
  Description: This file contains the Main Routine - "While" Operating System
  

  Tobias Desotelle
  Team: Magic Smoke
  October 14 2022
  Built with IAR Embedded Workbench Version: (7.21.1)

  Project 10 v1.0
*/


//Coding Check List
//create adc readout menu
//fix measurment function for edge cases
//Build pid debuging display


//Make pid_update updated from timer
//
//Make serial lighter
//faster ADC
//
//build ping wifi server

#include "macros.h"

volatile unsigned short motor_control_bits;
volatile unsigned char switch_control;
volatile unsigned short timer_bits;
volatile unsigned short serial_bits;
volatile unsigned short display_bits;
extern short timing;
extern PIDController pid;
int wheel_test = 0;
void main(void){
  PM5CTL0 &= ~LOCKLPM5;// Disable the GPIO power-on default high-impedance mode to activate
  Master_Init();
  PIDController_Init(&pid);
  BACKLIGHT = 0; // Backlight control for late night programming
  while(!((display_bits) & (Splash_bit))){}//Wait for 2 seconds to boot IOT 
  IOT_main();//uncommet when IOT Works
  line_calibration();
  timing=1;
  while(ALWAYS){
    //menu_state_machine();
    process_switches();
    Command_state();
    Display_Process();
    //P3OUT ^= TEST_PROBE;   	// Change State of TEST_PROBE OFF
    diplay_pad();
  }
}
  