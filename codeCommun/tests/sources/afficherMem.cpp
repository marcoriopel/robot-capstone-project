/*
 * Nom: afficherMem.cpp
 * auteur: Samuel Ouvrard
 * cree le 13 mars 2019
 * Version: 1.1
 * 
 */

#include "memoire.h"
#include "UART.h"

int main()
{
    initialisationUART();

    uint8_t nOctets0 = receptionUART();
    uint8_t nOctets1 = receptionUART();
    uint16_t nOctets = (nOctets0 << 8) | nOctets1;

    afficherMemoire(102);
    

    return 0;
}