/*
 * Nom: dell.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

#pragma once

#define F_CPU 8000000UL
#include "dell.h"
#include <util/delay.h>


enum DEL
{
    ROUGE,
    VERT,
    AMBRE,
    ETEINT
};

const uint8_t SORTIE = 0b11111111;
const uint8_t LUMIERE_ROUGE = 0b00000001;
const uint8_t LUMIERE_VERTE = 0b00000010;
const uint8_t LUMIERE_ETEINTE = 0b00000000;

void allumeDEL(DEL couleur)
{
    switch (couleur)
    {
        case ROUGE : PORTB = LUMIERE_ROUGE;
        break;

        case VERT : PORTB = LUMIERE_VERTE;
        break;

        case AMBRE : PORTB = LUMIERE_VERTE;
                    _delay_ms(2);
                    PORTB = LUMIERE_ROUGE;
                    _delay_ms(1);
        break;

        case ETEINT : PORTB = LUMIERE_ETEINTE;
        break;
    }  
}
