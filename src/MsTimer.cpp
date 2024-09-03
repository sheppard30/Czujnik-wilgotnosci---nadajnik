#include "MsTimer.h"

void MsTimer::init()
{
    // Ustawienie trybu CTC (Clear Timer on Compare Match)
    TCCR0A |= (1 << WGM01);

    // Preskaler
    TCCR0B |= (1 << CS01) | (1 << CS00); // 150 000 Hz

    // Obliczenie wartości OCR0A dla docelowej częstotliwości
    OCR0A = 200; // 750 przerwań

    // Włączenie przerwań od porównania z OCR0A
    TIMSK0 |= (1 << OCIE0A);

    // Włączenie globalnych przerwań
    sei();
}
