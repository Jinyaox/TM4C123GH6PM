#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "Miros.h"
#include "bsp.h"

uint32_t stack_main1[40];
OSthread sp_main1;

void __stackless main1(){
  while(1){
    LED_GREEN_ON();
    delay(10);
    LED_GREEN_OFF();
    delay(10);
  }
  
}

uint32_t stack_main2[40];
OSthread sp_main2;

void __stackless main2(){
  while(1){
    LED_BLUE_ON();
    delay(10);
    LED_BLUE_OFF();
    delay(10);
  }
}

uint32_t stack_idle[40];

//this is the main background loop!!!
int main(){
  OS_init(stack_idle,sizeof(stack_idle));
  
  OSthread_start(&sp_main1,&main1,stack_main1,sizeof(stack_main1));
  
  OSthread_start(&sp_main2,&main2,stack_main2,sizeof(stack_main2));
  
  OS_run(); //transfer control to RTOS to run all the threads

  return 0;
}
