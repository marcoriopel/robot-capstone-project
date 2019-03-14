/*
 * Nom: ecrireMem.cpp
 * auteur: Samuel Ouvrard
 * cree le 12 mars 2019
 * Version: 1.1
 * 
 */

#include <util/delay.h>
#include <memoire_24.h>
#include <memoire.h>
#include <UART.h>


int main()
{
    initialisationUART();
    Memoire24CXXX memoire;

    uint16_t adresse = 0x00;

    uint8_t nOctets0 = receptionUART();
    uint8_t nOctets1 = receptionUART();
    uint16_t nOctets = (nOctets0 << 8) | nOctets1;

    memoire.ecriture(adresse++, nOctets0);
    _delay_ms(5);
    memoire.ecriture(adresse++, nOctets1);
    _delay_ms(5);

    uint8_t tamponEcriture;
    for (int i = 0; i < nOctets - 2; ++i)
    {
        tamponEcriture = receptionUART();   
        memoire.ecriture(adresse++, tamponEcriture);
        _delay_ms(5);
    }
    

    return 0;
}