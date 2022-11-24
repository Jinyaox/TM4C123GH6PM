#include "tm4c123gh6pm.h"

void GPIOA_SETUP(){
  SYSCTL_RCGCGPIO_R|=SYSCTL_RCGCGPIO_R0;
  while(!((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R0)==SYSCTL_RCGCGPIO_R0));
  UART0_CTL_R &=(~UART_CTL_UARTEN);
  GPIO_PORTA_DEN_R=0x03U;
  GPIO_PORTA_AFSEL_R=0x03U;
  GPIO_PORTA_PCTL_R=0x11;
  
  //end of GPIOA configuration
}


void UART_SETUP(){
  SYSCTL_RCGCUART_R|=0x01;
  while(!((SYSCTL_RCGCUART_R & SYSCTL_RCGCUART_R0)==SYSCTL_RCGCUART_R0));
  GPIOA_SETUP();

  UART0_CTL_R &=(~UART_CTL_UARTEN);


  //set baud rate
  UART0_IBRD_R=104;
  UART0_FBRD_R=11;
  
  //set bit, parity, stopbit, ~FIFO
  UART0_CC_R=0; //use default clock
  UART0_LCRH_R=0x60;
  
  UART0_CTL_R|=(UART_CTL_RXE|UART_CTL_TXE|UART_CTL_UARTEN);

  /*UART Interruption Setup!!!*/
  UART0_ICR_R |=(1<<4)|(1<<5);
  UART0_IM_R  |=(1<<4)|(0<<5);
  NVIC_EN0_R  |=(1<<5);
}


void UART_TX(char c){
  while((UART0_FR_R & 0x20) !=0);
  UART0_DR_R=c;
}

char UART_RX(void)  {    
  char data;  
  while((UART0_FR_R & (1<<4)) != 0); /* wait until Rx buffer is not full */    
  data = UART0_DR_R ;  /* before giving it another byte */    
  return (unsigned char) data; 
}

void print_str(char* str){
  int cursor=0;
  while(str[cursor]!='\0'){
    UART_TX(str[cursor]);
    cursor++;
  }
  return;
}


void BUTTON_SETUP(void){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF;
    GPIO_PORTF_LOCK_R=0x4C4F434B;
    GPIO_PORTF_CR_R|=0x01;
    GPIO_PORTF_LOCK_R=0;

    //PF0 and PF4 are input pins
    GPIO_PORTF_DIR_R &= ~(1<<4)|~(1<<0);
    GPIO_PORTF_DIR_R |=(1<<3);
    __asm__ volatile("  .byte 0x1, 0xE0\n" //need to modify this b  0x3
            "   add sp,sp,#0x100\n"
            "   add sp,sp,#0x100\n"
            );
    GPIO_PORTF_DEN_R |= (1<<4)|(1<<3)|(1<<0);
    GPIO_PORTF_PUR_R |= (1<<4)|(1<<0);

    GPIO_PORTF_IS_R &= ~(1<<4)|~(1<<0);
    __asm__ volatile (" .byte 0x9F,0xF8, 0xDF,0xF5\n"); //f89ff5df instrc
    GPIO_PORTF_IBE_R &=~(1<<4)|~(1<<0);
    GPIO_PORTF_IEV_R &= ~(1<<4)|~(1<<0);
    GPIO_PORTF_ICR_R |= (1<<4)|(1<<0);
    GPIO_PORTF_IM_R  |= (1<<4)|(1<<0);


    NVIC_EN0_R|= (1<<30);
    return;
}

void get_command(char buf[],int max_len){
  char c;
  int counter=0;
  do{
    c=UART_RX();
    buf[counter]=c;
    counter++;
  }while((c!=0x0d)&&(counter<max_len));
  return;
}
