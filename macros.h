/*
  Description: This will contain all of the #defines for refrance and
  ease of modification in the future.  

  Tobias Desotelle
  Team: Magic Smoke
  October 14 2022
  Built with IAR Embedded Workbench Version: (7.21.1)
*/

//  
#include  "functions.h"
#include  "msp430.h"
#include  "pid.h"
#include  "time.h"
#include <string.h>
#include <stdlib.h>


#define ALWAYS                  (1)
#define CHANGED                 (1)
#define RESET_STATE             (0)
#define RESET                   (0)
#define TRUE                    (0x01)


#define TURN_SPEED              (0)
#define BASE_SPEED              (5000)
//===========================GENERAL PORT DEFINTIONS ===========================
#define LOW                     (0X00)
#define HIGH                    (0X01)
#define PORT_OUT                (0X00)
#define PORT_IN                 (0X01)
#define DEFAULT                 (0X00)
//===========================Serial=============================================
#define BAUD115200      (0x00)
#define BAUD460800      (0x01)
#define SERIAL_WAITING  (0X01)
#define SERIAL_RX       (0X02)
#define SERIAL_TX       (0x04)
#define tx_buff_update  (0x08)
#define rx_buff_update  (0x10)
#define Serial_off      (0x20)
#define UCA1_TX         (0x40)
#define Command_bit      (0x80)
#define Process_command (0x100)
#define Process_buffer_0 (0x200)
#define Process_buffer_1 (0x400)
#define Send_next_command (0x800)
#define Wifi_connected	  (0x1000)

#define NUM_Commands		(10)
#define NUM_Command_chars	(16)

#define Send_UCA0        (0x00)
#define Send_UCA1        (0x01)

#define PASSWORD	("1234")
#define PASSWORD_LENGTH 	(4)

#define SEND_THIS              ("UNCA  #1")
#define BEGINNING (0)
#define SMALL_RING_SIZE (32)
#define NUM_PROCESS_BUF (8)
#define PROCESS_BUF_LENGTH  (64)


// ===========================Menu==============================================

#define menu_options_3          (V_Thumb >> 10)
#define menu_options_16         (V_Thumb >> 8 )

//menu cases
#define Start_menu              (0x00)
#define Main_menu               (0x01)
#define Settings                (0x02)
#define ADC_menu                (0x03)
#define PID_menu                (0x04)
#define IP_Display		(0X05)

#define Settings_dis             ("  Settings")
#define Adc_disp                 ("  ADC Vals")
#define Pid_menu                 ("  PID Tune")


// ===========================SWITCHES==========================================
#define PRESSED                 (1)
#define RELEASED                (0)
#define OKAY                    (1)
#define NOT_OKAY                (0)
#define DEBOUNCE_RESTART        (0)
#define DEBOUNCE_TIME           (50)


#define SW1_PRESSED                 (0x01)
#define SW2_PRESSED                 (0x02)
#define SW1_RELEASED                (0x04)
#define SW2_RELEASED                (0x08)
#define SW1_TOGGLED                 (0x10)
#define SW2_TOGGLED                 (0x20)

#define SW1_AND_TOGGLED               (switch_control & SW1_TOGGLED)
#define SW2_AND_TOGGLED               (switch_control & SW2_TOGGLED)
#define SW1_CLEAR                     (switch_control &= ~SW1_TOGGLED)
#define SW2_CLEAR                     (switch_control &= ~SW2_TOGGLED)

#define WAITING2START (500)

// ===========================STATES============================================
#define IDLE                    (0x00)
#define START                   (0x01)
#define LINE_FOUND              (0x02)
#define BACK_UP                 (0x03)
#define ALIGN                   (0x04)
#define PID                     (0x05)
#define ADJUST                  (0x06)

#define Configure_Wheel_Speeds  ('C')
#define Forward_Move_Start      ('F')
#define Forward_Adjust          ('f')
#define Reverse_Move_Start      ('R')
#define Reverse_Adjust          ('r')
#define Initiate_Stop           ('s')
#define Stop                    ('D')
#define RUN                     ('R')
#define REPEAT                  ('r')
#define END                     ('E')

#define F1                      ('X')
#define F2                      ('z')
#define F3                      ('Z')
//===========================DISPLAY============================================
#define DISPLAYLINES            (4)
#define DISPLAYCHARS            (11)
#define DISPLAYEND              (10)
#define DISPLAYSTART            (0)
#define DISPLAYCHANGED          (1)
#define DISPLAY0                (0)
#define DISPLAY1                (1)
#define DISPLAY2                (2)
#define DISPLAY3                (3)
#define UPDATED                 (1)

