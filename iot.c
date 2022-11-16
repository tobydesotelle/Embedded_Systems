#include "macros.h"
extern volatile unsigned short serial_bits;

#define System_Store0	 ("AT+SYSSTORE=0\r\n")
#define CIPMUX1		 ("AT+CIPMUX=1\r\n")
#define CIPSERVER1	 ("AT+CIPSERVER=1,4200\r\n")
#define Find_IP		 ("AT+CIFSR\r\n")

#define OK		("OK\r\n")
#define IP_found	("WIFI GOT IP\r\n")
char IOT_state=0;
char IOT_state_mem;
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
    send(Find_IP,Send_UCA0);
    IOT_state++;
    break;
  case 8:
    get_IP();
    break;
  }
  
}
