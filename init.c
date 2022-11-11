//------------------------------------------------------------------------------
//
//  Description: This file contains the all of the intilzation functions.
//
//
//  Tobias Desotelle
//  September 20 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//------------------------------------------------------------------------------
#include "macros.h"

extern char display_line[DISPLAYLINES][DISPLAYCHARS];
extern char *display[DISPLAYLINES];
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;

void Master_Init(void){
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_LEDs();
  Init_ADC();
  Init_Serial_UCA0(BAUD115200);
  Init_Serial_UCA1(BAUD115200);
  Init_Display();
  //#define BAUD115200      (0x00)
  //#define BAUD460800      (0x01)
}
void Init_Conditions(void){
//------------------------------------------------------------------------------

  int i;
  for(i=DISPLAYSTART;i<DISPLAYCHARS;i++){
    display_line[DISPLAY0][i] = RESET_STATE;
    display_line[DISPLAY1][i] = RESET_STATE;
    display_line[DISPLAY2][i] = RESET_STATE;
    display_line[DISPLAY3][i] = RESET_STATE;
  }
  display_line[DISPLAY0][DISPLAYEND] = RESET_STATE;
  display_line[DISPLAY1][DISPLAYEND] = RESET_STATE;
  display_line[DISPLAY2][DISPLAYEND] = RESET_STATE;
  display_line[DISPLAY3][DISPLAYEND] = RESET_STATE;

  display[DISPLAY0] = &display_line[DISPLAY0][RESET_STATE];
  display[DISPLAY1] = &display_line[DISPLAY1][RESET_STATE];
  display[DISPLAY2] = &display_line[DISPLAY2][RESET_STATE];
  display[DISPLAY3] = &display_line[DISPLAY3][RESET_STATE];
  update_display = RESET_STATE;


// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}
void enable_interrupts(void){
  __bis_SR_register(GIE);     // enable interrupts
//  asm volatile ("eint \n");
}
void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}