#define Splash_bit              (0x01)
#define Song_char_changed         (0x02)
#define Display_IP		(0x04)
		

#define GET_V_THUMB     (0x00)
#define GET_L_DETECT    (0x01)
#define GET_R_DETECT    (0x02)

#define R_BASE          (0x01)
#define R_SLIGHT        (0x02)
#define R_STRONG        (0x04)
#define R_FULL          (0x08)
#define L_BASE          (0x10)
#define L_SLIGHT        (0x20)
#define L_STRONG        (0x40)
#define L_FULL          (0x80)

#define R_MASK         (0x0F)
#define L_MASK         (0xF0)
#define R_CLEAR         (0xf0)
#define L_CLEAR         (0x0f)
//===========================TIMES==============================================
#define TIME5                 (5)
#define TIME20                 (20)
//===========================TIMERS==============================================
#define CCR1           (2)
#define CCR2           (4)
#define CCR3           (6)
#define CCR4           (8)
#define CCR5           (10)
#define TIMER_OVERFLOW    (14)
#define TIMER_CASE_0           (0)
#define MILL_TO_HALFSECONDS        (200)

#define START_DELAY             (5)
#define TB1CCR1_BIT             (0x10)
#define DELAY_2_SEC             (0x04)
#define DELAYED_2_SEC           (0x08)
#define Movemet_timer		(0x10)
#define Change_wheel_state	(0x20)
//#define 


//Timer 0
#define TB0CCR0_INTERVAL        (6250)
#define TB0CCR1_INTERVAL        (6250)//
#define TB0CCR2_INTERVAL        (25000)//200MS
//Timer 1
#define TB1CCR0_INTERVAL        (25000)
#define TB1CCR1_INTERVAL        (1250)

#define TB1CCR2_INTERVAL        (1250)
//Timer 2
#define TB2CCR0_INTERVAL        (25000)
//#define TB2CCR1_INTERVAL        (6250)
//#define TB2CCR2_INTERVAL        (6250)
//Timer 3
#define RIGHT_REVERSE_SPEED   (TB3CCR1)  // P6.0 TimerB3_2
#define RIGHT_FORWARD_SPEED   (TB3CCR2)  // P6.1 TimerB3_1 
#define LEFT_REVERSE_SPEED    (TB3CCR3)  // P6.2 TimerB3_4
#define LEFT_FORWARD_SPEED    (TB3CCR4)  // P6.3 TimerB3_3
#define BACKLIGHT             (TB3CCR5)  //OLD = LED_TEST
//===========================PWM================================================
#define WHEEL_PERIOD               (62500)
#define WHEEL_OFF             (0)        // Wheel off for PWM duty cycle

#define R_MOTOR_STATE       (0x01)
#define L_MOTOR_STATE       (0x02)
#define R_MOTOR_DIR         (0x04)
#define L_MOTOR_DIR         (0x08)
#define R_MOTOR_DIR_CHANGED (0X10)   
#define L_MOTOR_DIR_CHANGED (0X20)
#define R_MOTOR_SPD_CHANGED (0X40)
#define L_MOTOR_SPD_CHANGED (0X80)

#define RIGHT_MOTOR           ('R')
#define LEFT_MOTOR            ('L')

#define WHEELS_ON             (0x03)
#define WHEELS_DIR_CHANGED    (0x30)
#define DIR_MASK              (0x0f)

#define BOTH_FORWARD          (0x03)
#define PIVOT_F_L             (0x01) 
#define FORWARD               (0x03)
#define REVERSE               (0x0F)
#define STOP		      (0x00)
#define ESTOP		      (0xF1)
#define CCW                   (0x0B)
#define  CW                   (0x07)
#define BOTH_REVERSE          (0x0f)



//#define CW                    (0x00)//need to define
//===========================PID================================================
#define PID_SETPOINT                    (255.0f)
//===========================PORTS==============================================
//--------------------Port1-----------------------------

//LIGHT PORT CONFIG
#define OUT1			(0x00)
#define DIR1			(0x01)
#define SEL1_0			(0xFE)
#define SEL1_1			(0x3E)
#define RED_LED                 (0x01) //P1.0
#define A1_SEEED                (0x02) //P1.1
#define V_DETECT_L              (0x04) //P1.2
#define V_DETECT_R              (0x08) //P1.3
#define A4_SEEED                (0x10) //P1.4
#define V_THUMB                 (0x20) //P1.5
#define UCA0RXD                 (0x40) //P1.6
#define UCA0TXD                 (0x80) //P1.7

