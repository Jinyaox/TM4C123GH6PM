#ifndef __BSP__
#define __BSP__

void UART_TX(char c);
void UART_SETUP(void);
char UART_RX(void);
void print_str(char*);
void BUTTON_SETUP(void);
void get_command(char*, int);

#endif
