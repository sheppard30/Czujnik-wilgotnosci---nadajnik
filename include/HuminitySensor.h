#ifndef HUMINITYSENSOR_H
#define HUMINITYSENSOR_H

#include <avr/io.h>

#define INTERVAL 10000
#define ADC_PIN PB4

class HuminitySensor
{
public:
    HuminitySensor();
    void init();
    uint16_t read();
};

#endif