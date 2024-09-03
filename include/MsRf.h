#ifndef MS_RF_H
#define MS_RF_H

#define PREAMBLE 0b10101010

#include <avr/io.h>
#include <MsUart.h>
#include "MsTimer.h"

class MsRf : public MsTimer
{
private:
    char *data;
    uint16_t tick;

public:
    MsRf();
    void send(char *data);
    void onTimerInterrupt();
};

#endif