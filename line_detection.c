#include "macros.h"
#define DECTECTION_THRESHOLD            (100)
#define DECTECTION_TOLERANCE            (10)


#define FULL_DETECTION                  (110)
#define STRONG_DETECTION                (100)
#define SLIGHT_DETECTION                (30)
#define BASE_READING                    (20)

#define SLIGHT_DETECTION_TOLERANCE      (30)


#define BASE_READING_TOLERANCE          (20)


#define DTH                             (DECTECTION_THRESHOLD+DECTECTION_TOLERANCE)//DECTECTION_THRESHOLD_LOW
#define DTL                             (DECTECTION_THRESHOLD-DECTECTION_TOLERANCE)//DECTECTION_THRESHOLD_HIGH

#define ERROR_LIMITS                          (1000)


#define Treshold			(200)
#define White_val			(300)
#define Black_val			(3000)
#define Off_line_ret			(450)
extern char display_line[DISPLAYLINES][DISPLAYCHARS];
extern volatile unsigned char switch_control;
unsigned short line_detection;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int V_Thumb;
unsigned int R_white;
unsigned int L_white;
unsigned int R_black;
unsigned int L_black;
short measure_state = 0;
char calibration_state = 0;
char calibrated = 0;

#define ON_line		(0)
#define right_of_line		(1)
#define left_of_line		(2)


int measurment(){//This is the measurment value for the pid contoller
  if(ADC_Left_Detect<=L_white+Treshold/*+Treshold*/&& measure_state != right_of_line && measure_state != left_of_line ){
  	measure_state = right_of_line;
  }
  if(ADC_Right_Detect<=R_white+Treshold/*+Treshold*/&& measure_state != right_of_line && measure_state != left_of_line ){
	measure_state =  left_of_line;
  }
  
  switch(measure_state){//current state of where it is on line
  case ON_line:
    strcpy(display_line[DISPLAY3], "    on    ");
    return (ADC_Left_Detect - L_white) - (ADC_Right_Detect - R_white) ;
  break;
  case right_of_line://want to turn left and keep turning until found line
    strcpy(display_line[DISPLAY3], "   right  ");
    if(ADC_Right_Detect>R_white+Treshold && ADC_Left_Detect > L_white+Treshold) measure_state = ON_line;
    return -Off_line_ret;
    break;
  case left_of_line://want to turn right and keep turning until found line
    strcpy(display_line[DISPLAY3], "   left   ");
    if(ADC_Right_Detect>R_white+Treshold && ADC_Left_Detect > L_white+Treshold) measure_state = ON_line;
    return Off_line_ret;
    break;
  
  }
  return (ADC_Left_Detect - L_white) - (ADC_Right_Detect - R_white) ;
}
void line_calibration(){
  while(!(calibrated)){
    switch(calibration_state){
    case 0:
      if(SW1_AND_TOGGLED){
	SW1_CLEAR;
	R_white = ADC_Right_Detect;
	L_white = ADC_Left_Detect;
	calibration_state++;
      }
      line_calibration_display('w');
      break;
    case 1:
      if(SW1_AND_TOGGLED){
	SW1_CLEAR;
	R_black = ADC_Right_Detect;
	L_black = ADC_Left_Detect;
	calibration_state++;
	
      }
      line_calibration_display('b');
      break;
    case 2:
      calibrated = 1;
      break;
    }
    Display_Process();
  }
}

void set_line_bit(unsigned short level_detection){
  if(level_detection>L_CLEAR)line_detection &= L_CLEAR;
  else line_detection &= R_CLEAR;
  line_detection |= level_detection;
}

void left_detector_process(){
  if(ADC_Right_Detect<=BASE_READING)set_line_bit(R_BASE);
  else if(ADC_Right_Detect<=SLIGHT_DETECTION)set_line_bit(R_SLIGHT);
  else if(ADC_Right_Detect<=STRONG_DETECTION)set_line_bit(R_STRONG);
  else if(ADC_Right_Detect>STRONG_DETECTION)set_line_bit(R_FULL);
}
void right_detector_process(){
  if(ADC_Left_Detect<=BASE_READING)set_line_bit(L_BASE);
  else if(ADC_Left_Detect<=SLIGHT_DETECTION)set_line_bit(L_SLIGHT);
  else if(ADC_Left_Detect<=STRONG_DETECTION)set_line_bit(L_STRONG);
  else if(ADC_Left_Detect>STRONG_DETECTION)set_line_bit(L_FULL);
}

void process_detectors(){
  left_detector_process();
  right_detector_process();
}

unsigned short strong_detect(){
  if(line_detection==0x88){
    return 1;
  }
  return 0;
}

