#ifndef MIROS_H
#define MIROS_H

#include <stdint.h>


//making a TCB

typedef struct{
  void* sp;
  uint32_t timeout;
  /*other attributes assocaited with a thread*/
} OSthread;

typedef void(*OSthreadHandler)(); //A function pointer returning void and take no arguments 

void OS_init (void*, uint32_t);

void OS_onIdle(void);

void OS_Sched(void);

void OS_run(void);

void OS_tick(void);

void OS_onStartup(void);

void OSthread_start(OSthread *me, OSthreadHandler threadHandler, void* stack, uint32_t stack_size);


#endif /*MIROS_H*/

