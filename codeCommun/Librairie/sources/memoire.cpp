/*
 * Nom: dell.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

#pragma once

#include <util/delay.h>
#include "memoire_24.h"
#include "UART.h"

void effacerMemoire()
{
    Memoire24CXXX memoire;

    memoire.ecriture(0x00, 0xFF);
    _delay_ms(5);

}

void afficherMemoire(int nOctets)
{
    uint8_t* tamponLecture;
    Memoire24CXXX memoire;
    uint16_t adresse = 0x00;
    
    for (int i = 0; i < 102; ++i)
    {
        memoire.lecture(adresse++, tamponLecture);
        transmissionUART(*tamponLecture);
    }
}