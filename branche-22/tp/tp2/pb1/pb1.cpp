/*
 * Nom: pb1.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 14 janvier 2019
 * Version: 1.1
 * 
 * 
 * Il faut brancher le fil a la lumiere del et aux pins 0 et 1 du port A pour que le programme fonctionne correctement
 * 
 * //A represente le bouton
 * //Z represente la lumiere rouge (1 etant allume et 0 etant eteinte)
 * +--------------+---+--------------+----------+
 * | Etat present | A | Etat suivant | Sortie Z |
 * +--------------+---+--------------+----------+
 * | INIT         | 0 | INIT         | 0        |
 * +--------------+---+--------------+----------+
 * | INIT         | 1 | S0           | 0        |
 * +--------------+---+--------------+----------+
 * | S0           | 0 | S0           | 0        |
 * +--------------+---+--------------+----------+
 * | S0           | 1 | S1           | 0        |
 * +--------------+---+--------------+----------+
 * | S1           | 0 | S1           | 0        |
 * +--------------+---+--------------+----------+
 * | S1           | 1 | S2           | 0        |
 * +--------------+---+--------------+----------+
 * | S2           | 0 | S2           | 0        |
 * +--------------+---+--------------+----------+
 * | S2           | 1 | S3           | 0        |
 * +--------------+---+--------------+----------+
 * | S3           | 0 | S3           | 0        |
 * +--------------+---+--------------+----------+
 * | S3           | 1 | S4           | 0        |
 * +--------------+---+--------------+----------+
 * | S4           | 0 | S4           | 0        |
 * +--------------+---+--------------+----------+
 * | S4           | 1 | INIT         | 1        |
 * +--------------+---+--------------+----------+
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

enum etat
{
    INIT,
    S1,
    S2,
    S3,
    S4,
};

const uint8_t SORTIE = 0b11111111;
const uint8_t LUMIERE_ROUGE = 0b00000001; // On change la tension entre la pin 0 et 1 du port en question pour allumer la lumiere
const uint8_t LUMIERE_ETEINTE = 0b00000000;

/*
*    Debounce pour s'assurer de prendre une seule valeur lorsque le bouton est enfonce
*    \return          bool
*/
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
    DDRD = 0b11111011; // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)
    DDRA = SORTIE;     // On formate le port A pour que toutes les pin soient en sortie
    int etat = INIT;
    PORTA = LUMIERE_ETEINTE;

    for (;;)
    {
        if (debounce())
        {

            switch (etat)
            {
            case INIT:
                etat = S1;
                break;

            case S1:
                etat = S2;
                break;

            case S2:
                etat = S3;
                break;

            case S3:
                etat = S4;
                break;

            case S4:
                PORTA = LUMIERE_ROUGE;
                _delay_ms(1000);
                PORTA = LUMIERE_ETEINTE;
                etat = INIT;
                break;
            }
        }
    }

    return 0;
}