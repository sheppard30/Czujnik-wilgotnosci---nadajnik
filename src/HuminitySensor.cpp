#include "HuminitySensor.h"

HuminitySensor::HuminitySensor()
{
}

void HuminitySensor::init()
{
    // Ustawienie napięcia referencyjnego na Vcc oraz wybór kanału ADC2 (PB4)
    ADMUX = (1 << MUX1); // ADMUX ustawiony na kanał ADC2 (PB4)

    // Włączenie ADC oraz ustawienie preskalera na 64 (dla 9.6 MHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
}

uint16_t HuminitySensor::read()
{
    // Rozpoczęcie konwersji ADC
    ADCSRA |= (1 << ADSC);

    // Czekanie na zakończenie konwersji (ADS bit ustawia się na 0 po zakończeniu)
    while (ADCSRA & (1 << ADSC))
        ;

    // Zwrócenie odczytanej wartości
    return ADC;
}