#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void ajustementPWM(uint8_t pourcentagePWM)
{

    uint8_t timerCycles = (pourcentagePWM * 255) / 100;

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

    // page 177 de la description technique du ATmega324PA)

    OCR1A = timerCycles;

    OCR1B = timerCycles;

    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM10);

    TCCR1B |= (1 << CS11);

    TCCR1C = 0;
}

int main()
{
    const uint8_t SORTIE = 0b11111111;
    const uint8_t ENTREE = 0b00000000;
    DDRD = SORTIE;
    PORTD = 0x00;


    while (true)
    {
        ajustementPWM(100);
        _delay_ms(2000);

        ajustementPWM(75);
        _delay_ms(2000);

        ajustementPWM(50);
        _delay_ms(2000);

        _delay_ms(2000);

        ajustementPWM(25);
        _delay_ms(2000);
    }


    return 0;
}