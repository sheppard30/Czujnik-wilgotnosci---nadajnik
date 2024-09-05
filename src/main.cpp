#include <avr/io.h>
#include <util/delay.h>
#include "MsRf.h"
#include "MsHuminitySensor.h"

int main()
{
    _delay_ms(10); // z tym delayem wysyla dane

    MsHuminitySensor sensor;
    MsRf rf;

    rf.init();
    sensor.init();

    while (1)
    {
        uint8_t huminity = sensor.read();
        rf.send(huminity);
        _delay_ms(5000);
    }

    return 0;
}