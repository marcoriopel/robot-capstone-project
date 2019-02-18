/*
 * Nom: pb1.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 28 janvier 2019
 * Version: 1.1
 * 
 * Il faut brancher le fil a la lumiere del et aux pins 0 et 1 
 * du port B pour que le programme fonctionne correctement
 * 
 * //A represente le bouton
 * //Z represente la couleur de la DEL
 * +--------------+---+--------------+----------------+
 * | Etat present | A | Etat suivant | Sortie Z       |
 * +--------------+---+--------------+----------------+
 * | S0           | 0 | S0           | ETEINTE        |
 * +--------------+---+--------------+----------------+
 * | S0           | 1 | S1           | ETEINTE        |
 * +--------------+---+--------------+----------------+
 * | S1           | - | S2           | ETEINTE        |
 * +--------------+---+--------------+----------------+
 * | S2           | - | S3           | Clignote VERT  |
 * +--------------+---+--------------+----------------+
 * | S3           | - | S4           | ETEINTE        |
 * +--------------+---+--------------+----------------+
 * | S4           | - | S5           | Clignote ROUGE |
 * +--------------+---+--------------+----------------+
 * | S5           | - | S0           | VERT           |
 * +--------------+---+--------------+----------------+
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t SORTIE = 0b11111111;
const uint8_t LUMIERE_ROUGE = 0b00000001;
const uint8_t LUMIERE_VERTE = 0b00000010;
const uint8_t LUMIERE_ETEINTE = 0b00000000;

enum etat
{
    S0,
    S1,
    S2,
    S3,
    S4,
    S5
};


bool debounce()
{
    if (PIND & 0x04)
    {
        _delay_ms(10); // On met un delay de 10ms pour assurer la fonction debounce
        if (PIND & 0x04)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    DDRD = 0b11111011; // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)
    DDRB = SORTIE;     // On formate le port B pour que toutes les pin soient en sortie
    int etat = S0;
    uint16_t compteur;
    for (;;)
    {
        switch (etat)
        {
            case S0:
                compteur = 0;
                PORTB = LUMIERE_ETEINTE;
                if (debounce())
                    ++etat;
                break;

            case S1:
                while (PIND & 0x04)
                {
                    _delay_ms(100);  // On veut que le compteur s'incremente 10 fois par secondes
                    ++compteur;
                    if (compteur == 120)
                    {
                        break;
                    }
                }
                ++etat;
                break;

            case S2:
                for (int i = 0; i < 10; ++i) // On veut que cet etat dure environ 1/2 seconde
                {
                    PORTB = LUMIERE_VERTE;
                    _delay_ms(25);
                    PORTB = LUMIERE_ETEINTE;
                    _delay_ms(25);

                }
                ++etat;
                break;
            
            case S3:
                _delay_ms(2000); // On veut que cet etat dure environ 2 secondes
                ++etat;
                break;
            
            case S4:
                for (unsigned int i = 0; i < (compteur/2); i++)
                {
                    PORTB = LUMIERE_ROUGE;
                    _delay_ms(250);
                    PORTB = LUMIERE_ETEINTE;
                    _delay_ms(250);
                }
                ++etat;
                break;

            case S5:
                PORTB = LUMIERE_VERTE;
                _delay_ms(1000); // On veut que cet etat dure environ 1 seconde
                etat = S0;
                break;
        }  
        
    }
    return 0;
}