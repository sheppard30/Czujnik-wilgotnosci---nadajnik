#ifndef MS_HUMINITYSENSOR_H
#define MS_HUMINITYSENSOR_H

#include <avr/io.h>

#define INTERVAL 10000

typedef void (*ReadCallback)(uint16_t huminity);

class MsHuminitySensor
{
private:
    uint16_t time;
    uint16_t huminity;

    void init();
    uint16_t read();
    ReadCallback onReadCallback;

public:
    MsHuminitySensor();
    void onTimerInterrupt();
    void onRead(ReadCallback callback);
};

#endif