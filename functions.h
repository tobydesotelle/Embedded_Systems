//******************************************************************************
//
//  Description: This file contains the Function prototypes
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************
void main(void);
//===========================Functions to be Sorted=============================
void Display_Process(void);
//void Carlson_StateMachine(void);
void change_display(char *shape);
void ramp_up_to(unsigned int setpoint);
void update_times(void);
void get_command();
void get_from_serial(char *store);
void adc_display();
void wifi_move_diplay(char *movement);
void Connecting_Display(void);
void Connecting_machine();
void pwm_test(unsigned int duty_cycle);
unsigned int duty_cycle(unsigned int input);
char *hex_to_string(unsigned int adc_value);
void ramp_to_setpoint(unsigned int setpoint);
void process_switches(void);
char *get_IP();
char *get_SSID();
void IOT_main();
void line_calibration_display(char color);
void line_calibration();
void HEXtoBCD(unsigned int hex_value);
void wheel_control(unsigned char motor,unsigned char direction);
void idle_case(unsigned char nextState);
void Master_Init(void);
void change_display_adc(char *text,unsigned int line);
void process_detectors(void);
void Wheels_Process(void);
void pid_control();
void display_IP();
void iot_wifi_connect();
void process_buffer_0(char *look_for);
void clear_buffer();
void get_connected();
void clear_command();
void process_command();
char *iot_command(char *command);
int measurment();
void clear_display();
void shape_menu_display(int value);
void song_menu_display();
void song_menu();
void Command_state();
unsigned int str_to_int(char *num_string);
void shape_menu();
void main_menu();
void main_menu_display(int line);
void Init_Display_1(void);
void start_menu();
void menu_state_machine();
void resistor_menu_display(int value);
void resistor_menu();
void waiting_animation();
void v_thumb_process();
void enable_interrupts(void);
void Init_Serial_UCA0(char speed);
void Init_Serial_UCA1(char speed);
void change_display_line(char *text,int line);
void do_for(unsigned char *curState,unsigned char nextState,unsigned int time);
void search(unsigned char nextState);
unsigned short strong_detect();
void on_line_check();
void Init_Display(void);
void clear_line(unsigned int line);
void diplay_IR();
void adc_menu();
void pid_menu();
void settings_menu();
void send(char *string, char port);
//===========================Wheel Control Functions============================
void process_wheels(unsigned short movement_bits);
void stop(void);
void changed_check(unsigned short movement_bits);
void delay_motor(void);
void move(unsigned short movement_bits);
void set_speed(unsigned int speed);
void set_left_speed(unsigned int speed);
void set_right_speed(unsigned int speed);

//---------------------------Movements------------------------------------------




//===========================Initialization=====================================
void Init_Conditions(void);
void Init_LEDs(void);
void Init_Conditions(void);
void Init_ADC(void);
void Init_Clocks(void);
void Init_Timers(void);
void Init_LEDs(void);

// Interrupts
void enable_interrupts(void);
__interrupt void Timer0_B0_ISR(void);
__interrupt void switch_interrupt(void);

// Analog to Digital Converter

// Clocks


// LED Configurations

void IR_LED_control(char selection);
void Backlite_control(char selection);

  // LCD
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void update_string(char *string_data, int string);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);

void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);
//void lcd_draw_time_page(void);
//void lcd_power_off(void);
void lcd_enter_sleep(void);
void lcd_exit_sleep(void);
//void lcd_write(unsigned char c);
//void out_lcd(unsigned char c);

void Write_LCD_Ins(char instruction);
void Write_LCD_Data(char data);
void ClrDisplay(void);
void ClrDisplay_Buffer_0(void);
void ClrDisplay_Buffer_1(void);
void ClrDisplay_Buffer_2(void);
void ClrDisplay_Buffer_3(void);

void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_BIG_bot(void);
void lcd_120(void);

void lcd_4line(void);
void lcd_out(char *s, char line, char position);
void lcd_rotate(char view);

//void lcd_write(char data, char command);
void lcd_write(unsigned char c);
void lcd_write_line1(void);
void lcd_write_line2(void);
void lcd_write_line3(void);

void lcd_command( char data);
void LCD_test(void);
void LCD_iot_meassage_print(int nema_index);

// Menu
void Menu_Process(void);

// Ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char smclk);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);

// SPI
void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);
void WriteIns(char instruction);
void WriteData(char data);

// Switches
void Init_Switches(void);
//void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);
void Init_Switch(void);
void Switch_Process(void);
void Switch1_Process(void);
void Switch2_Process(void);
void menu_act(void);
void menu_select(void);

// Timers
void Init_Timers(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void Init_Timer_B3(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);




