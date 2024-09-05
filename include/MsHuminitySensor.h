#ifndef MS_HUMINITYSENSOR_H
#define MS_HUMINITYSENSOR_H

#include <avr/io.h>

#define INTERVAL 10000
#define ADC_PIN PB4

class MsHuminitySensor
{
public:
    MsHuminitySensor();
    void init();
    uint16_t read();
};

#endif