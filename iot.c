#include "macros.h"
extern volatile unsigned short serial_bits;
extern volatile unsigned short display_bits;
extern volatile unsigned char switch_control;
extern volatile unsigned short timer_bits;

extern unsigned char menu_state;
extern char IP_Addy[21];
extern char SSID[64];
extern char Commands[NUM_Commands][NUM_Command_chars];
unsigned int cur_command;
unsigned int commmand_time; 
unsigned short IOT_bits;
unsigned char command_state;
extern unsigned int write_command_line;
unsigned int trim;
extern short timing;
char last_command[6];
#define System_Store0	 ("AT+SYSSTORE=0\r\n")
#define CIPMUX1		 ("AT+CIPMUX=1\r\n")
#define SSID_Find	 ("AT+CWJAP?\r\n")
#define CIPSERVER1	 ("AT+CIPSERVER=1,4200\r\n")
#define Find_IP		 ("AT+CIFSR\r\n")

#define OK		("OK\r\n")
#define IP_found	("WIFI GOT IP\r\n")
#define Start_timmer	(0x54)
#define Trim		(0x59)
#define Display_pad	(0xA4)
#define IOT_Process_next (0x01)
#define Change_Speed	(0xA5)
#define NUM_queues	(50)

unsigned char command_queue[NUM_queues];
unsigned int time_queue[NUM_queues];

unsigned char *add_to_queue=command_queue;
unsigned char *read_command_queue=command_queue;

