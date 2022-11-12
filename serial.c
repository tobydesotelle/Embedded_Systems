#include "macros.h"

extern volatile unsigned short serial_bits;
#define eUCA0_rx                ()


volatile unsigned int usb_rx_ring_wr;
volatile char USB_Char_Rx[SMALL_RING_SIZE];
char temp;
//char process_buf_back[32];
//char process_buf_front[32];
char process_buf_rx[PROCESS_BUF_LENGTH];
char process_buf_tx[PROCESS_BUF_LENGTH];
int count=0;
char RING_BUF_A0[SMALL_RING_SIZE];
char *rx_start;
char TX_A1[SMALL_RING_SIZE];
char *TX_char=process_buf_rx; 

char *RX_write=RING_BUF_A0;
char *RX_read;

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
  //UCA1TXBUF = 0x00; // Prime the Pump
  UCA1IE |= UCRXIE; // Enable RX interrupt
  break;
  }
  //------------------------------------------------------------------------------
}
char test_output[11];
#pragma vector=EUSCI_A0_VECTOR
__interrupt void EUSCI_A0_ISR(void){
  
  switch(__even_in_range(UCA0IV,0x08)){ // Bruh IDK what I did here needs to be fixed
  case 0: // Vector 0 - no interrupt
    break;
  case 2: // Vector 2 - RXIFG
    serial_bits = SERIAL_RX;
    *RX_write = UCA0RXBUF;// Writes UCA0RXBUF to current RING_BUF_A0 location
    count++;
    if(*RX_write != '\0' && rx_start == NULL){
      rx_start = RX_write;
      count = 0;
    }
    RX_write++;
    if(*(RX_write-1) == '\n' || count == 10){
      RX_write--;
      for(int i=0; i<SMALL_RING_SIZE; i++){
        if(rx_start == RX_write && i < PROCESS_BUF_LENGTH){
          process_buf_rx[i] = ' ';
        }
        else if(rx_start == RX_write){
          process_buf_rx[i] = '\0';
        } 
        else{
          if(rx_start == RING_BUF_A0+SMALL_RING_SIZE){
            rx_start = RING_BUF_A0;
          }
          process_buf_rx[i] = *(rx_start);
          rx_start++;
        }
      }
      serial_bits &= ~rx_buff_update;
      rx_start = NULL;
      RX_write++;
    }
    if(RX_write == RING_BUF_A0+SMALL_RING_SIZE){
      RX_write = RING_BUF_A0;
    }
    
    break;
  case 4: // Vector 4 – TXIFG
    serial_bits = SERIAL_TX;
    if(*TX_char=='\0'){
      UCA0TXBUF = '\n';
      UCA0IE &= ~UCTXIE;
      //TX_char=TX_A1;
      serial_bits |= tx_buff_update;
      TX_char=process_buf_rx;
    }
      else{
        //UCA0IE &= ~UCTXIE; //<=====
        UCA0TXBUF = *TX_char;
        TX_char++;
      }
    break;
  default: break;
  }
}
#pragma vector=EUSCI_A1_VECTOR
  __interrupt void EUSCI_A1_ISR(void){
  switch(__even_in_range(UCA1IV,0x08)){
  case 0: // Vector 0 - no interrupt
  break;
  case 2: // Vector 2 - RXIFG
  temp =  UCA1RXBUF;
  UCA1TXBUF = temp;
  serial_bits |= Serial_off;
  break;
  case 4: // Vector 4 – TXIFG
  if(serial_bits & Serial_off){//check to see if we recived something first
  break;
  }else{
    
  }
  }
  }
//      switch(baud){
//      case BAUD115200:
//        change_display_line( BAUD115200_STRING,DISPLAY2);
//        //sw2 buton press switch to 460800
//        //sw1 button press transmit current process buffer
//        if(SW1_AND_TOGGLED){
//          SW1_CLEAR;
//          serial_bits = SERIAL_TX; // Sets the flag to chage current buffer in main.
//          //x   strcpy(process_buf_tx,process_buf_rx);
//          UCA0IE |= UCTXIE;
//          //UCA0TXBUF = '\0';
//          //move rx string to tx position
//        }
//        if(SW2_AND_TOGGLED){
//          SW2_CLEAR;
//          baud=BAUD460800;
//          Init_Serial_UCA0(BAUD460800);
//        }
//        break;
//      case BAUD460800:
//        change_display_line( BAUD460800_STRING,DISPLAY2);
//        if(SW1_AND_TOGGLED){
//          SW1_CLEAR;
//          UCA0IE |= UCTXIE;
//          //UCA0TXBUF = '\0';
//        }
//        if(SW2_AND_TOGGLED){
//          SW2_CLEAR;
//          baud=BAUD115200;
//          Init_Serial_UCA0(BAUD115200);
//        }
//        break;
//        
//      }
//      // have two buffer a display buffer and a write buffer.
//      if(update_display==UPDATED){
//        switch(serial_bits&0x7){
//        case SERIAL_WAITING:
//          
//          waiting_animation();
//          
//          break;
//        case SERIAL_RX:
//          change_display_line(RECIVED,DISPLAY0);
//          clear_line(DISPLAY1);
//          change_display_line(process_buf_rx,DISPLAY3);
//          break;
//        case SERIAL_TX:
//          change_display_line(TRASMIT,DISPLAY0);
//          clear_line(DISPLAY3);
//          change_display_line(process_buf_rx,DISPLAY1);
//          break;
//        default:
//          serial_bits = SERIAL_WAITING;
//          break;
//        }
//      }
//    