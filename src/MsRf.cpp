#include "MsRf.h"

MsUart uart(&DDRB, &PORTB, 4);

MsRf::MsRf()
{
}

void MsRf::init()
{
    DATA_DDR |= (1 << DATA_PIN);
}

// Zmiana funkcji send, która teraz przyjmuje liczbę uint16_t zamiast stringa
void MsRf::send(uint16_t data)
{
    transmit(data);
}

void MsRf::transmit(uint16_t data)
{
    // Sprawdzanie bitu na pozycji `bitIndex`
    uint8_t bytesToTransmit = 16;

    // Wysylanie preambuly. Musi byc int8_t
    for (int8_t index = 7; index >= 0; index--)
    {
        uint8_t bit = ((PREAMBLE >> index) & 1);

        transmitEncodedFirstBit(bit);
        transmitEncodedSecondBit(bit);
    }

    for (int8_t index = bytesToTransmit - 1; index >= 0; index--)
    {
        uint8_t bit = ((data >> index) & 1);

        transmitEncodedFirstBit(bit);
        transmitEncodedSecondBit(bit);
    }

    transmitBit(0);
}

void MsRf::transmitBit(uint8_t bit)
{
    if (bit == 0)
    {
        DATA_PORT &= ~(1 << DATA_PIN);
    }
    else
    {
        DATA_PORT |= (1 << DATA_PIN);
    }

    _delay_ms(1);
}

void MsRf::transmitEncodedFirstBit(uint8_t bit)
{
    if (bit == 0)
    {
        transmitBit(1);
    }
    else
    {
        transmitBit(0);
    }
}

void MsRf::transmitEncodedSecondBit(uint8_t bit)
{
    if (bit == 0)
    {
        transmitBit(0);
    }
    else
    {
        transmitBit(1);
    }
}
