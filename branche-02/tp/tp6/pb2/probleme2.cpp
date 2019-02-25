#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const uint8_t LUMIERE_ROUGE = 0b10101010;
const uint8_t LUMIERE_VERTE = 0b01010101;
const uint8_t LUMIERE_FERMEE = 0;
const uint8_t NIVEAU_AMBRE = 120; //Les niveaux ont ete choisis en effectuant des tests de lumiere en laboratoire
const uint8_t NIVEAU_ROUGE = 205; 

int main()
{
    DDRA = ENTREE;
    DDRB = SORTIE;

    can can;

    while (true)
    {
        uint8_t pos = 0;
        uint16_t quantiteLumiere = (can.lecture(pos) >> 2); //On lit la quantite de lumiere a l'aide de la classe fournie

        if (quantiteLumiere > NIVEAU_ROUGE) //Lumiere est forte donc lumiere rouge
        {
            PORTB = LUMIERE_ROUGE;
        }
        else if (quantiteLumiere > NIVEAU_AMBRE) //Lumiere est a un bon niveau donc ambre
        {
            //On met un delai entre rouge et vert pour creer la couleur ambre
            PORTB = LUMIERE_VERTE;
            _delay_ms(2);
            PORTB = LUMIERE_ROUGE;
            _delay_ms(1);
        }
        else //Lumiere est basse donc verte
        {
            PORTB = LUMIERE_VERTE;
        }
    }
    return 0;
}