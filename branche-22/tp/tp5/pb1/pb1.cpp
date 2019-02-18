/*
 * Nom: pb1.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 30 janvier 2019
 * Version: 1.1
 * 
 */

#include <util/delay.h>
#include "memoire_24.h"

const uint8_t SORTIE = 0xFF;
const uint8_t LUMIERE_ROUGE = 0b00000001;
const uint8_t LUMIERE_VERTE = 0b00000010;
const uint8_t LUMIERE_ETEINTE = 0b00000000; 
const uint16_t ADRESSE = 0x00;
const uint8_t LONGUEUR = 46; 


int main()
{
    uint8_t donneeEcriture[LONGUEUR] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    uint8_t donneeLecture[LONGUEUR];

    DDRA = SORTIE;
    PORTA = LUMIERE_ETEINTE;

    Memoire24CXXX memoire;
    memoire.ecriture(ADRESSE, donneeEcriture, LONGUEUR);

    _delay_ms(5);

    memoire.lecture(ADRESSE, donneeLecture, LONGUEUR);


    bool estdifferent = false;
    for(int i = 0; i < LONGUEUR; ++i)
    {
        if (donneeEcriture[i] != donneeLecture[i])
        {
            estdifferent = true;
        }
    }

    if (estdifferent)
    {
        PORTA = LUMIERE_ROUGE;
    }
    else
    {
        PORTA = LUMIERE_VERTE;
    }
    

    return 0;
}