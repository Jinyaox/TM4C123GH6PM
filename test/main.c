#include "tm4c123gh6pm.h"
#include "bsp.h"
#include "random.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t seed;


int main(void)
{
    UART_SETUP();
    BUTTON_SETUP();
    RandomAddEntropy(14);RandomAddEntropy(23);
    seed=RandomSeed(); //seed need to be changed to randomize!!
    __asm volatile("    mov R12,#0x1\n"
                       "    adr R9, #0x09\n"
                       "    mul R12, R9, R12\n"
                       "    mov R12,LR\n"
                       "    bx LR\n"); //see if the R12 register has the correct addr
    while(1)
    {
    }
}
