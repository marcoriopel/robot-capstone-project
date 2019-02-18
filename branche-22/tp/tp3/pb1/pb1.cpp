/*
 * Nom: pb1.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 14 janvier 2019
 * Version: 1.1
 */

//max ampere .4-.5
//5 volt
//section 16 de la doc

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

const uint8_t SORTIE = 0b11111111;
const uint8_t LUMIERE_ETEINTE = 0b00000000; // On change la tension entre la pin 0 et 1 du port en question pour eteindre la lumiere
const uint8_t LUMIERE_ROUGE = 0b00000001; // On change la tension entre la pin 0 et 1 du port en question pour allumer la lumiere
const uint8_t LUMIERE_VERTE = 0b00000010;


bool debounce()
{
    if (PIND & 0x04)
    {
        _delay_ms(10); // On met un delay de 10ms pour assurer la fonction debounce
        if (PIND & 0x04)
        {
            while (PIND & 0x04); // On place une boucle vide pour s'assurer que le bouton est relache
            return true;
        }
    }
    return false;
}

int main()
{
    DDRA = SORTIE;     // On formate le port A pour que toutes les pin soient en sortie
    DDRD = 0b00000000; // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)    
    PORTA = LUMIERE_ROUGE;
    uint8_t lumiereAllumee = LUMIERE_ROUGE;


    for (;;)
    {
        if (debounce())
        {
            int allumer = 100;
            int fermer = 100 - allumer;

            while(allumer != 0)
            {
                for(int i = 0; i <= allumer; ++i)
                {
                    PORTA = lumiereAllumee;
                    _delay_us(200);
                }
                for(int i = 0; i <= fermer; ++i)
                {
                    PORTA = LUMIERE_ETEINTE;
                    _delay_us(200);
                }
                allumer--;
                fermer ++;
            }

            if (lumiereAllumee == LUMIERE_ROUGE)
            {
                lumiereAllumee = LUMIERE_VERTE;
            }
            else
            {
                lumiereAllumee = LUMIERE_ROUGE;
            }

        }
    }
}