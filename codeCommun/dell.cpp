/*
 * Nom: dell.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

#define F_CPU 8000000UL
#include "dell.h"
#include <util/delay.h>


void allumerLumiereRouge()
{
    PORTB = 0b00000001;
}

void allumerLumiereVert()
{
    PORTB = 0b00000010;
}

void allumerLumiereAmbre()
{
    PORTB = allumerLumiereVert;
    _delay_ms(2);
    PORTB = allumerLumiereRouge;
    _delay_ms(1);
}

void fermerLumiere()
{
    PORTB = 0;
}