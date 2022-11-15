/*
  Description: This file contains the Main Routine - "While" Operating System
  

  Tobias Desotelle
  Team: Magic Smoke
  October 14 2022
  Built with IAR Embedded Workbench Version: (7.21.1)
*/


//Coding Check List
//create adc readout menu
//fix measurment function for edge cases
//Build pid debuging display
//Make pid_update updated from timer
//Menu Function
//Start using Dac
//fix Processbuffers to rolling


#include "macros.h"

// Global Variables
extern char display_line[DISPLAYLINES][DISPLAYCHARS];
extern char *display[DISPLAYLINES];


extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

extern char process_buf_rx[PROCESS_BUF_LENGTH];
extern char process_buf_tx[PROCESS_BUF_LENGTH];

//volatile unsigned int time50;//50ms
volatile unsigned int time_interval50;//50ms

unsigned char state;

volatile unsigned short motor_control_bits;
volatile unsigned char switch_control;
volatile unsigned short timer_bits;
volatile unsigned short serial_bits;
volatile unsigned short display_bits;

unsigned char baud; 
int *test;
void main(void){
  PM5CTL0 &= ~LOCKLPM5;// Disable the GPIO power-on default high-impedance mode to activate
  Master_Init();
  BACKLIGHT = 30000;
  while(!((display_bits) & (Splash_bit))){
  }
  P3OUT |= IOT_EN_CPU;
  //test=(int *)malloc(sizeof(int)*10000);
  //int test[1000];
  //test[0]=1;
//  malloc(10);
  //serial_bits= 1;
  while(ALWAYS){
    menu_state_machine();
    process_switches();
    Display_Process();
    if(serial_bits & UCA1_TX){
      serial_bits &= UCA1_TX;
      UCA1TXBUF = '\0';
    }
      
    P3OUT ^= TEST_PROBE;   // Change State of TEST_PROBE OFF
    //Wheels_Process();         //State machine for line following 
  }
}

  