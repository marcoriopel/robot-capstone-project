/*
 * Nom: dell.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

#pragma once

#define F_CPU 8000000UL
#include "DEL.h"
#include <util/delay.h>
#include "can.h"


const uint8_t SORTIE = 0b11111111;
const uint8_t LUMIERE_ROUGE = 0b00000001;
const uint8_t LUMIERE_VERTE = 0b00000010;
const uint8_t LUMIERE_ETEINTE = 0b00000000;

void allumeDEL(couleur couleur)
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




can convertisseur;

void detecterLum()
{
    uint8_t pos = 0;
    uint16_t quantiteLumiere = convertisseur.lecture(pos);

    quantiteLumiere = quantiteLumiere >> 2;

    if (quantiteLumiere >= 0x0000 && quantiteLumiere <= 0x0055) //faible intensite de lumiere recu
    {
        allumerDEL(ROUGE);
    }
    else if(quantiteLumiere > 0x0055 && quantiteLumiere <= 0x00AA) //moyenne intensite de lumiere recu
    {
        allumerDEL(VERT);
        _delay_ms(2);
        allumerDEL(ROUGE);
        _delay_ms(1);
    }
    else if(quantiteLumiere > 0x0055 && quantiteLumiere <= 0x00FF) //grande intensite de lumiere recu
    {
        allumerDEL(VERT);
    }
    else
        allumerDEL(ETEINT);
}
