#include "tm4c123gh6pm.h"
#include "bsp.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    UART_SETUP();
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF;
    GPIO_PORTF_LOCK_R=0x4C4F434B;
    GPIO_PORTF_CR_R|=0x01;
    GPIO_PORTF_LOCK_R=0;

    //PF0 and PF4 are input pins
    GPIO_PORTF_DIR_R &= ~(1<<4)|~(1<<0);
    GPIO_PORTF_DIR_R |=(1<<3);
    GPIO_PORTF_DEN_R |= (1<<4)|(1<<3)|(1<<0);
    GPIO_PORTF_PUR_R |= (1<<4)|(1<<0);

    GPIO_PORTF_IS_R &= ~(1<<4)|~(1<<0);
    __asm__ volatile (" .byte 0x9F,0xF8, 0xDF,0xF5\n"
            "   NOP\n"
            "   NOP\n");
    GPIO_PORTF_IBE_R &=~(1<<4)|~(1<<0);
    GPIO_PORTF_IEV_R &= ~(1<<4)|~(1<<0);
    GPIO_PORTF_ICR_R |= (1<<4)|(1<<0);
    GPIO_PORTF_IM_R  |= (1<<4)|(1<<0);


    NVIC_EN0_R|= (1<<30);

    while(1)
    {
    }
}
