#include "MsRf.h"

MsUart uart(&DDRB, &PORTB, 4);

MsRf::MsRf() : tick(0)
{
    MsTimer::init();
}

void MsRf::send(char *data)
{
    this->data = data;
}

void MsRf::onTimerInterrupt()
{
    if (tick++ >= 750)
    {
        uart.print("a");
        tick = 0;
    }
}
