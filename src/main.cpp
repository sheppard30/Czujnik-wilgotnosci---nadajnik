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

    while (1)
    {
        rf.send(0b01110000);
        _delay_ms(500);
    }

    return 0;
}
