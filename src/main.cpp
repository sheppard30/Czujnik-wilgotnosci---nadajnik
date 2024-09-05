#include <avr/io.h>
#include <util/delay.h>
#include <MsUart.h>
#include "MsRf.h"
#include "MsHuminitySensor.h"

#define TX_PIN PB4
#define ADC_PIN PB4

MsRf rf;

ISR(TIM0_COMPA_vect)
{
    rf.onTimerInterrupt();
}

int main()
{
    rf.init();
    rf.send(456);

    // _delay_ms(10); // z tym delayem wysyla dane
    while (1)
    {
    }

    return 0;
}