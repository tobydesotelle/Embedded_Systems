#include "macros.h"

extern volatile unsigned short serial_bits;
#define eUCA0_rx                ()


volatile unsigned int usb_rx_ring_wr;
volatile char USB_Char_Rx[SMALL_RING_SIZE];
char temp[2];

char process_buf[NUM_PROCESS_BUF][PROCESS_BUF_LENGTH];
char process_buf_0[NUM_PROCESS_BUF][PROCESS_BUF_LENGTH];
char Ring_buf_0[SMALL_RING_SIZE];
char *Rx_write_0=Ring_buf_0;
char *Rx_read_0;
int line;
int cur_0;
//process 0 is for reciving PC
//process 1 is for reciving IOT
//Process 2 is for Command buffer

char RING_BUF[SMALL_RING_SIZE];
char *RX_write=RING_BUF;
char *RX_read;
unsigned Process_in_cur;

char *Commad_start;
char *Command_end;
char *Tx_String;

int process_line;
unsigned int i;


#define Command_bit      (0x80)

#define Command_Char     ('^')
#define Command_End      (0x0D)
#define Command_LF       ('\n')
#define Test_Command	 ("^^")
#define Fast_Command 	 ("^F")
#define Slow_Command 	 ("^S")


#define CR		 ("\r")
#define NL		 ("\n")


//process_buf_0;

void send(char *string, char port){
  i=0;
  Tx_String = &string[0];
  switch(port){
  case Send_UCA0:
    UCA0IE |= UCTXIE;
    UCA0TXBUF = Tx_String[i++];
    break;
  case Send_UCA1:
    UCA1IE |= UCTXIE;
    UCA1TXBUF = Tx_String[i++];
    break;
  }
  
}
void process_command(char *command){// maybe have a process queue buffer that feeds into a small command.
  //if()
}

void process_buffer_0(char *look_for){
  if(serial_bits & Process_buffer_0){
    if(strcmp(process_buf_0[process_line] , look_for) == 0){
      serial_bits |= Send_next_command;
    }
    serial_bits &= ~Process_buffer_0;
    clear_buffer();
    process_line++;
    if(process_line == NUM_PROCESS_BUF)process_line =RESET;
  }
}
void clear_buffer(){
  for(int j = 0;j<PROCESS_BUF_LENGTH;j++){
    process_buf_0[process_line][j]=RESET;
  }
}
char IP_Addy[16];
char *IP;
char *get_IP(){
  if(serial_bits & Process_buffer_0){
    
      if((IP = strstr(process_buf_0[process_line] , "\""))!=NULL){
	
	IP++;
	
	serial_bits |= Send_next_command;
	int j=0;    
	while(*IP != '\"'){
	  IP_Addy[j]=*IP;
	  IP++;
	  j++;
	}
      }
	  serial_bits &= ~Process_buffer_0;
	  clear_buffer();
	  process_line++;
	  if(process_line == NUM_PROCESS_BUF)process_line =RESET;
  }
	  return IP_Addy;
}
void Init_Serial_UCA0(char speed){

  switch(speed){
  case BAUD115200:
  //------------------------------------------------------------------------------
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
  // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
  //------------------------------------------------------------------------------
  // Configure eUSCI_A0 for UART mode
  UCA0CTLW0 = 0;
  UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA0CTLW0 &= ~UCPEN; // No Parity
  UCA0CTLW0 &= ~UCSYNC;
  UCA0CTLW0 &= ~UC7BIT;
  UCA0CTLW0 |= UCMODE_0;
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  UCA0BRW = 4 ; // 115,200 baud
  UCA0MCTLW = 0x5551 ;
  UCA0CTLW0 &= ~UCSWRST ; // release from reset
  //UCA0TXBUF = 0x00; // Prime the Pump
  UCA0IE |= UCRXIE; // Enable RX interrupt
  break;
  case BAUD460800:
  UCA0CTLW0 = 0;
  UCA0CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA0CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA0CTLW0 &= ~UCPEN; // No Parity
  UCA0CTLW0 &= ~UCSYNC;
  UCA0CTLW0 &= ~UC7BIT;
  UCA0CTLW0 |= UCMODE_0;
  UCA0BRW = 17 ; // 115,200 baud
  UCA0MCTLW = 0x4A00 ;
  UCA0CTLW0 &= ~UCSWRST ; // release from reset
  //UCA0TXBUF = 0x00; // Prime the Pump
  UCA0IE |= UCRXIE; // Enable RX interrupt
  break;
  }
  //------------------------------------------------------------------------------
}
void Init_Serial_UCA1(char speed){
  
  switch(speed){
  case BAUD115200:
  //------------------------------------------------------------------------------
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 4800 1 104 2 0xD6 -0.08 0.04 -0.10 0.14
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  // 8000000 19200 1 26 0 0xB6 -0.08 0.16 -0.28 0.20
  // 8000000 57600 1 8 10 0xF7 -0.32 0.32 -1.00 0.36
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
  //------------------------------------------------------------------------------
  // Configure eUSCI_A0 for UART mode
  UCA1CTLW0 = 0;
  UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA1CTLW0 &= ~UCPEN; // No Parity
  UCA1CTLW0 &= ~UCSYNC;
  UCA1CTLW0 &= ~UC7BIT;
  UCA1CTLW0 |= UCMODE_0;
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 115200 1 4 5 0x55 -0.80 0.64 -1.12 1.76
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  UCA1BRW = 4 ; // 115,200 baud
  UCA1MCTLW = 0x5551 ;
  UCA1CTLW0 &= ~UCSWRST ; // release from reset
 // UCA1TXBUF = 0x00; // Prime the Pump
  UCA1IE |= UCRXIE; // Enable RX interrupt
  break;
  case BAUD460800:
  UCA1CTLW0 = 0;
  UCA1CTLW0 |= UCSWRST ; // Put eUSCI in reset
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 &= ~UCMSB; // MSB, LSB select
  UCA1CTLW0 &= ~UCSPB; // UCSPB = 0(1 stop bit) OR 1(2 stop bits)
  UCA1CTLW0 &= ~UCPEN; // No Parity
  UCA1CTLW0 &= ~UCSYNC;
  UCA1CTLW0 &= ~UC7BIT;
  UCA1CTLW0 |= UCMODE_0;
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 460800 0 17 0 0x4A -2.72 2.56 -3.76 7.28
  // UCA?MCTLW = UCSx + UCFx + UCOS16
  UCA1BRW = 17 ;
  UCA1MCTLW = 0x4A00 ;
  UCA1CTLW0 &= ~UCSWRST ; // release from reset
  UCA1TXBUF = 0x00; // Prime the Pump
  UCA1IE |= UCRXIE; // Enable RX interrupt
  break;
  }
  //------------------------------------------------------------------------------
}
char test_output[11];
#pragma vector=EUSCI_A0_VECTOR//To IOT
__interrupt void EUSCI_A0_ISR(void){
  
  switch(__even_in_range(UCA0IV,0x08)){ // Bruh IDK what I did here needs to be fixed
  case 0: // Vector 0 - no interrupt
    break;
  case 2: // Vector 2 - RXIFG
    
  //UCA1TXBUF=UCA0RXBUF;
  *Rx_write_0 = UCA0RXBUF;
  Rx_read_0 = Rx_write_0;
  Rx_write_0++;
  UCA1TXBUF = *Rx_read_0;
  if(Rx_write_0-Ring_buf_0 == SMALL_RING_SIZE)Rx_write_0 = Ring_buf_0;
  if(*Rx_read_0 == '\n'){
    process_buf_0[line][cur_0++]=*Rx_read_0;
    *Rx_read_0 = RESET;
    line++;
    cur_0 = 0;
    serial_bits |= Process_buffer_0;
    if(line == NUM_PROCESS_BUF)line = 0;
  }else{
    process_buf_0[line][cur_0++]=*Rx_read_0;
    *Rx_read_0 = RESET;
  }
  
  
  
	//we want to capture in a process buf if something found
      
    
    
      
    break;
  case 4: // Vector 4 – TXIFG
    if( Tx_String[i]=='\0'){//If the end of a string add line feed and turn off Tx
      UCA0IE &= ~UCTXIE;
      //UCA0TXBUF = '\r';
    //}//else if(Tx_String[i]=='\r'){
      //UCA0IE &= ~UCTXIE;
    }else{// keep chars going
      UCA0TXBUF = Tx_String[i++];
    }
    break;
  default: break;
  }
}



