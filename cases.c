#include "macros.h"

extern volatile unsigned int time_changed;


extern unsigned int started;

extern unsigned char state;
extern unsigned char event;

unsigned int delay_start;
unsigned int times_repeated;

extern volatile unsigned char switch_control;
extern volatile unsigned short timer_bits;
extern unsigned short line_detection;

unsigned int time100;

void idle_case(unsigned char nextState){
  //This will wait until SW1 is pressed.
  if(switch_control&SW1_TOGGLED)state=nextState;
  switch_control &= ~SW1_TOGGLED;
}

//void find_line(unsigned char nextstate){
//  //this will stop the car when line is detected
//  
//  
//}
void do_for(unsigned char *curState,unsigned char nextState,unsigned int time){
  if((TB1CCTL1&CCIE)!=CCIE){
  TB1CCTL1 &= ~CCIFG;
  //TB1CCR1+=TB1CCR1_INTERVAL;
  TB1CCTL1 |= CCIE;
  time100=0;
  }
  if(timer_bits&TB1CCR1_BIT){
    time100++;
    timer_bits &= ~TB1CCR1_BIT;
  }
  if(time100>=time){
    *curState=nextState;
    time100=0;
    TB1CCTL1 &= ~CCIE;
  }
}

void search(unsigned char nextState){
  if(line_detection!=0x11){
    state=nextState;
  }
}
void delay();

void wait_case(unsigned char nextState){
 //if(half_seconds==1){
  
 //}
}
void next_state(unsigned int duration,unsigned char nextState){
  
}
void start_case(unsigned char nextState){
 //move_forward();
 state = nextState;
}

void repeat_case(unsigned char repeatState,unsigned char nextState,unsigned int repeat_times){
  if(times_repeated==repeat_times){
    state=nextState;
  }else{
    times_repeated++;
    state=repeatState;
  }
}
void end_case(unsigned char nextEvent){
 stop();
 delay_start=RESET_STATE;
 times_repeated=RESET_STATE;
 //state = WAIT;
 event = nextEvent;
}
//Diffrent Motions
//void Run_Straight(void){
// switch(state){
//   case WAIT: // Begin
//       wait_case(START);
//       break; //
//     case START: // Begin
//       start_case(RUN);
//       break; //
//     case RUN: // Run
//       run_case(END);
//       break; //
//     case END: // End
//       end_case(WAIT);
//       break; //
//     default:
//       state=WAIT;
//       break;
// }
//}