#include "bsp.h"
#include "tm4c123gh6pm.h"

void LED_GREEN_ON(){
  GPIO_PORTF_AHB_DATA_BITS_R[LED_Green]|=LED_Green;
}

void LED_GREEN_OFF(){
  GPIO_PORTF_AHB_DATA_BITS_R[LED_Green]&=~(LED_Green);
}

void LED_RED_ON(){
  GPIO_PORTF_AHB_DATA_BITS_R[LED_RED]|=LED_RED;
}

void LED_BLUE_ON(){
   GPIO_PORTF_AHB_DATA_BITS_R[LED_Blue]|=LED_Blue;
}

void LED_BLUE_OFF(){
   GPIO_PORTF_AHB_DATA_BITS_R[LED_Blue]&=~(LED_Blue);
}

void delay(int x){
  int volatile count=x;
  while(count>0){--count;}
  return;
}

void systick_init(){
  NVIC_ST_CTRL_R|=(1U<<2)|(1U<<1)|(1U);
  NVIC_ST_RELOAD_R|=16000000U/2U-1;
  NVIC_ST_CURRENT_R|=0U;
}

void init(){
    
  SYSCTL_RCGCGPIO_R|=(1U<<5);
  SYSCTL_GPIOHBCTL_R|=(1U<<5);
  GPIO_PORTF_AHB_DIR_R |=0x0eU;
  GPIO_PORTF_AHB_DEN_R |=0x0eU; //also can be written to (LED_RED|LED_BLUE|LED_GREEN) which is e (1110)
  
  systick_init();
}