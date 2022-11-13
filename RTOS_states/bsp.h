#ifndef __BSP_H__
#define __BSP_H__

#define LED_RED (1U<<1)
#define LED_Blue (1U<<2)
#define LED_Green (1U<<3)

void LED_GREEN_ON(void);

void LED_GREEN_OFF(void);

void LED_RED_ON(void);

void LED_BLUE_ON(void);

void LED_BLUE_OFF(void);

void delay(int);

void init(void);

#endif