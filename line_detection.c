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


unsigned short line_detection;
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int V_Thumb;



float measurment(){//This is the measurment value for the pid contoller
//  if(ADC_Left_Detect<=BASE_READING);//
//  if(ADC_Right_Detect<=BASE_READING);
  return (float)ADC_Left_Detect - ADC_Right_Detect ;//+ PID_SETPOINT;
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

