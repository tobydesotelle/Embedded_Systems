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


#define Trying_to_connect	(0x00)
void Connecting_machine(){
  switch(connect_state){
  case Trying_to_connect:
    Connecting_Display();
    if(display_bits & Display_IP)connect_state = IP_Display;
    break;
  case IP_Display:
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
void Init_Display_1(void){
    //lcd_BIG_mid();
    strcpy(display_line[DISPLAY0], "Connecting");
    strcpy(display_line[DISPLAY1], "          ");
    //strcpy(display_line[DISPLAY2], "Desotelle ");
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
void serial_display(){
  
  
  
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
void change_display_adc(char *text,unsigned int line){ 
  
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
  strcpy(display_line[DISPLAY0], Settings_dis);
  strcpy(display_line[DISPLAY1], Adc_disp);
  strcpy(display_line[DISPLAY2], Pid_menu);
  strcpy(display_line[DISPLAY3], CLEAR_DISPLAY);
  switch(line){
  case 0x00:
    display_line[DISPLAY0][0] = '-';
    display_line[DISPLAY0][1] = '>';
    break;
  case 0x01:
    display_line[DISPLAY1][0] = '-';
    display_line[DISPLAY1][1] = '>';
    break;
  case 0x03:
  case 0x02:
    display_line[DISPLAY2][0] = '-';
    display_line[DISPLAY2][1] = '>';
    break;
  }
  display_changed=DISPLAYCHANGED;
}
void adc_menu_display(){
  
  
}