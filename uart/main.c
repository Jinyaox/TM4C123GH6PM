#include "tm4c123gh6pm.h"
#include <stdint.h>

void GPIOA_SETUP(){
  SYSCTL_RCGCGPIO_R|=1;
  GPIO_PORTA_AFSEL_R=0x03;
  GPIO_PORTA_PCTL_R=0x11;
  
  //enable gpio pin as digital I/O
  GPIO_PORTA_DEN_R=0x03;
  
  //end of GPIOA configuration
}

void UART_SETUP(){
  SYSCTL_RCGCUART_R|=1;
  UART0_CTL_R=0x00;
  
  //set baud rate
  UART0_IBRD_R=104;
  UART0_FBRD_R=11;
  
  //set bit, parity, stopbit, ~FIFO
  UART0_LCRH_R=0x60;
  UART0_CC_R=0; //use default clock
  
  UART0_CTL_R=0x301; //enable the uart0, tx, rx
}

void UART_TX(char c){
  while((UART0_FR_R & 0x20) !=0){UART0_DR_R=c;}
}

void delay(int n){
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<3180;j++){
      {}
    }
  }
}

int main()
{
  GPIOA_SETUP();
  UART_SETUP();
  delay(1);
  
  for (;;)
    {
      UART_TX('Y');
    }
  return 0;
}