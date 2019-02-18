/*
 * Nom: dell.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

#include "dell.h"

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
    while(true)
    {
        PORTB = ~PORTB;
    }
}

void fermerLumiere()
{
    PORTB = 0;
}