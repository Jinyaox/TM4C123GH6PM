#include <stdint.h>
#include <stdbool.h>
#include "bsp.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/watchdog.h"
#include "driverlib/interrupt.h"
#include "driverlib/hibernate.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"

void loop(){
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x04);
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateGPIORetentionEnable();
    SysCtlDelay(64000000);
    HibernateWakeSet(HIBERNATE_WAKE_PIN);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3, 0x00);
    WatchdogResetDisable(WATCHDOG0_BASE);
    HibernateRequest();
}

void watchdog_setup(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG0);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WDOG0)){}

    if(WatchdogLockState(WATCHDOG0_BASE)==true){
        WatchdogUnlock(WATCHDOG0_BASE);
    }

    WatchdogReloadSet(WATCHDOG0_BASE,0x00FFFFFF);

    WatchdogResetEnable(WATCHDOG0_BASE);

    IntEnable(INT_WATCHDOG);
    WatchdogIntEnable(WATCHDOG0_BASE);
    WatchdogEnable(WATCHDOG0_BASE);
}

int main()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    watchdog_setup();
    loop();

    while(1){}
}
