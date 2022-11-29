#include "macros.h"
#define	ADC_AVG		(5)
//extern volatile unsigned int ADC_Left_Detect;
unsigned int ADC_Left_Detect;
unsigned int ADC_Right_Detect;
unsigned int V_Thumb;
//unsigned int Right_detect[ADC_AVG];
//unsigned int Left_detect[ADC_AVG];
//unsigned int V_Thumb_arry[ADC_AVG];
char adc_char[5];
unsigned int ADC_Channel=0;

void Init_ADC(void){
  //------------------------------------------------------------------------------
  // V_DETECT_L (0x04) // Pin 2 A2
  // V_DETECT_R (0x08) // Pin 3 A3
  // V_THUMB (0x20) // Pin 5 A5
  //------------------------------------------------------------------------------
  // ADCCTL0 Register
  ADCCTL0 = RESET_STATE; // Reset
  ADCCTL0 |= ADCSHT_2; // 16 ADC clocks
  ADCCTL0 |= ADCMSC; // MSC
  ADCCTL0 |= ADCON; // ADC ON
  
  // ADCCTL1 Register
  ADCCTL2 = RESET_STATE; // Reset
  ADCCTL1 |= ADCSHS_0; // 00b = ADCSC bit
  ADCCTL1 |= ADCSHP; // ADC sample-and-hold SAMPCON signal from sampling timer.
  ADCCTL1 &= ~ADCISSH; // ADC invert signal sample-and-hold.
  ADCCTL1 |= ADCDIV_0; // ADC clock divider - 000b = Divide by 1
  ADCCTL1 |= ADCSSEL_0; // ADC clock MODCLK
  ADCCTL1 |= ADCCONSEQ_0; // ADC conversion sequence 00b = Single-channel single-conversion
  // ADCCTL1 & ADCBUSY identifies a conversion is in process
  
  // ADCCTL2 Register
  ADCCTL2 = RESET_STATE; // Reset
  ADCCTL2 |= ADCPDIV0; // ADC pre-divider 00b = Pre-divide by 1
  ADCCTL2 |= ADCRES_2; // ADC resolution 10b = 12 bit (14 clock cycle conversion time) was ADCRES_0
  ADCCTL2 &= ~ADCDF; // ADC data read-back format 0b = Binary unsigned.
  ADCCTL2 &= ~ADCSR; // ADC sampling rate 0b = ADC buffer supports up to 200 ksps
  // ADCMCTL0 Register
  ADCMCTL0 |= ADCSREF_0; // VREF - 000b = {VR+ = AVCC and VR– = AVSS }
  ADCMCTL0 |= ADCINCH_5; // V_THUMB (0x20) Pin 5 A5
  ADCIE |= ADCIE0; // Enable ADC conv complete interrupt
  ADCCTL0 |= ADCENC; // ADC enable conversion.
  ADCCTL0 |= ADCSC; // ADC start conversion.
}
#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
  case ADCIV_NONE:
    break;
  case ADCIV_ADCOVIFG: // When a conversion result is written to the ADCMEM0
    // before its previous conversion result was read.
    break;
  case ADCIV_ADCTOVIFG: // ADC conversion-time overflow
    break;
  case ADCIV_ADCHIIFG: // Window comparator interrupt flags
    break;
  case ADCIV_ADCLOIFG: // Window comparator interrupt flag
    break;
  case ADCIV_ADCINIFG: // Window comparator interrupt flag
    break;
  case ADCIV_ADCIFG: // ADCMEM0 memory register with the conversion result
    ADCCTL0 &= ~ADCENC; // Disable ENC bit.
    switch (ADC_Channel++){
    case GET_V_THUMB: // Channel A2 Interrupt
      ADCMCTL0 &= ~ADCINCH_5; // Disable Last channel A2
      ADCMCTL0 |= ADCINCH_2; // Enable Next channel A3
      V_Thumb = ADCMEM0; // Move result into Global
      V_Thumb = V_Thumb; // Divide the result by 4
      P2OUT|=IR_LED;
      break;
    case GET_L_DETECT:
       ADCMCTL0 &= ~ADCINCH_2; // Disable Last channel A2
      ADCMCTL0 |= ADCINCH_3; // Enable Next channel A3
      ADC_Right_Detect = ADCMEM0; // Move result into Global
      ADC_Right_Detect = ADC_Right_Detect; // Divide the result by 4
      HEXtoBCD(ADC_Right_Detect); // Convert result to String
      //change_display_adc(adc_char,DISPLAY0); // Place String in Display
      break;
    case GET_R_DETECT:
      ADCMCTL0 &= ~ADCINCH_3; // Disable Last channel A2
      ADCMCTL0 |= ADCINCH_5; // Enable Next channel A3
      ADC_Left_Detect = ADCMEM0; // Move result into Global
      ADC_Left_Detect = ADC_Left_Detect; // Divide the result by 4
      HEXtoBCD(ADC_Left_Detect); // Convert result to String
      //change_display_adc(adc_char,DISPLAY1); // Place String in Display
      ADC_Channel=RESET_STATE;
      P2OUT&=~IR_LED;
      break;
    default:
      break;
    }
//    ADCCTL0 |= ADCENC; // Enable Conversions
//    ADCCTL0 |= ADCSC; // Start next sample
    break;
  default:
    break;
  }
}
//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
void HEXtoBCD(unsigned int hex_value){
  unsigned int value=0;
  for(int i=RESET_STATE; i < adc_num_chars; i++) {
    adc_char[i] = CHAR_0;
  }
  while (hex_value > Above_999){
    hex_value = hex_value - (Above_999+add_one);
    value = value + add_one;
    adc_char[adc_c_0] = CHAR_0 + value;
  }
  value = RESET_STATE;
  while (hex_value > Above_99){
    hex_value = hex_value - (Above_99+add_one);
    value = value + add_one;
    adc_char[adc_c_1] = CHAR_0 + value;
  }
  value = RESET_STATE;
  while (hex_value > Above_9){
    hex_value = hex_value - (Above_9+add_one);
    value = value + add_one;
    adc_char[adc_c_2] = CHAR_0 + value;
  }
  adc_char[adc_c_3] = CHAR_0 + hex_value;
  adc_char[4] = '\0';
}


//char *hex_to_string(unsigned int adc_value){
//  unsigned int value;
//  char ret[adc_num_chars+1];
//  for(int i=RESET_STATE; i < adc_num_chars; i++) {
//    ret[i] = CHAR_0;
//  }
//  while (adc_value > Above_999){
//    adc_value = adc_value - (Above_999+add_one);
//    value = value + add_one;
//    ret[adc_c_0] = CHAR_0 + value;
//  }
//  value = RESET_STATE;
//  while (adc_value > Above_99){
//    adc_value = adc_value - (Above_99+add_one);
//    value = value + add_one;
//    ret[adc_c_1] = CHAR_0 + value;
//  }
//  value = RESET_STATE;
//  while (adc_value > Above_9){
//    adc_value = adc_value - (Above_9+add_one);
//    value = value + add_one;
//    ret[adc_c_2] = CHAR_0 + value;
//  }
//  ret[adc_c_3] = CHAR_0 + adc_value;
//  ret[adc_num_chars] = '\0';
//  return ret;
//}