#include "bsp.h"
#include "Miros.h"
#include <stdint.h>
#include "core_cmFunc.h"
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

void systick_init(){
  NVIC_ST_CTRL_R|=(1U<<2)|(1U<<1)|(1U);
  NVIC_ST_RELOAD_R|=16000000U/2U-1;
  NVIC_ST_CURRENT_R|=0U;
}

void OS_onStartup(void){
  SYSCTL_RCGCGPIO_R|=(1U<<5);
  SYSCTL_GPIOHBCTL_R|=(1U<<5);
  GPIO_PORTF_AHB_DIR_R |=0x0eU;
  GPIO_PORTF_AHB_DEN_R |=0x0eU; //also can be written to (LED_RED|LED_BLUE|LED_GREEN) which is e (1110)
  
  systick_init();
}
  

void __stackless delay(int x){
  __asm("PUSH        {r7,LR}");
  extern OSthread* OS_Current;
  extern uint32_t OS_readyset;
  extern uint32_t OS_curridx;
  
  __disable_irq();
  OS_Current->timeout=x;
  OS_readyset&=~(1U<<(OS_curridx-1U));
  OS_Sched();
  __asm("POP        {r7,LR}");
  __enable_irq();
}

void init(){
    
  SYSCTL_RCGCGPIO_R|=(1U<<5);
  SYSCTL_GPIOHBCTL_R|=(1U<<5);
  GPIO_PORTF_AHB_DIR_R |=0x0eU;
  GPIO_PORTF_AHB_DEN_R |=0x0eU; //also can be written to (LED_RED|LED_BLUE|LED_GREEN) which is e (1110)
  
  systick_init();
}