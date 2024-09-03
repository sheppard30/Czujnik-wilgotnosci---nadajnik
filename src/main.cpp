#include <avr/io.h>
#include <util/delay.h>
#include <MsUart.h>
#include "MsRf.h"

#define TX_PIN PB4
#define ADC_PIN PB4
#define RF_TX_PIN PB3

MsRf rf;
// MsUart uart(&DDRB, &PORTB, TX_PIN);

ISR(TIM0_COMPA_vect)
{
    rf.onTimerInterrupt();
}

int main()
{
    DDRB |= (1 << RF_TX_PIN);

    // sensor_init();

    while (1)
    {
        // uint8_t huminity = adc_read();
        // uart_print("Test");
    }

    return 0;
}