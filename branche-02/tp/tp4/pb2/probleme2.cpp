#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t minuterieExpiree = 0;
volatile uint8_t boutonPoussoir = 0;
const uint8_t LUMIERE_ROUGE = 0b10101010;
const uint8_t LUMIERE_VERTE = 0b01010101;
const uint8_t LUMIERE_FERMEE = 0;

void initialisation(void)
{
    cli();

    const uint8_t SORTIE = 0b11111111;
    const uint8_t ENTREE = 0b00000000;
    DDRD = ENTREE;
    DDRA = SORTIE;

    EIMSK = (1 << INT0);
    EICRA = 01;

    sei();

}

ISR(TIMER1_COMPA_vect)
{
    minuterieExpiree = 1;
}

ISR(INT0_vect)
{
    boutonPoussoir = 1;
    // anti-rebond

}

void partirMinuterie(uint16_t duree)
{

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0;

    OCR1A = duree;

    TCCR1A = 0;

    TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12); //Clock divided by 1024

    TCCR1C = 0;

    TIMSK1 = (1 << OCIE1A);
}

int main()
{
    initialisation();

    _delay_ms(10000); //10 sec. delay

    PORTA = LUMIERE_ROUGE;

    _delay_ms(100); // 1/10 sec. delay

    PORTA = LUMIERE_FERMEE;

    sei();

    partirMinuterie(7820); //7820 cpu cycles for 1 sec.

    do
    {

        // attendre qu'une des deux variables soit modifiée

        // par une ou l'autre des interruptions.

    } while (minuterieExpiree == 0 && boutonPoussoir == 0);

    // Une interruption s'est produite. Arrêter toute

    // forme d'interruption. Une seule réponse suffit.

    cli();

    // Verifier la réponse

    if(minuterieExpiree == 1)
    {
        PORTA = LUMIERE_ROUGE;
    }
    else if(boutonPoussoir == 1)
    {
        PORTA = LUMIERE_VERTE;
    }
}