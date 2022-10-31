#ifndef MIROS_H
#define MIROS_h


//making a TCB

typedef struct{
  void* sp;
  /*other attributes assocaited with a thread*/
} OSthread;

typedef void(*OSthreadHandler)(); //A function pointer returning void and take no arguments 

void OS_init(void);

void OS_Sched(void);

void OSthread_start(OSthread *me, OSthreadHandler threadHandler, void* stack, uint32_t stack_size);


#endif /*MIROS_H*/