unsigned int *add_to_time=time_queue;
unsigned int *read_time=time_queue;
unsigned int timerb1_2_cnt;
char IOT_state=0;
char IOT_state_mem;
char Exit;
char char_num[5];
extern char display_pad_case;
unsigned int foward_speed = 8000;
unsigned int right_trim = 500;
unsigned int left_trim = 0;
char Speed_state;
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
void Command_state(){//handle movements and times 
  get_command();
  process_command();
  
  //if(Command_state == 0){//flag new command  and stop command
    switch(*read_command_queue){// Add display 
    case IDLE:
      move(0X00);
      if(display_pad_case == 0){
	change_display_line(" Waiting  ",DISPLAY0);
	//last_command = "     ";
      }
      stop();
      break;
    case ESTOP:
      stop();
      move(0X00);
      do_for(read_command_queue,Process_next,*read_time);
      break;
    case STOP:
      stop();
      //wifi_move_diplay(Stop_display);
      do_for(read_command_queue,Process_next,*read_time);
      break;
    case FORWARD:
//      set_speed(8000);
      set_right_speed(foward_speed+right_trim);//8000
      set_left_speed(foward_speed+left_trim);
      move(FORWARD);
      clear_line(0);
      //change_display_line("f0080",DISPLAY3);
      do_for(read_command_queue,Process_next,*read_time);
      //command_state = Start_timmer;
      break;
    case REVERSE:
      set_speed(8000);
      move(REVERSE);
      //change_display_line("b0080",DISPLAY3);
      //wifi_move_diplay(REVERSE_display);
      do_for(read_command_queue,Process_next,*read_time);
      //command_state = Start_timmer;
      break;
    case CCW:
      set_speed(7000);
      move(CW);
      //change_display_line("r0001",DISPLAY3);
      //wifi_move_diplay(CCW_display);
      do_for(read_command_queue,Process_next,*read_time);
      //command_state = Start_timmer;
      break;
    case CW:
      set_speed(7000);
      move(CCW);
      //change_display_line("l0001",DISPLAY3);
      //wifi_move_diplay(CW_display);
      do_for(read_command_queue,Process_next,*read_time);
      //command_state = Start_timmer;
      break;
    case PID:
      //change_display_line("p9000",DISPLAY3);
      Line_Machine();
      //timing = 1; ------------------------------ timing start
      //do_for(read_command_queue,Process_next,*read_time);
      break;
    case Trim:
      trim+=100;
      do_for(read_command_queue,Process_next,*read_time);
      break;
    case Display_pad:
      //change_display_line("u0000",DISPLAY3);
      diplay_pad_increment();
      do_for(read_command_queue,Process_next,*read_time);
      break;
    case Change_Speed:
      switch(Speed_state){
      case 0:
	foward_speed = 8000;
	right_trim = 500;
	Speed_state++;
	break;
      case 1:
	foward_speed = 30000;
	left_trim = 1000;
	right_trim = 0;
	Speed_state++;
	break;
      case 2:
	foward_speed = 58000;
	left_trim = 3000;
	right_trim = 0;
	Speed_state = 0;
	break;
      }
      do_for(read_command_queue,Process_next,*read_time);
      break;
    case Start_timmer:
      do_for(read_command_queue,Process_next,*read_time);
      break;
    case Process_next:
      stop();
      move(0X00);
      *read_command_queue = RESET;
      *read_time = RESET;
	read_command_queue++;
	read_time++;
	if(read_command_queue - command_queue >= NUM_queues)read_command_queue = command_queue;
	if(read_time- time_queue >= NUM_queues)read_time= time_queue;
      break;
    //}
  }
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
    //get_SSID();
    get_from_serial(SSID);
    break;
  case 9:
    send(Find_IP,Send_UCA0);
    IOT_state++;
    break;
  case 10:
    //get_IP();
    get_from_serial(IP_Addy);
    break;
  case 11:
    process_buffer_0(OK);
    break;
  case 12:
    P3OUT |= IOT_LINK_CPU;
    display_bits |= Display_IP;
    //menu_state = IP_Display;
    IOT_state++;
    break;
  case 13:
    get_connected();
      break;
  case 14:
    serial_bits |= Wifi_connected;
    clear_display();
  }
  
}
void process_command(){ // reads command then adds to the queue
  if(Commands[cur_command][PASSWORD_LENGTH]=='x'){//If currently written is the estop command
    *read_command_queue = ESTOP;
    cur_command++;
  }
  if(Commands[cur_command][PASSWORD_LENGTH]=='w'){//If currently written is the estop command
    Exit=1;
    cur_command++;
  }
  else if(strncmp(Commands[cur_command],PASSWORD,PASSWORD_LENGTH) == 0){
    switch(Commands[cur_command][PASSWORD_LENGTH]){
    case 'f':
      *add_to_queue++ = FORWARD;
      break;
    case 'b':
      *add_to_queue++ = REVERSE;
      break;
    case 'r':
      *add_to_queue++ = CW;
      break;
    case 'l':
      *add_to_queue++ = CCW;
      break;
    case 's':
      *add_to_queue++ = STOP;
      break;
    case 'p':
      *add_to_queue++ = PID;
      break;
    case 'x':
      *add_to_queue++ = Trim;
      break;
    case 'u':
      *add_to_queue++ = Display_pad;
      break;
    case 'c':
      *add_to_queue++ = Change_Speed;
      break;
    }
    
    
    strncpy(char_num,&Commands[cur_command][PASSWORD_LENGTH+1],4);
    
    clear_command();
    
    *add_to_time++ = str_to_int(char_num);  
    cur_command++;
    
    if(cur_command>=NUM_Commands)cur_command = RESET;
    if(add_to_time - time_queue >= NUM_queues)add_to_time = time_queue;
    if(add_to_queue - command_queue >= NUM_queues)add_to_queue = command_queue;

    
    
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
void movement_time(unsigned int time){
  TB1CCTL2 &= ~CCIFG;
  TB1CCTL2 |= CCIE;
  if(timer_bits & Movemet_timer){
    timerb1_2_cnt++;
     timer_bits &= ~Movemet_timer;
    if(timerb1_2_cnt >= time){
     TB1CCTL2 &= ~CCIE;
      timerb1_2_cnt = 0;
      
      command_state = STOP;
    }
  }
}
