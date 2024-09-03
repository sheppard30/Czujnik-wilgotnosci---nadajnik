#ifndef MS_TIMER_H
#define MS_TIMER_H

#ifndef F_CPU
#error "Undefined F_CPU"
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

class MsTimer
{
public:
    static void init();
};

#endif