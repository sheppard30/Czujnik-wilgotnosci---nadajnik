#include "Transmitter.h"

Transmitter::Transmitter(char identifier)
{
    this->identifier = identifier;
}

void Transmitter::init()
{
    DATA_DDR |= (1 << DATA_PIN);
}

// Zmiana funkcji send, która teraz przyjmuje liczbę uint16_t zamiast stringa
void Transmitter::send(uint16_t data)
{
    transmit(data);
}

void Transmitter::transmit(uint16_t data)
{
    // Sprawdzanie bitu na pozycji `bitIndex`
    uint8_t bytesToTransmit = 16;

    // Wysylanie preambuly 8 bit (16 manchester). Musi byc int8_t
    for (int8_t index = 7; index >= 0; index--)
    {
        uint8_t bit = ((PREAMBLE >> index) & 1);

        transmitEncodedFirstBit(bit);
        transmitEncodedSecondBit(bit);
    }

    // Wysyłanie identyfikatora 8 bitów (16 bitów manchester)
    for (int8_t index = 7; index >= 0; index--)
    {
        uint8_t bit = ((identifier >> index) & 1);

        transmitEncodedFirstBit(bit);
        transmitEncodedSecondBit(bit);
    }

    // Wysyłanie danych 16 bitów (32 manchester)
    for (int8_t index = bytesToTransmit - 1; index >= 0; index--)
    {
        uint8_t bit = ((data >> index) & 1);

        transmitEncodedFirstBit(bit);
        transmitEncodedSecondBit(bit);
    }

    transmitBit(0);
}

void Transmitter::transmitBit(uint8_t bit)
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

void Transmitter::transmitEncodedFirstBit(uint8_t bit)
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

void Transmitter::transmitEncodedSecondBit(uint8_t bit)
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
