//------------------------------------------------------------------------------
//
//  Description: This file contains the functions of controling the display.
//
//
//  Tobias Desotelle
//  September 20 2022
//  Built with IAR Embedded Workbench Version: (7.21.1)
//--------------------------------------------------------------------------
#include "macros.h"
extern volatile unsigned char update_display;
extern volatile unsigned char display_changed;
extern char display_line[DISPLAYLINES][DISPLAYCHARS];
extern volatile unsigned short display_bits;
char ani_state;
unsigned char connect_state;
extern char IP_Addy[21];
extern char SSID[11];
extern char adc_char[5];
extern unsigned int ADC_Left_Detect;
extern unsigned int ADC_Right_Detect;
extern unsigned int V_Thumb;
char time_disp[4];
extern unsigned int timer;
char display_pad_case;
#define Trying_to_connect	(0x00)
void Connecting_machine(){
  switch(connect_state){
  case Trying_to_connect:
    Connecting_Display();
    if(display_bits & Display_IP)connect_state = WIFI_menu;
    break;
  case WIFI_menu:
    display_IP();
    break;
  }
  
}
void Init_Display(void){
    strcpy(display_line[DISPLAY0], "  MSP 430 ");
    strcpy(display_line[DISPLAY1], "Powered on");
    strcpy(display_line[DISPLAY2], "          ");
    strcpy(display_line[DISPLAY3], "          ");
  display_changed = TRUE;
  update_display=UPDATED;
  Display_Process();
  
}
void Connecting_Display(void){
    //lcd_BIG_mid();
    strcpy(display_line[DISPLAY0], "Connecting");
    strcpy(display_line[DISPLAY1], "          ");
    //strcpy(display_line[DISPLAY2], "Desotelle ");
  display_changed = TRUE;
  update_display=UPDATED;
  Display_Process();
}
void Display_Process(void){
  if(update_display){
    update_display = RESET_STATE;
    if(display_changed){
      display_changed = RESET_STATE;
      Display_Update(RESET_STATE,RESET_STATE,RESET_STATE,RESET_STATE);
    }
  }
}
void display_IP(){
  if(display_bits & Display_IP){
    	char temp_ip[11];
	//strncpy(temp_ip,SSID,10);
	change_display_line("connected ",DISPLAY0);
    	change_display_line(SSID,DISPLAY1);
  	strncpy(temp_ip,IP_Addy,10);
	change_display_line(temp_ip,DISPLAY2);
	strncpy(temp_ip,&IP_Addy[10],10);
	change_display_line(temp_ip,DISPLAY3);
	
  }
  else{
    change_display_line("connecting",DISPLAY0);
  }
  display_changed = TRUE;
  update_display=UPDATED;
  Display_Process();
}
//void display_ssid(){
//  strstr(SSID,'.')
//  
//}
void waiting_animation(){
  switch(ani_state){
  case 0:
    change_display_line(WAITING1,DISPLAY0);
    ani_state++;
    break;
  case 1:
    ani_state++;
    change_display_line(WAITING2,DISPLAY0);
    break;
  case 2:
    change_display_line(WAITING3,DISPLAY0);
    ani_state=0;
    break;
  default:
    ani_state=0;
    break;
  } 
  
  
}
void diplay_pad_increment(){
  display_pad_case++;
}
char pad[2] = "0\0";
int pad_num;
void diplay_pad(){
  switch(display_pad_case){
  case 0:
    break;
  case 1:
    BACKLIGHT = 50000;
    strcpy(display_line[0],"Arrived 0" );
    strcat(display_line[0], pad);
    display_pad_case++;
    display_changed=DISPLAYCHANGED;
    break;
  case 2:
    
    break;
  case 3:
    BACKLIGHT = 0;
    clear_line(0);
    display_pad_case=0;
    pad_num++;
    pad[0]='0'+pad_num;
    display_changed=DISPLAYCHANGED;
    break;
  }
  make_time(timer);
  display_changed=DISPLAYCHANGED;
}
void clear_line(unsigned int line){
  strcpy(display_line[line], "          ");
  display_changed=DISPLAYCHANGED;
}
void clear_display(){
  clear_line(DISPLAY0);
  clear_line(DISPLAY1);
  clear_line(DISPLAY2); 
  clear_line(DISPLAY3);
}
void change_display_line(char *text,int line){ 
  strcpy(display_line[line], text);
  display_changed=DISPLAYCHANGED;
}
void change_display_adc(char *text,unsigned int line){ //MIght be outdated soon
  
  //text[]
  text[4]=' ';
  text[5]=' ';
  text[6]='\0';
  //text[7]='\0';
  switch(line){
  
  case DISPLAY0:
    strcpy(display_line[0],DETECT_L_STRING );
    strcat(display_line[0],text);
    break;
  case DISPLAY1:
    strcpy(display_line[1],DETECT_R_STRING );
    strcat(display_line[1],text);
    break;
  case DISPLAY2:
    strcpy(display_line[2],V_THUMB_STRING );
    strcat(display_line[2],text);
    break;
  case DISPLAY3:
    break;
  default:
    break;
  } 
  display_changed=DISPLAYCHANGED;
}
void main_menu_display(int line){
  strcpy(display_line[DISPLAY0], Wifi_dis);
  strcpy(display_line[DISPLAY1], Adc_disp);
  strcpy(display_line[DISPLAY2], Pid_menu);
  strcpy(display_line[DISPLAY3], Settings_dis);
  switch(line){
  case 0x00:
    display_line[DISPLAY0][0] = '-';
    display_line[DISPLAY0][1] = '>';
    break;
  case 0x01:
    display_line[DISPLAY1][0] = '-';
    display_line[DISPLAY1][1] = '>';
    break;
  case 0x02:
    display_line[DISPLAY2][0] = '-';
    display_line[DISPLAY2][1] = '>';
    break;
  case 0x03:
    display_line[DISPLAY3][0] = '-';
    display_line[DISPLAY3][1] = '>';
    break;
  }
  display_changed=DISPLAYCHANGED;
}
void wifi_move_diplay(char *movement){
  lcd_BIG_mid();
  strcpy(display_line[DISPLAY1], movement);
  display_changed=DISPLAYCHANGED;
}
void adc_display(){ // might be outdated    
    strcpy(display_line[0], V_THUMB_STRING );
    HEXtoBCD(V_Thumb); // Convert result to String
    strcat(display_line[0],adc_char);
    strcat(display_line[0], "   ");
    strcpy(display_line[1], DETECT_L_STRING);
    HEXtoBCD(ADC_Right_Detect); // Convert result to String
    strcat(display_line[1],adc_char);
    strcat(display_line[1], "   ");
    strcpy(display_line[2],DETECT_R_STRING );
    HEXtoBCD(ADC_Left_Detect); // Convert result to String
    strcat(display_line[2],adc_char);
    strcat(display_line[2], "   ");
    display_changed=DISPLAYCHANGED;
}
void line_calibration_display(char color){ // might be outdated  
  switch(color){
  case 'w':
    strcpy(display_line[0], "  White  " );
    break;
  case 'b':
    strcpy(display_line[0], "  Black  " );
	break;  
  }
    strcpy(display_line[1], DETECT_L_STRING);
    HEXtoBCD(ADC_Right_Detect); // Convert result to String
    strcat(display_line[1],adc_char);
    strcat(display_line[1], "   ");
    strcpy(display_line[2],DETECT_R_STRING );
    HEXtoBCD(ADC_Left_Detect); // Convert result to String
    strcat(display_line[2],adc_char);
    strcat(display_line[2], "   ");
    display_changed=DISPLAYCHANGED;
}
void project_7_display(){ // might be outdated  
//    make_time(timer);
//    strcpy(display_line[0], time_disp );
//    strcat(display_line[0], "   ");
    strcpy(display_line[1], DETECT_L_STRING);
    HEXtoBCD(ADC_Right_Detect); // Convert result to String
    strcat(display_line[1],adc_char);
    strcat(display_line[1], "   ");
    strcpy(display_line[2],DETECT_R_STRING );
    HEXtoBCD(ADC_Left_Detect); // Convert result to String
    strcat(display_line[2],adc_char);
    strcat(display_line[2], "   ");
    display_changed=DISPLAYCHANGED;
}
void make_time(unsigned int time_in){
  for(int i=7;i<11;i++){
    display_line[DISPLAY3][i]='0';
  }
  while(time_in > 500){
    display_line[DISPLAY3][7]+=1;
    time_in-=500;
  }
  while(time_in > 50){
    display_line[DISPLAY3][8]+=1;
    //time_disp[1]+=1;
    time_in-=50;
  }
  while(time_in > 5){
    display_line[DISPLAY3][9]+=1;
    //time_disp[2]+=1;
    time_in-=5;
  }
  //time_disp[3]='.';
  
  
  
}
//void project_10_display()