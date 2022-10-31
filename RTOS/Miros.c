#include <stdint.h>
#include "Miros.h"
#include "bsp.h"
#include "core_cmFunc.h"

OSthread * volatile OS_Current; //pointer to the current thread object
OSthread * volatile OS_Next;

void OS_init(void){
  *(uint32_t volatile*)0xE000ED20|=(0xFFU<<16);
}

void OS_Sched(void){
  extern OSthread sp_main1;
  extern OSthread sp_main2;
  
  if(OS_Current==&sp_main1){
    OS_Next=&sp_main2;
  }
  else{OS_Next=&sp_main1;}

  if (OS_Next != OS_Current){
    *(uint32_t volatile*)0xE000ED04 = (1U<<28); //triggers the PendSV interruption
  }
}

void OSthread_start(OSthread *me, OSthreadHandler threadHandler, void* stack, uint32_t stack_size)
{
  //stack grows from high to low and align by 8
  
  uint32_t *sp=(uint32_t *) ((((uint32_t)stack+stack_size)/8)*8);
  
  *(--sp)= (1U<<24);                      //this is the PSR Register (determines the thumb state)
  *(--sp)= (uint32_t)threadHandler;              //The PC of the main1, use function pointer
  *(--sp)= 0x0000000EU;                   //LR (this never returns so no need to worry
  *(--sp)= 0x0000000CU;                   //r 12
  *(--sp)= 0x00000003U;                   //r 3
  *(--sp)= 0x00000002U;                   //r 2
  *(--sp)= 0x00000001U;                   //r 1
  *(--sp)= 0x00000000U;                   //r 0
  //for other registers 4-11
  *(--sp)= 0x0000000BU;                   //r 11
  *(--sp)= 0x0000000AU;                   //r 10
  *(--sp)= 0x00000009U;                   //r 9
  *(--sp)= 0x00000008U;                   //r 8
  *(--sp)= 0x00000007U;                   //r 7
  *(--sp)= 0x00000006U;                   //r 6
  *(--sp)= 0x00000005U;                   //r 5
  *(--sp)= 0x00000004U;                   //r 4
  
  me->sp=sp;
}

void SysTick_Handler(void){
  __disable_irq();
  OS_Sched();
  __enable_irq();
}


void PendSV_Handler(void){
  __disable_irq();
  if(OS_Current!=(OSthread*)0){
    //OS_Current->sp=sp;
    __asm("PUSH       {r4-r11}");
    __asm ("LDR       R0, =OS_Current\n\tSTR       R1, [R0]");
    __asm("STR       sp, [R1]");
  }
  //sp=OS_Next->sp;
   __asm ("LDR.N     R1, =OS_Next");
   __asm ("LDR       R0, [R1]");
   __asm("LDR       sp, [R0]");
  
  //OS_Current=OS_Next;
   __asm ("LDR       R1, =OS_Next");
   __asm ("LDR       R1, [R1]");
   __asm ("LDR       R2, =OS_Current");
   __asm ("STR       R1, [R2]");
   
   __asm("POP        {r4-r11}");

   __enable_irq();
}

