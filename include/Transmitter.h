#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <avr/io.h>
#include <util/delay.h>

#define DATA_PORT PORTB
#define DATA_PIN PB3
#define DATA_DDR DDRB
#define PREAMBLE 0b10101010

class Transmitter
{
private:
    char identifier;

    void transmit(uint16_t data);
    void transmitBit(uint8_t bit);
    void transmitEncodedFirstBit(uint8_t bit);
    void transmitEncodedSecondBit(uint8_t bit);

public:
    Transmitter(char identifier);
    void init();
    void send(uint16_t data);
};

#endif