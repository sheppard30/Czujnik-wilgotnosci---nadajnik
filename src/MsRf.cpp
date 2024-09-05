#include "MsRf.h"

MsUart uart(&DDRB, &PORTB, 4);

MsRf::MsRf()
{
    bitToTransmit = BitState::NODATA;
    bitIndex = 0;
    data = 0;
    transmitting = false;
}

void MsRf::init()
{
    DATA_DDR |= (1 << DATA_PIN);
    MsTimer::init();
}

// Zmiana funkcji send, która teraz przyjmuje liczbę uint16_t zamiast stringa
void MsRf::send(uint16_t number)
{
    this->data = number; // Przechowuj liczbę w polu `data`
    setBitToSend();      // Zainicjuj pierwszy zestaw bitów do transmisji
}

void MsRf::setBitToSend()
{
    // Sprawdzanie bitu na pozycji `bitIndex`
    uint8_t bit = ((data >> bitIndex) & 1);

    if (bit == 1)
    {
        bitToTransmit = BitState::HIGH;
    }
    else if (bit == 0)
    {
        bitToTransmit = BitState::LOW;
    }

    bitIndex++;

    // Jeżeli wszystkie 16 bitów zostały przesłane, resetujemy bitIndex
    if (bitIndex >= 16)
    {
        bitIndex = 0; // Resetujemy indeks bitów
        data = 0;     // Koniec danych do transmisji
        bitToTransmit = BitState::NODATA;
    }
}

void MsRf::transmitFirstBit()
{
    if (bitToTransmit == BitState::LOW)
    {
        // uart.print("1");

        DATA_PORT |= (1 << DATA_PIN); // Gdy bit jest 0 najpierw pierwszy bit do góry
    }
    else
    {
        // uart.print("0");

        DATA_PORT &= ~(1 << DATA_PIN); // Gdy bit jest 1 najpierw pierwszy bit do dołu
    }
}

void MsRf::transmitSecondBit()
{
    if (bitToTransmit == BitState::LOW)
    {
        // uart.print("0");

        DATA_PORT &= ~(1 << DATA_PIN); // Gdy bit jest 0 drugi bit na dół
    }
    else
    {
        // uart.print("1");

        DATA_PORT |= (1 << DATA_PIN); // Gdy bit jest 1 drugi bit do góry
    }
}

void MsRf::onTimerInterrupt()
{

    if (bitToTransmit != BitState::NODATA && !transmitting)
    {
        transmitFirstBit();
        transmitting = true;
        return;
    }

    if (bitToTransmit != BitState::NODATA && transmitting)
    {
        transmitSecondBit();
        setBitToSend(); // Pobierz kolejne bity Manchester

        transmitting = false;
    }
}
