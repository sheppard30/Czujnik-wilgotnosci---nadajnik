#ifndef MS_RF_H
#define MS_RF_H

#include <avr/io.h>
#include <MsUart.h>
#include "MsTimer.h"

#define TICK_FOR_MANCHESTER_BIT_1 1
#define TICK_FOR_MANCHESTER_BIT_2 2
#define DATA_PORT PORTB
#define DATA_PIN PB3
#define DATA_DDR DDRB
#define PREAMBLE 0b10101010

class MsRf : public MsTimer
{
private:
    enum BitState
    {
        HIGH,
        LOW,
        NODATA
    };

    uint16_t data;
    uint8_t bitIndex;
    BitState bitToTransmit;
    bool transmittingFirstHalf;

    void setBitToSend();
    void transmitFirstHalf();
    void transmitSecondHalf();

public:
    MsRf();
    void init();
    void send(uint16_t data);
    void onTimerInterrupt();
};

#endif