#pragma vector=EUSCI_A1_VECTOR//PC Communication
__interrupt void EUSCI_A1_ISR(void){
  switch(__even_in_range(UCA1IV,0x08)){
  case 0: // Vector 0 - no interrupt
    break;
  case 2: // Vector 2 - RXIFG
    					//Need to save the rx to send to the UCA0 (IOT)
    *RX_write =  UCA1RXBUF;		//Store UCA1RXBUF into current ring buf location
    RX_read = RX_write;			// set read to the current write
    RX_write++;				// increment write location
    if(RX_write - RING_BUF == SMALL_RING_SIZE) RX_write = RING_BUF;//processing Ring_buf overflow seting it back to start
    if(*RX_read == Command_Char)serial_bits |= Command_bit;//If command Start is found
    if((*RX_read == Command_End || *RX_read == Command_LF) && serial_bits & Command_bit ){//if Command end is found
      serial_bits &= ~Command_bit;
      strncpy(process_buf[2],process_buf[0],Process_in_cur);
      Process_in_cur = 0;
      serial_bits |= Process_command;	//SET PROCESS COMMAND BIT
      //send(process_buf[0],Send_UCA0);
    }  
    else if(serial_bits & Command_bit){//processing command when it is found
      process_buf[0][Process_in_cur] = *RX_read;
        Process_in_cur++;
    }else if(*RX_read != '\0' /*|| *RX_read !=*/ ){
      UCA0TXBUF = *RX_read;
      //send(IOT_char[0],Send_UCA0);
    }else{
      UCA0TXBUF = '\r';
    }
    //UCA0TXBUF = temp;
    serial_bits |= Serial_off;
    break;
  case 4: // Vector 4 – TXIFG
    if(Tx_String[i]=='\0' /*|| Tx_String[i]=='\n'*/ ){//If the end of a string add line feed and turn off Tx
        UCA1TXBUF = '\n';
        UCA1IE &= ~UCTXIE;
    }else{// keep chars going
      UCA1TXBUF = Tx_String[i++];
    }
    break;
  
  }
}