/*
  Description: This is where all the inturrpt service routuines are.
 

  Tobias Desotelle
  Team: Magic Smoke
  October 14 2022
  Built with IAR Embedded Workbench Version: (7.21.1)
*/

#include "macros.h"
extern volatile unsigned char update_display;

unsigned int time_interval50;//50ms
unsigned int time_interval_200;

extern volatile unsigned short display_bits;
extern volatile unsigned short timer_bits;
extern volatile unsigned short motor_control_bits;
extern volatile unsigned short serial_bits;
extern volatile unsigned char switch_control;
extern unsigned short line_detection;
unsigned int timer200=0;

extern volatile unsigned int sw1_timer;
extern volatile unsigned int sw2_timer;
extern unsigned int time100;
extern unsigned int right_speed;
extern unsigned int left_speed;


int cur=0;

//==================================Timer 0=====================================
/* Timer 0 Refreance
  SMCLK 8MHZ
  
  #define TB0CCR0_INTERVAL        (6250)//50MS
  50ms timer counter for timed events and enables conversions
  
  #define TB0CCR1_INTERVAL        (6250)//50MS
  CCR1 used for a toggle 50ms timer used for debouncing
  
  #define TB0CCR2_INTERVAL        (25000)//200MS
  CCR2 used for motor delay


*/
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  TB0CCR0 += TB0CCR0_INTERVAL;
  //process_detectors();
    ADCCTL0 |= ADCENC; //Enable Conversions
    ADCCTL0 |= ADCSC;  //Start next sample
  time_interval50++;
  if(time_interval50>=4){
    time_interval50=0;
    update_display=UPDATED;
  }
  
}
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  switch(__even_in_range(TB0IV,14)){
  case TIMER_CASE_0: break; // No interrupt
  case CCR1:
    TB0CCTL1 &= ~CCIFG;
    TB0CCR1 += TB0CCR1_INTERVAL;
    if(switch_control&SW1_PRESSED){
      sw1_timer++;
    }
    if(switch_control&SW2_PRESSED){
      sw2_timer++;
    }
    break;
  case CCR2: 
    time_interval_200++;
    if((time_interval_200 >= 5 )&& serial_bits & Serial_off){
      send("hello im testing the length of stings that can be sent",1);
      time_interval_200 = 0;
    }
    TB0CCR2 += TB0CCR2_INTERVAL;
    break;
  case TIMER_OVERFLOW: // overflow
    break;
  default: break; 
  }
}



//==================================Timer 1=====================================
/* Timer 1 Refreance
  SMCLK 8MHZ
  
  #define TB1CCR0_INTERVAL        (6250)//50MS
  CCR0 is used for ramping pwm signals
  
  #define TB0CCR1_INTERVAL        (6250)//50MS
  un-used
  
  #define TB0CCR2_INTERVAL        (25000)//200MS
  CCR2 used for updating display
  un-used

*/
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){ 
  if(!(display_bits&Splash_bit)){
    timer200++;
    if(timer200>=START_DELAY){
      display_bits |= Splash_bit;
      clear_line(0);
      timer200=RESET;
    }
  }
  if(timer_bits & DELAY_2_SEC){
    timer200++;
    if(timer200>=START_DELAY){
      timer_bits |= DELAYED_2_SEC;
      timer_bits &= ~DELAY_2_SEC;
      timer200=RESET;
    }
  }
    
    
//  if(BACKLIGHT==speed){
//    TB1CCTL0 &= ~CCIFG;
//    TB1CCTL0 &= ~CCIE; 
//  }
//  else if(BACKLIGHT<speed){
//    BACKLIGHT+=1000;
//    TB1CCR0+=TB1CCR0_INTERVAL;
//  }
//  else if(BACKLIGHT>speed){
//    BACKLIGHT-=1000;
//    TB1CCR0+=TB1CCR0_INTERVAL;
//  }
}
#pragma vector=TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void){
  switch(__even_in_range(TB1IV,14)){
  case TIMER_CASE_0: break; // No interrupt
  case CCR1://use for lentgth of movement
    TB1CCR1+=TB1CCR1_INTERVAL;
    timer_bits |= TB1CCR1_BIT;
    break;
  case CCR2: 
    TB1CCTL2 &= ~CCIFG;
    TB1CCR2+=TB1CCR2_INTERVAL;
    
    break;
  case TIMER_OVERFLOW:
    break;
  default: break; 
  }
}


//==================================Timer 2=====================================
/* Timer 2 Refreance
  SMCLK 8MHZ
  
  #define TB0CCR0_INTERVAL        (6250)//50MS
  50ms timer counter for timed events and enables conversions
  
  #define TB0CCR1_INTERVAL        (6250)//50MS
  CCR1 used for a toggle 50ms timer used for debouncing
  
  #define TB0CCR2_INTERVAL        (25000)//200MS
  CCR2 used for updating display


*/
#pragma vector = TIMER2_B0_VECTOR
__interrupt void Timer2_B0_ISR(void){ 
  TB2CCTL0 &= ~CCIFG;
  TB2CCTL0 &= ~CCIE;
  TB2CCR0 = TB0CCR0_INTERVAL;
  timer_bits |= Change_wheel_state;
}
#pragma vector=TIMER2_B1_VECTOR
__interrupt void TIMER2_B1_ISR(void){
  switch(__even_in_range(TB2IV,14)){
  case TIMER_CASE_0: break; // No interrupt
  case CCR1:
    break;
  case CCR2: 
    break;
  case TIMER_OVERFLOW:
    break;
  default: break; 
  }
  //----------------------------------------------------------------------------
}

//==================================Timer 3=====================================
/* Timer 3 Refreance
  SMCLK 8MHZ
  
  #define TB0CCR0_INTERVAL        (6250)//50MS
  50ms timer counter for timed events and enables conversions
  
  #define TB0CCR1_INTERVAL        (6250)//50MS
  CCR1 used for a toggle 50ms timer used for debouncing
  
  #define TB0CCR2_INTERVAL        (25000)//200MS
  CCR2 used for updating display


*/
#pragma vector = TIMER3_B0_VECTOR
__interrupt void Timer3_B0_ISR(void){ 
  // TB3_0 - no interrupt
}
#pragma vector = TIMER3_B1_VECTOR
__interrupt void TIMER3_B1_ISR(void){
  switch(__even_in_range(TB3IV,14)){
  case TIMER_CASE_0: break;   // No interrupt
  case CCR1:   // R_FORWARD
    break; 
  case CCR2:   // L_FORWARD
    // No interrupt
    break;
  case CCR3:   // R_REVERSE
    // No interrupt
    break;
  case CCR4:   // L_REVERSE
    // No interrupt
    break;
  case CCR5:   // L_REVERSE
    // No interrupt
    break;
  case TIMER_OVERFLOW:     // overflow available for greater than 1 second timer
    break;
  default: break;
  }
} 


    
    

  