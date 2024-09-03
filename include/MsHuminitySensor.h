#ifndef MS_HUMINITYSENSOR_H
#define MS_HUMINITYSENSOR_H

#include <avr/io.h>

class MsHuminitySensor
{
private:
    void init();

public:
    MsHuminitySensor();
    uint16_t read();
};

#endif