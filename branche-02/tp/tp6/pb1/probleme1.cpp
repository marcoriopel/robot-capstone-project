#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const uint8_t LUMIERE_ROUGE = 0b10101010;
const uint8_t LUMIERE_VERTE = 0b01010101;
const uint8_t LUMIERE_FERMEE = 0;
const int DEBOUNCEDELAYMS = 10;
uint16_t compteur;

enum States
{
    INIT,
    S1, //Bouton enfonce et compteur qui roule
    S2, //Bouton relache ou compteur a 120 atteint
    S3, //Carte mere ne fait rien pour 2 secondes
    S4, //Lumiere rouge s'allume
    S5, //Lumiere verte pour 1 seconde
};

States state = INIT;

bool estAppuye() //Fonction qui determine si le bouton-poussoir est bel et bien enfonce
{
    return !(PIND & 0x04);
}

void doAction(States state) //Machine a etats qui sert uniquement a effectuer les actions pour chaque state
{
    switch (state)
    {
    case INIT: //On reinitialise le compteur a 0

        PORTB = LUMIERE_FERMEE;
        compteur = 0;
        break;

    case S1: //Tant que le bouton est enfonce, on incremente le compteur jusqu'a temps qu'on atteigne 120 ou que le bouton soit relache

        compteur++;
        _delay_ms(100);
        break;

    case S2: //On allume la lumiere verte pour 1/2 seconde

        PORTB = LUMIERE_VERTE;
        _delay_ms(500);
        break;

    case S3: //Rien ne se passe pour 2 secondes

        PORTB = LUMIERE_FERMEE;
        _delay_ms(2000);
        break;

    case S4: //la lumiere rouge clignote compteur/2 fois 2 fois par seconde

        for (uint8_t i = 0; i < compteur / 2; i++)
        {
            PORTB = LUMIERE_ROUGE;
            _delay_ms(250);
            PORTB = LUMIERE_FERMEE;
            _delay_ms(250);
        }
        break;

    case S5: //On allume la lumiere verte pour 1 seconde

        PORTB = LUMIERE_VERTE;
        _delay_ms(1000);
        break;
    }
}

void stateSwitch(States &state) //Machine a etats dont le but est uniquement de changer d'un etat a un autre
{
    switch (state)
    {
    case INIT:
        if (estAppuye()) //Quand on appuie sur le bouton-poussoir, on change a S1
        {
            _delay_ms(10);
            if (estAppuye())
                state = S1;
        }
        break;

    case S1:
        if (!estAppuye() || compteur >= 120) //Quand on relache le bouton ou que le compteur atteint 120, on change a S2
        {
            _delay_ms(10);
            if (!estAppuye() || compteur >= 120)
                state = S2;
        }
        break;

    case S2:

        state = S3;
        break;

    case S3:

        state = S4;
        break;

    case S4:

        state = S5;
        break;

    case S5:

        state = INIT;
        break;
    }
}

int main()
{
    DDRD = ENTREE;
    DDRB = SORTIE;
    while (true) //Boucle infinie
    {
        doAction(state); //L'action du present etat est effectuee a chaque boucle
        stateSwitch(state); //On change d'etat a chaque boucle
    }
    return 0;
}