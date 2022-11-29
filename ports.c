/*
  Description: ports.c has all the intilizations of the ports and a function 
  that will run all of the port intilizations.  

  Tobias Desotelle
  Team: Magic Smoke
  October 14 2022
  Built with IAR Embedded Workbench Version: (7.21.1)
*/

#include "macros.h"

void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3(USE_GPIO);
  Init_Port4();
  Init_Port5();
  Init_Port6();
}
void Init_Port1(void){
/*
#define RED_LED                 (0x01) //P1.0
#define A1_SEEED                (0x02) //P1.1
#define V_DETECT_L              (0x04) //P1.2
#define V_DETECT_R              (0x08) //P1.3
#define A4_SEEED                (0x10) //P1.4
#define V_THUMB                 (0x20) //P1.5
#define UCA0RXD                 (0x40) //P1.6
#define UCA0TXD                 (0x80) //P1.7
*/

P1OUT = OUT1; // P1 set Low
P1DIR = DIR1; // Set P1 direction to output
P1SEL0 = SEL1_0;
P1SEL1 = SEL1_1;

//P1SEL0 &= ~RED_LED;
//P1SEL1 &= ~RED_LED;
//P1OUT |= RED_LED;
//P1DIR |= RED_LED;
//
//P1SEL0 |= A1_SEEED;
//P1SEL1 |= A1_SEEED;
//// P1OUT &= ~A1_SEEED;
//// P1DIR &= ~A1_SEEED;
//
//P1SEL0 |= V_DETECT_L;
//P1SEL1 |= V_DETECT_L;
////P1OUT &= ~V_DETECT_L;
////P1DIR &= ~V_DETECT_L;
//
//P1SEL0 |= V_DETECT_R;
//P1SEL1 |= V_DETECT_R;
////P1OUT &= ~V_DETECT_R;
////P1DIR &= ~V_DETECT_R;
//
//P1SEL0 |= A4_SEEED;
//P1SEL1 |= A4_SEEED;
////P1OUT &= ~A4_SEEED;
////P1DIR &= ~A4_SEEED;
//
//P1SEL0 |= V_THUMB;
//P1SEL1 |= V_THUMB;
////P1OUT &= ~V_THUMB;
////P1DIR &= ~V_THUMB;
//
//P1SEL0 |= UCA0RXD;
//P1SEL1 &= ~UCA0RXD;
////P1OUT &= ~UCA0RXD;
////P1DIR &= ~UCA0RXD;
//
//P1SEL0 |= UCA0TXD;
//P1SEL1 &= ~UCA0TXD;
////P1OUT &= ~UCA0TXD;
////P1DIR &= ~UCA0TXD;
}
void Init_Port2(void){ 
//------------------------------------------------------------------------------
//P2OUT = LOW; // P2 set Low
//P2DIR = PORT_OUT; // Set P2 direction to output

P2OUT = OUT2; 
P2DIR = DIR2; 
P2SEL0 = SEL2_0;
P2SEL1 = SEL2_1;
P2REN |= SW2; // Enable pullup resistor
P2IES |= SW2; // P4.2 Hi/Lo edge interrupt
P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
P2IE |= SW2; // P4.2 interrupt enabled

//P2SEL0 &= ~RESET_LCD; // RESET_LCD GPIO operation
//P2SEL1 &= ~RESET_LCD; // RESET_LCD GPIO operation
//P2OUT &= ~RESET_LCD; // Initial Value = Low / Off
//P2DIR |= RESET_LCD; // Direction = output
//
//P2SEL0 &= ~Check_Bat; // Check_Bat GPIO operation
//P2SEL1 &= ~Check_Bat; // Check_Bat GPIO operation
//P2OUT &= ~Check_Bat; // Initial Value = Low / Off
//P2DIR |= Check_Bat; // Direction = output
//
//P2SEL0 &= ~IR_LED; // P2_2 GPIO operation
//P2SEL1 &= ~IR_LED; // P2_2 GPIO operation
//P2OUT &= ~IR_LED; // Initial Value = Low / Off
//P2DIR |= IR_LED; // Direction = input
//
//P2SEL0 &= ~SW2; // SW2 Operation
//P2SEL1 &= ~SW2; // SW2 Operation
//P2OUT |= SW2; // Configure pullup resistor
//P2DIR &= ~SW2; // Direction = input
//P2REN |= SW2; // Enable pullup resistor
//P2IES |= SW2; // P4.2 Hi/Lo edge interrupt
//P2IFG &= ~SW2; // Clear all P2.6 interrupt flags
//P2IE |= SW2; // P4.2 interrupt enabled

//P2SEL0 &= ~IOT_RUN_CPU; // IOT_RUN_CPU GPIO operation
//P2SEL1 &= ~IOT_RUN_CPU; // IOT_RUN_CPU GPIO operation
//P2OUT |= IOT_RUN_CPU; // Initial Value = Low / Off
//P2DIR |= IOT_RUN_CPU; // Direction = input
//
//P2SEL0 &= ~DAC_ENB; // DAC_ENB GPIO operation
//P2SEL1 &= ~DAC_ENB; // DAC_ENB GPIO operation
//P2OUT |= DAC_ENB; // Initial Value = High
//P2DIR |= DAC_ENB; // Direction = output
//
//P2SEL0 &= ~LFXOUT; // LFXOUT Clock operation
//P2SEL1 |= LFXOUT; // LFXOUT Clock operation
//
//P2SEL0 &= ~LFXIN; // LFXIN Clock operation
//P2SEL1 |= LFXIN; // LFXIN Clock operation
//------------------------------------------------------------------------------
}
void Init_Port3(char smclk){ 
  P3OUT = OUT3; 
  P3DIR = DIR3; 
  P3SEL0 = SEL3_0;
  P3SEL1 = SEL3_1;
//  
//  
//  
//  P3OUT = LOW; // P3 set Low
//  P3DIR = PORT_OUT; // Set P3 direction to output
//
//  P3SEL0 &= ~TEST_PROBE; 
//  P3SEL1 &= ~TEST_PROBE;
//  P3OUT |= TEST_PROBE;
//  P3DIR |= TEST_PROBE;
//
//  P3SEL0 |= OA2O;
//  P3SEL1 |= OA2O;
//  //P3OUT &= ~OA2O;
//  //P3DIR &= ~OA2O;
//
//  P3SEL0 |= OA2N;
//  P3SEL1 |= OA2N;
//  //P3OUT &= ~OA2N;
//  //P3DIR &= ~OA2N;
//
//  P3SEL0 |= OA2P;
//  P3SEL1 |= OA2P;
//  //P3OUT &= ~OA2P;
//  //P3DIR &= ~OA2P;
//  switch(smclk){
//    case(USE_GPIO):
//      P3SEL0 &= ~SMCLK;
//      P3SEL1 &= ~SMCLK;
//      P3OUT &= ~SMCLK;
//      P3DIR |= SMCLK;
//      break;
//    case(USE_SMCLK):
//      P3SEL0 |= SMCLK;
//      P3SEL1 &= ~SMCLK;
//      //P3OUT  &= ~SMCLK;
//      P3DIR  |= SMCLK;
//       break;
//  default:
//    break;
//  }
//
//  P3SEL0 &= ~DAC_CNTL;
//  P3SEL1 &= ~DAC_CNTL;
//  P3OUT &= ~DAC_CNTL;
//  P3DIR &= ~DAC_CNTL;
//
//  P3SEL0 &= ~IOT_LINK_CPU;
//  P3SEL1 &= ~IOT_LINK_CPU;
//  P3OUT &= ~IOT_LINK_CPU;
//  P3DIR |= IOT_LINK_CPU;
//
  P3SEL0 &= ~IOT_EN_CPU;
  P3SEL1 &= ~IOT_EN_CPU;
  P3OUT &= ~IOT_EN_CPU;
  P3DIR |= IOT_EN_CPU;
}
void Init_Port4(void){ 
//------------------------------------------------------------------------------

  P4OUT = OUT4; 
  P4DIR = DIR4; 
  P4SEL0 = SEL4_0;
  P4SEL1 = SEL4_1;
  P4REN |= SW1; // Enable pullup resistor
  P4IES |= SW1; // P4.2 Hi/Lo edge interrupt
P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
P4IE |= SW1; // P4.2 interrupt enabled
//  P4OUT = LOW; // P4 set Low
//P4DIR = PORT_OUT; // Set P4 direction to output
//
//P4SEL0 &= ~DAC_CNTL1; // DAC_CNTL1 GPIO operation
//P4SEL1 &= ~DAC_CNTL1; // DAC_CNTL1 GPIO operation
//P4OUT |= DAC_CNTL1; // Set DAC_CNTL1 Off [High]
//P4DIR |= DAC_CNTL1; // Set DAC_CNTL1 direction to output
//
//P4SEL0 &= ~SW1; // SW1 GPIO operation
//P4SEL1 &= ~SW1; // SW1 GPIO operation
//P4OUT |= SW1; // Configure pullup resistor
//P4DIR &= ~SW1; // Direction = input
//P4REN |= SW1; // Enable pullup resistor
//P4IES |= SW1; // P4.2 Hi/Lo edge interrupt
//P4IFG &= ~SW1; // Clear all P2.6 interrupt flags
//P4IE |= SW1; // P4.2 interrupt enabled
//
//P4SEL0 |= UCA1TXD; // USCI_A1 UART operation
//P4SEL1 &= ~UCA1TXD; // USCI_A1 UART operation
//
//P4SEL0 |= UCA1RXD; // USCI_A1 UART operation
//P4SEL1 &= ~UCA1RXD; // USCI_A1 UART operation
//
//P4SEL0 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
//P4SEL1 &= ~UCB1_CS_LCD; // UCB1_CS_LCD GPIO operation
//P4OUT |= UCB1_CS_LCD; // Set SPI_CS_LCD Off [High]
//P4DIR |= UCB1_CS_LCD; // Set SPI_CS_LCD direction to output
//
//P4SEL0 |= UCB1CLK; // UCB1CLK SPI BUS operation
//P4SEL1 &= ~UCB1CLK; // UCB1CLK SPI BUS operation
//
//P4SEL0 |= UCB1SIMO; // UCB1SIMO SPI BUS operation
//P4SEL1 &= ~UCB1SIMO; // UCB1SIMO SPI BUS operation
//
//P4SEL0 |= UCB1SOMI; // UCB1SOMI SPI BUS operation
//P4SEL1 &= ~UCB1SOMI; // UCB1SOMI SPI BUS operation
//------------------------------------------------------------------------------
}
void Init_Port5(void){ 

  P5OUT = OUT5; 
  P5DIR = DIR5; 
  P5SEL0 = SEL5_0;
  P5SEL1 = SEL5_1;
//  
//  P5OUT = LOW; // P5 set Low
//P5DIR = PORT_OUT; // Set P5 direction to output 
//
//P5SEL0 &= ~CHECK_BAT;
//P5SEL1 &= ~CHECK_BAT;
//P5OUT &= ~CHECK_BAT;
//P5DIR &= ~CHECK_BAT;
//
//P5SEL0 &= ~V_BAT;
//P5SEL1 &= ~V_BAT;
//P5OUT &= ~V_BAT;
//P5DIR &= ~V_BAT;
//
//P5SEL0 &= ~V_DAC;
//P5SEL1 &= ~V_DAC;
//P5OUT &= ~V_DAC;
//P5DIR &= ~V_DAC;
//
//P5SEL0 &= ~V_3_3;
//P5SEL1 &= ~V_3_3;
//P5OUT &= ~V_3_3;
//P5DIR &= ~V_3_3;
//
P5SEL0 &= ~IOT_BOOT_CPU;
P5SEL1 &= ~IOT_BOOT_CPU;
P5OUT &= ~IOT_BOOT_CPU;
P5DIR &= ~IOT_BOOT_CPU;
}
void Init_Port6(void){ 
  
  P6OUT = OUT6; 
  P6DIR = DIR6; 
  P6SEL0 = SEL6_0;
  P6SEL1 = SEL6_1;
  
//P6OUT = LOW; // P6 set Low
//P6DIR = PORT_OUT; // Set P6 direction to output  
//
//P6SEL0 |= R_FORWARD;
//P6SEL1 &= ~R_FORWARD;
//P6OUT &= ~R_FORWARD;
//P6DIR |= R_FORWARD;
//
//P6SEL0 |= R_REVERSE;
//P6SEL1 &= ~R_REVERSE;
//P6OUT &= ~R_REVERSE;
//P6DIR |= R_REVERSE;
//
//P6SEL0 |= L_FORWARD;
//P6SEL1 &= ~L_FORWARD;
//P6OUT &= ~L_FORWARD;
//P6DIR |= L_FORWARD;
//
//P6SEL0 |= L_REVERSE;
//P6SEL1 &= ~L_REVERSE;
//P6OUT &= ~L_REVERSE;
//P6DIR |= L_REVERSE;
//
//P6SEL0 |= LCD_BACKLIGHT;
//P6SEL1 &= ~LCD_BACKLIGHT;
//P6OUT &= ~LCD_BACKLIGHT;
//P6DIR |= LCD_BACKLIGHT;
//
//P6SEL0 |= P6_5;
//P6SEL1 &= ~P6_5;
//P6OUT &= ~P6_5;
//P6DIR |= P6_5;
//
//P6SEL0 &= ~GRN_LED;
//P6SEL1 &= ~GRN_LED;
//P6OUT &= ~GRN_LED;
//P6DIR |= GRN_LED;
}