/*
 * Nom: pb2.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 14 janvier 2019
 * Version: 1.1
 * 
 * 
 * Il faut brancher le fil a la lumiere del et aux pins 0 et 1 du port A pour que le programme fonctionne correctement
 * 
 * //A represente le bouton
 * //Z represente la couleur de la lumière
 * +--------------+---+--------------+----------+
 * |ETAT PRESENT  | A | Etat suivant | Sortie Z |
 * +--------------+---+--------------+----------+
 * |ROUGE         | 0 | ROUGE        | ROUGE    |
 * +--------------+---+--------------+----------+
 * |ROUGE         | 1 | VERT         | AMBRE    |
 * +--------------+---+--------------+----------+
 * |VERT          | 0 | VERT         | VERT     |
 * +--------------+---+--------------+----------+
 * |VERT          | 1 | ETEINT       | ROUGE    |
 * +--------------+---+--------------+----------+
 * |ETEINT        | 0 | ETEINT       | ETEINT   |
 * +--------------+---+--------------+----------+
 * |ETEINT        | 1 | ROUGE        | VERT     |
 * +--------------+---+--------------+----------+
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

enum etat
{
    VERT,
    ROUGE,
    ETEINT
};

const uint8_t SORTIE = 0b11111111;
const uint8_t LUMIERE_ROUGE = 0b00000001;
const uint8_t LUMIERE_VERTE = 0b00000010;
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
                return true;
            }
        }
    return false;
}

//Il faut brancher le fil a la lumiere del et aux pins 0 et 1 du port A pour que le programme fonctionne correctement
int main()
{
    DDRD = 0b11111011; // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)
    DDRA = SORTIE;     // On formate le port A pour que toutes les pin soient en sortie
    int etat = ROUGE;
    PORTA = LUMIERE_ROUGE;

    for (;;)
    {
        if (debounce())
        {

                switch (etat)
                {
                case ROUGE:
                    while (PIND & 0x04)
                    {
                        PORTA = ~PORTA; // On inverse la polarite des pin 0 et 1 du port A pour creer la couleur ambre
                    }
                    PORTA = LUMIERE_VERTE;
                    etat = VERT;
                    break;

                case VERT:
                    while (PIND & 0x04)
                    {
                        PORTA = LUMIERE_ROUGE;
                    }
                    PORTA = LUMIERE_ETEINTE;
                    etat = ETEINT;
                    break;

                case ETEINT:
                    while (PIND & 0x04)
                    {
                        PORTA = LUMIERE_VERTE;
                    }
                    PORTA = LUMIERE_ROUGE;
                    etat = ROUGE;
                    break;
                }
        }
    }

    return 0;
}