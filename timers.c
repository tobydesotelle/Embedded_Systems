/*
  Description: This file contains the all of the intilzation functions.
 

  Tobias Desotelle
  Team: Magic Smoke
  October 14 2022
  Built with IAR Embedded Workbench Version: (7.21.1)
*/
#include "macros.h"
void Init_Timers(void){
  Init_Timer_B0();
  Init_Timer_B1();
  Init_Timer_B2();
  Init_Timer_B3();
}
void Init_Timer_B0(void){
  TB0CTL = TBSSEL__SMCLK;       // SMCLK source
  TB0CTL |= TBCLR;              // Resets TB0R, clock divider, count direction
  TB0CTL |= MC__CONTINOUS;      // Continuous up
  TB0CTL |= ID__8;              // Divide clock by 8
  TB0EX0 = TBIDEX__8;           // Divide clock by an additional 8
  
  TB0CCR0 = TB0CCR0_INTERVAL;   // CCR0
  TB0CCTL0 &= ~CCIFG;           // CCR0 clear flag
  TB0CCTL0 |= CCIE;             // CCR0 enable interrupt
  
  //TB0CCR1 = TB0CCR1_INTERVAL;   // CCR1 
  //TB0CCTL1 &= ~CCIFG;         // CCR0 enable interrupt
  //TB0CCTL1 |= CCIE;           // CCR1 enable interrupt
  
  TB0CCR2 = TB0CCR2_INTERVAL; // CCR2 
  TB0CCTL2 &= ~CCIFG;         // CCR0 clear flag
  //TB0CCTL2 |= CCIE;           // CCR2 enable interrupt
  
  TB0CTL &= ~TBIE; // Disable Overflow Interrupt
  TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}
void Init_Timer_B1(void){
  TB1CTL = TBSSEL__SMCLK; // SMCLK source
  TB1CTL |= TBCLR; // Resets TB0R, clock divider, count direction
  TB1CTL |= MC__CONTINOUS; // Continuous up
  TB1CTL |= ID__8; // Divide clock by 8
  TB1EX0 = TBIDEX__8; // Divide clock by an additional 8
  
  TB1CCR0 = TB1CCR0_INTERVAL; // CCR0
  TB1CCTL0 &= ~CCIFG; // CCR0 enable interrupt
  TB1CCTL0 |= CCIE; // CCR0 enable interrupt
  
  //TB1CCR1 = TB0CCR1_INTERVAL; // CCR1 
  
  
  //TB0CCTL1 &= ~CCIFG; // CCR0 enable interrupt
  // TB0CCTL1 |= CCIE; // CCR1 enable interrupt
  
  TB1CCR2 = TB0CCR2_INTERVAL; // CCR2 
  //TB1CCTL2 |= CCIE; // CCR2 enable interrupt
  
  TB1CTL &= ~TBIE; // Disable Overflow Interrupt
  TB1CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}
void Init_Timer_B2(void){
  TB2CTL = TBSSEL__SMCLK; // SMCLK source
  TB2CTL |= TBCLR; // Resets TB0R, clock divider, count direction
  TB2CTL |= MC__CONTINOUS; // Continuous up
  TB2CTL |= ID__8; // Divide clock by 8
  TB2EX0 = TBIDEX__8; // Divide clock by an additional 8
  
  TB2CCR0 = TB0CCR0_INTERVAL; // CCR0
  //TB0CCTL0 &= ~CCIFG; // CCR0 enable interrupt
  //TB0CCTL0 |= CCIE; // CCR0 enable interrupt
  
  TB2CCR1 = TB0CCR1_INTERVAL; // CCR1 
  //------------------------------------
  
  //TB0CCTL1 &= ~CCIFG; // CCR0 enable interrupt
  // TB0CCTL1 |= CCIE; // CCR1 enable interrupt
  
  TB2CCR2 = TB0CCR2_INTERVAL; // CCR2 
  TB2CCTL2 |= CCIE; // CCR2 enable interrupt
  
  TB2CTL &= ~TBIE; // Disable Overflow Interrupt
  TB2CTL &= ~TBIFG; // Clear Overflow Interrupt flag
}
void Init_Timer_B3(void) {
  /*
  Timer B3 will control the pwm signals using 1MHz CLK
  */
  TB3CTL = TBSSEL__SMCLK; // SMCLK 
  TB3CTL |= TBCLR;        // Resets TB3R, clock divider, count direction
  //TB3CTL |= ID__8;
  TB3CTL |= MC__UP;       // Up Mode
  
  
  TB3CCR0 = WHEEL_PERIOD;   // PWM Period
  TB3CCTL0 |= CCIE;         // Enable interrupt
  
  TB3CCTL1 = OUTMOD_7;             // CCR1 reset/set
  TB3CCTL1 |= CCIE;         // Enable interrupt
  RIGHT_FORWARD_SPEED = WHEEL_OFF; // P6.0 Right Forward off
  
  TB3CCTL2 = OUTMOD_7;             // CCR2 reset/set
  LEFT_FORWARD_SPEED = WHEEL_OFF;  // P6.1 Left Forward off
  
  TB3CCTL3 = OUTMOD_7;             // CCR3 reset/set
  RIGHT_REVERSE_SPEED = WHEEL_OFF; // P6.2 Right Reverse off
  
  TB3CCTL4 = OUTMOD_7;             // CCR4 reset/set
  LEFT_REVERSE_SPEED = WHEEL_OFF;  // P6.3 Left Reverse off
  
  TB3CCTL5 = OUTMOD_7;             // CCR4 reset/set
  
}


