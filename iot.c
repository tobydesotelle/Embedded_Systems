#include "macros.h"
extern volatile unsigned short serial_bits;
extern volatile unsigned short display_bits;
extern volatile unsigned char switch_control;
extern volatile unsigned short timer_bits;

extern unsigned char menu_state;
extern char IP_Addy[21];
extern char SSID[11];
extern char Commands[NUM_Commands][NUM_Command_chars];
unsigned int cur_command;
unsigned int commmand_time; 
unsigned short IOT_bits;
unsigned char command_state;
#define System_Store0	 ("AT+SYSSTORE=0\r\n")
#define CIPMUX1		 ("AT+CIPMUX=1\r\n")
#define SSID_Find	 ("AT+CWJAP?\r\n")
#define CIPSERVER1	 ("AT+CIPSERVER=1,4200\r\n")
#define Find_IP		 ("AT+CIFSR\r\n")

#define OK		("OK\r\n")
#define IP_found	("WIFI GOT IP\r\n")
#define Start_timmer	(0x54)
#define Process_next	(0x55)
#define IOT_Process_next (0x01)

char IOT_state=0;
char IOT_state_mem;
void IOT_main(){
    P3OUT |= IOT_EN_CPU;
  while(!(serial_bits & Wifi_connected) ){
    Connecting_machine();
    iot_wifi_connect();
    Display_Process();
  }
  SW1_CLEAR;
  SW2_CLEAR;
  menu_state = Main_menu;
  IOT_bits |= IOT_Process_next;
}

void iot_wifi_connect(){
  if(serial_bits & Send_next_command){
    IOT_state++;
    serial_bits &= ~Send_next_command;
  }
  switch(IOT_state){
  case 0://add timerfor timing out finding
    process_buffer_0(IP_found);
    break;
  case 1:
    send(System_Store0,Send_UCA0);
    IOT_state++;
    break;
  case 2://check for okay process
    process_buffer_0(OK);
    break;
  case 3:
    send(CIPMUX1,Send_UCA0);
    IOT_state++;
    break;
  case 4:
    process_buffer_0(OK);
    break;
  case 5:
    send(CIPSERVER1,Send_UCA0);
    IOT_state++;
    break;
  case 6:
    process_buffer_0(OK);
    break;
  case 7:
    send(SSID_Find,Send_UCA0);
    IOT_state++;
    break;
  case 8:
    get_SSID();
    break;
  case 9:
    send(Find_IP,Send_UCA0);
    IOT_state++;
    break;
  case 10:
    get_IP();
    break;
  case 11:
    process_buffer_0(OK);
    break;
  case 12:
    P3OUT |= IOT_LINK_CPU;
    display_bits |= Display_IP;
    menu_state = IP_Display;
    IOT_state++;
    break;
  case 13:
    get_connected();
      break;
  case 14:
    serial_bits |= Wifi_connected;
  }
  
}
void process_command(){
  
  if(strncmp(Commands[cur_command],PASSWORD,PASSWORD_LENGTH) == 0){
    if(Commands[cur_command][PASSWORD_LENGTH]=='s'){
      command_state = 0;
	stop();
	
    }
    if(IOT_bits & IOT_Process_next){
      switch(Commands[cur_command][PASSWORD_LENGTH]){
      case 'f':
	command_state = FORWARD;
	break;
      case 'b':
	command_state = REVERSE;
	break;
      case 'r':
	command_state = CW;
	break;
      case 'l':
	command_state = CCW;
	break;
      case 's':
	command_state = 0;
	stop();
	break;
      }
      IOT_bits &= ~IOT_Process_next;
      
    }
    char char_num[5];
    strncpy(char_num,&Commands[cur_command][PASSWORD_LENGTH+1],4);
    commmand_time =str_to_int(char_num);  
    clear_command();
    cur_command++;
    if(cur_command>=NUM_Commands)cur_command = RESET;
    //now get length of time to do 
    
    
  }
  else{
    //clear_command();
    //cur_command++;
  }
}
unsigned int str_to_int(char *num_string){
  int sum=0;
  sum+=1000*((unsigned int)(num_string[0]-'0'));
  sum+=100*((unsigned int)(num_string[1]-'0'));
  sum+=10*((unsigned int)(num_string[2]-'0'));
  sum+=1*((unsigned int)(num_string[3]-'0'));
  return sum;
}
void clear_command(){
  for(int j = 0;j<NUM_Command_chars;j++){
    Commands[cur_command][j]=RESET;
  }
}
void Command_state(){//handle movements and times 
  process_command();
  //if(Command_state == 0){//flag new command  and stop command
    switch(command_state){
    case 0:
      IOT_bits |= IOT_Process_next;
      stop();
      break;
    case FORWARD:
      move(FORWARD);
      do_for(&command_state,Process_next,commmand_time);
      //command_state = Start_timmer;
      break;
    case REVERSE:
      move(REVERSE);
      do_for(&command_state,Process_next,commmand_time);
      //command_state = Start_timmer;
      break;
    case CCW:
      move(CW);
      do_for(&command_state,Process_next,commmand_time);
      //command_state = Start_timmer;
      break;
    case CW:
      move(CCW);
      do_for(&command_state,Process_next,commmand_time);
      //command_state = Start_timmer;
      break;
    case Start_timmer:
      do_for(&command_state,Process_next,commmand_time);
      break;
    case Process_next:
      cur_command++;
      IOT_bits |= IOT_Process_next;
      command_state = 0;
      break;
    //}
  }
  IOT_bits |= IOT_Process_next;
}
unsigned int timerb1_2_cnt;
void movement_time(unsigned int time){
  TB1CCTL2 &= ~CCIFG;
  TB1CCTL2 |= CCIE;
  if(timer_bits & Movemet_timer){
    timerb1_2_cnt++;
     timer_bits &= ~Movemet_timer;
    if(timerb1_2_cnt >= time){
     TB1CCTL2 &= ~CCIE;
      timerb1_2_cnt = 0;
      
      command_state = 0;
    }
  }
}
//void do_for(unsigned char *curState,unsigned char nextState,unsigned int time){
//  if((TB1CCTL1&CCIE)!=CCIE){
//  TB1CCTL1 &= ~CCIFG;
//  TB1CCTL1 |= CCIE;
//  time100=0;
//  }
//  if(timer_bits&TB1CCR1_BIT){
//    time100++;
//    timer_bits &= ~TB1CCR1_BIT;
//  }
//  if(time100>=time){
//    *curState=nextState;
//    time100=0;
//    TB1CCTL1 &= ~CCIE;
//  }
//}