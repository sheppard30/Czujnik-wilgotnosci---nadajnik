#include <avr/io.h>
#include <util/delay.h>
#include "Transmitter.h"
#include "HuminitySensor.h"

int main()
{
    _delay_ms(10); // z tym delayem wysyla dane

    HuminitySensor sensor;
    Transmitter rf('A'); // B dla drugiego

    rf.init();
    sensor.init();

    while (1)
    {
        uint16_t huminity = sensor.read();
        rf.send(huminity);
        _delay_ms(5000);
    }

    return 0;
}