#include "macros.h"

extern volatile unsigned short display_bits;
extern unsigned int V_Thumb;
extern volatile unsigned char switch_control;
int prev_thumb;
extern int wheel_test;
unsigned char menu_state;
void menu_state_machine(){
  switch(menu_state){
  case Start_menu://start menu will have bat voltage and othe general info
    start_menu();
    break;
  case Main_menu:
    main_menu();
    break;
  case WIFI_menu:
    display_IP();
    break;
  case Settings:
    //settings_menu();
    break;
  case ADC_menu:
    adc_menu();
    break;
  case PID_menu:
    //pid_menu();
    break;
  default:
    menu_state = Main_menu;
    break;
  }
  
}
void start_menu(){
  clear_display();
  menu_state = Main_menu;
  
}
void main_menu(){
  main_menu_display(menu_options_3);
  //add change state logic
  if(SW1_AND_TOGGLED){
    SW1_CLEAR;
    switch(menu_options_3){
    case CASE_0:
      menu_state = Settings;
      break;
    case CASE_1:
      menu_state = ADC_menu;
      break;
    case CASE_3:
    case CASE_2:
      menu_state = PID_menu;
      break;
    }
  }
}
//void settings_menu(){
//  if(SW2_AND_TOGGLED){
//    SW2_CLEAR;
//    menu_state = Main_menu;
//  }
//}
void adc_menu(){
  if(SW2_AND_TOGGLED){
    SW2_CLEAR;
    menu_state = Main_menu;
    lcd_4line();
  }
  if(SW1_AND_TOGGLED){
    SW1_CLEAR;
    wheel_test ^= 0x01;//-------------------------------------------------
    
  }
  adc_display();
}

//void pid_menu(){
//  if(SW2_AND_TOGGLED){
//    SW2_CLEAR;
//    menu_state = Main_menu;
//    lcd_4line();
//  }
//  
//}
void v_thumb_process(){
  if(prev_thumb<(V_Thumb>>4)){
    prev_thumb=V_Thumb>>4;
    display_bits |= Song_char_changed; 
  }
  else if(prev_thumb>V_Thumb>>4){
    prev_thumb=V_Thumb>>4;
  }
}