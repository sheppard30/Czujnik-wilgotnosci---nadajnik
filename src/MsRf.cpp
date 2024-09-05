#include "MsRf.h"

#define DEBUG_PIN PB4

#define High() (DATA_PORT |= (1 << DATA_PIN))
#define Low() (DATA_PORT &= ~(1 << DATA_PIN))
#define DebugHigh() (DATA_PORT |= (1 << DEBUG_PIN))
#define DebugLow() (DATA_PORT &= ~(1 << DEBUG_PIN))


//MsUart uart(&DDRB, &PORTB, 4);

#define PACKET_SIZE_BITS 8

MsRf::MsRf()
{
    bitToTransmit = BitState::NODATA;
    data = 0;
}

void MsRf::init()
{
    DATA_DDR |= (1 << DATA_PIN);
    DATA_DDR |= (1 << DEBUG_PIN); // debug
    High();

    MsTimer::init();
}

// Zmiana funkcji send, która teraz przyjmuje liczbę uint16_t zamiast stringa
void MsRf::send(uint16_t number)
{
    data = number; // Przechowuj liczbę w polu `data`
    bitIndex = 0;  // Resetuj indeks bitów
    transmittingFirstHalf = true;
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

    // Jeżeli wszystkie bity zostały przesłane, resetujemy bitIndex
    if (bitIndex > PACKET_SIZE_BITS)
    {
        bitIndex = 0; // Resetujemy indeks bitów
        data = 0;     // Koniec danych do transmisji
        bitToTransmit = BitState::NODATA;
    }
}

void MsRf::transmitFirstHalf()
{
    if (bitToTransmit == BitState::LOW)
    {
        High(); // Gdy bit jest 0 najpierw pierwszy bit do góry
    }
    else
    {
        Low(); // Gdy bit jest 1 najpierw pierwszy bit do dołu
    }
}

void MsRf::transmitSecondHalf()
{
    if (bitToTransmit == BitState::LOW)
    {
        Low(); // Gdy bit jest 0 drugi bit do dołu
    }
    else
    {
        High(); // Gdy bit jest 1 drugi bit do góry
    }
}

volatile bool state = false;

void MsRf::onTimerInterrupt()
{
    if (bitToTransmit == BitState::NODATA)
    {
        High();
        return;
    }

    if (transmittingFirstHalf) {
        DebugHigh();
        _delay_us(5);
        DebugLow();
        transmitFirstHalf();
    } else {
        transmitSecondHalf();
        setBitToSend(); // Pobierz kolejne bity Manchester
    }

    transmittingFirstHalf = !transmittingFirstHalf;
}
