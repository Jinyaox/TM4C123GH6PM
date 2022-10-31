/*start up code for TM4C*/
#include "tm4c123gh6pm.h"
#include "bsp.h"


extern int CSTACK$$Limit;
void __iar_program_start(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);

void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

const int __vector_table[] @ ".intvec"={
  (int)&CSTACK$$Limit,                   //should be initial value of SP or CSTACK$$LIMIT (NOT BASE!!!)
  (int)&__iar_program_start,              //Reset handler at 4
  
  //Below are Important Handlers that may be optional but recommended!!
  (int)&NMI_Handler,
  (int)&HardFault_Handler,
  (int)&MemManage_Handler,
  (int)&BusFault_Handler,
  (int)&UsageFault_Handler,
  0, /*Reserved*/
  0, /*Reserved*/
  0, /*Reserved*/
  0, /*Reserved*/
  (int)&SVC_Handler,
  (int)&DebugMon_Handler,
  0, /*Reserved*/
  (int)&PendSV_Handler,
  (int)&SysTick_Handler,
};

//now all handlers are being initialized, we just need to write these codes now for each handler