//--------------------Port2-----------------------------
#define OUT2			(0x3D)
#define DIR2			(0x37)
#define SEL2_0			(0x00)
#define SEL2_1			(0xC0)

#define RESET_LCD               (0x01) //P2.0
#define Check_Bat               (0x02) //P2.1
#define IR_LED                  (0x04) //P2.2
#define SW2                     (0x08) //P2.3
#define IOT_RUN_CPU             (0x10) //P2.4
#define DAC_ENB                 (0x20) //P2.5
#define LFXOUT                  (0x40) //P2.6
#define LFXIN                   (0x80) //P2.7

//--------------------Port3-----------------------------
#define OUT3			(0x01)
#define DIR3			(0xD1)
#define SEL3_0			(0x0E)
#define SEL3_1			(0x0E)

#define TEST_PROBE               (0x01) //P3.0
#define OA2O                     (0x02) //P3.1
#define OA2N                     (0x04) //P3.2
#define OA2P                     (0x08) //P3.3
#define SMCLK                    (0x10) //P3.4
#define DAC_CNTL                 (0x20) //P3.5
#define IOT_LINK_CPU             (0x40) //P3.6
#define IOT_EN_CPU               (0x80) //P3.7
#define USE_GPIO                 (0x00)
#define USE_SMCLK                (0x01)
//--------------------Port4-----------------------------
#define OUT4			(0x13)
#define DIR4			(0x11)
#define SEL4_0			(0xEC)
#define SEL4_1			(0x00)

#define DAC_CNTL1                (0x01) //P4.0
#define SW1                      (0x02) //P4.1
#define UCA1RXD                  (0x04) //P4.2
#define UCA1TXD                  (0x08) //P4.3
#define UCB1_CS_LCD              (0x10) //P4.4
#define UCB1CLK                  (0x20) //P4.5
#define UCB1SIMO                 (0x40) //P4.6
#define UCB1SOMI                 (0x80) //P4.7

//--------------------Port5-----------------------------
#define OUT5			(0x00)
#define DIR5			(0x00)
#define SEL5_0			(0x00)
#define SEL5_1			(0x00)

#define CHECK_BAT                (0x01) //P5.0
#define V_BAT                    (0x02) //P5.1
#define V_DAC                    (0x04) //P5.2
#define V_3_3                    (0x08) //P5.3
#define IOT_BOOT_CPU             (0x10) //P5.4

//--------------------Port6-----------------------------
#define OUT6			(0x00)
#define DIR6			(0x7F)
#define SEL6_0			(0x3F)
#define SEL6_1			(0x00)

#define R_FORWARD                (0x01) //P6.0
#define R_REVERSE                (0x02) //P6.1
#define L_FORWARD                (0x04) //P6.2
#define L_REVERSE                (0x08) //P6.3
#define LCD_BACKLIGHT            (0x10) //P6.4
#define P6_5                     (0x20) //P6.5
#define GRN_LED                  (0x40) //P6.6


//===========================STRINGS============================================
#define DETECT_L_STRING         ("DL=")
#define DETECT_R_STRING         ("DR=")
#define V_THUMB_STRING          ("VT=")
#define IR_STRING               ("IR_LED=")
#define BAUD115200_STRING       ("  115200  ")
#define BAUD460800_STRING       ("  460800  ")
#define CLEAR_DISPLAY           ("          ")
#define UNCA_STRING             (" UNCA  #1 ")
#define WAITING1                ("Waiting.  ")
#define WAITING2                ("Waiting.. ")
#define WAITING3                ("Waiting...")
#define Connecting1             ("Connecting")
#define Connecting2                ("Waiting.. ")
#define Connecting3                ("Waiting...")
#define RECIVED                 ("Recived rx")
#define TRASMIT                 (" Transmit ")
#define CHAR_0                  (0x30)
#define adc_num_chars           (4)
#define adc_c_0                 (0)
#define adc_c_1                 (1)
#define adc_c_2                 (2)
#define adc_c_3                 (3)
#define add_one                 (1)
#define Above_999              (999)
#define Above_99              (99)
#define Above_9              (9)



//===========================CASE Numbers============================================
#define CASE_0                  (0x00)
#define CASE_1                  (0x01)
#define CASE_2                  (0x02)
#define CASE_3                  (0x03)
#define CASE_4                  (0x04)
#define CASE_5                  (0x05)
#define CASE_6                  (0x06)
#define CASE_7                  (0x07)
#define CASE_8                  (0x08)
#define CASE_9                  (0x09)
#define CASE_10                 (0x0A)
