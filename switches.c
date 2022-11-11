//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to process if a switch has   
//      been pressed.
//
//  Tobias Desotelle
//  September 20 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//--------------------------------------------------------------------------

#include "macros.h"
extern volatile unsigned char switch_control;
extern volatile unsigned short timer_bits;

volatile unsigned int sw1_timer;
volatile unsigned int sw2_timer;
//Switch 1 
#pragma vector=PORT4_VECTOR
__interrupt void switchP4_interrupt(void){
  if (P4IFG & SW1) {
    P4IFG &= ~SW1; // IFG SW1 cleared
    switch_control |= SW1_PRESSED;
    switch_control &= ~SW1_RELEASED;
    switch_control |= SW1_TOGGLED;
    //sw1_timer=RESET_STATE;
    TB0CCTL1 |= CCIE; // starts debounce timer
  }
}
// Switch 2 
#pragma vector=PORT2_VECTOR
__interrupt void switchP2_interrupt(void){
  
  if (P2IFG & SW2) {
    P2IFG &= ~SW2; // IFG SW1 cleared
    switch_control |= SW2_PRESSED;
    switch_control &= ~SW1_RELEASED;
    switch_control ^= SW2_TOGGLED;
    //sw2_timer=RESET_STATE;
    TB0CCTL1 |= CCIE; //starts debounce timer
  }
}

void process_switches(){
  if(sw1_timer>=TIME20){
    sw1_timer = RESET_STATE;
    switch_control &= ~SW1_PRESSED;
    switch_control |= SW1_RELEASED;
  }
  if(sw2_timer>=TIME20){
    sw2_timer = RESET_STATE;
    switch_control &= ~SW2_PRESSED;
    switch_control |= SW2_RELEASED;
    
  }
  if(switch_control==0){
    switch_control |= SW1_RELEASED;
    switch_control |= SW2_RELEASED;
  }
//  if((switch_control&SW1_RELEASED)&&(switch_control&SW1_PRESSED)){
//    switch_control &= ~SW1_PRESSED;
//    switch_control |= SW1_RELEASED;
//  }
//  if((switch_control&SW2_RELEASED)&&(switch_control&SW2_PRESSED)){
//    switch_control &= ~SW2_PRESSED;
//    switch_control |= SW2_RELEASED;
//  }
  
  if((switch_control&SW1_RELEASED)&&(switch_control&SW2_RELEASED)){
    TB0CCTL1 &= ~CCIE; //Turn off debounce 
  }
}



