#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const int DEBOUNCEDELAYMS = 10;
const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const uint8_t LUMIERE_ROUGE = 0b10101010;
const uint8_t LUMIERE_VERTE = 0b01010101;
const uint8_t LUMIERE_FERMEE = 0;
const int DELAY_ONE_MS = 1000;

volatile bool etaitAppuye = false; // selon le nom de votre variable

enum States
{
    INIT,
    FIRSTPRESS,
    FIRSTUNPRESS,
    SECONDPRESS,
    SECONDUNPRESS,
    THIRDPRESS
};
volatile States state = INIT;

void initialisation(void)
{
    cli();

    const uint8_t SORTIE = 0b11111111;
    const uint8_t ENTREE = 0b00000000;
    DDRD = ENTREE;
    DDRA = SORTIE;

    EIMSK |= (1 << INT0);
    EICRA |= 01;

    sei();
}

bool estAppuye()
{
    return PIND & 0x04;
}

void stateSwitch()
{
    switch (state)
    {
        case INIT:
        {
            state = FIRSTPRESS;
            break;
        }
        case FIRSTPRESS:
        {
            state = FIRSTUNPRESS;
            break;
        }
        case FIRSTUNPRESS:
        {
            state = SECONDPRESS;
            break;
        }
        case SECONDPRESS:
        {
            state = SECONDUNPRESS;
            break;
        }
        case SECONDUNPRESS:
        {
            state = THIRDPRESS;
            break;
        }
        case THIRDPRESS:
        {
            state = INIT;
            break;
        }
    }
}
void doAction()
{
    switch (state)
    {
        case INIT:
        {
            PORTA = LUMIERE_ROUGE;
            break;
        }
        case FIRSTPRESS:
        {
            PORTA = LUMIERE_VERTE;
            _delay_ms(2);
            PORTA = LUMIERE_ROUGE;
            _delay_ms(1);
            break;
        }
        case FIRSTUNPRESS:
        {
            PORTA = LUMIERE_VERTE;
            break;
        }
        case SECONDPRESS:
        {
            PORTA = LUMIERE_ROUGE;
            break;
        }
        case SECONDUNPRESS:
        {
            PORTA = LUMIERE_FERMEE;
            break;
        }
        case THIRDPRESS:
        {
            PORTA = LUMIERE_VERTE;
            break;
        }
    }
}

ISR(INT0_vect)
{

    _delay_ms(30);

    // se souvenir ici si le bouton est pressé ou relâché

    if ((estAppuye()) && !etaitAppuye)
    {
        _delay_ms(10);
        if (estAppuye())
        {
            etaitAppuye = true;
            stateSwitch();
        }
    }
    if (!(estAppuye()) && etaitAppuye)
    {
        _delay_ms(10);
        if (!(estAppuye()))
        {
            etaitAppuye = false;
            stateSwitch();
        }
    }

    // Voir la note plus bas pour comprendre cette instruction et son rôle

    EIFR |= (1 << INTF0);
}

int main()
{
    initialisation();
    while (true)
    {
        doAction();
    }
    return 0;
}