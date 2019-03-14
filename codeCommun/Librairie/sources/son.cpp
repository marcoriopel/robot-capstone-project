/*
 * Nom: mson.cpp
 * auteur: Marc-Olivier Riopel
 * cree le 13 mars 2019
 * Version: 1.0
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "son.h"

const uint8_t SON_ALLUME = 0b00000001;
const uint8_t SON_ETEINT = 0;


void allumerSon(int intensitePourcentage, int frequence, double duree) //Duree en secondes
{
    DDRB = 0xFF;

    int allumer = intensitePourcentage;
    int fermer = 100 - allumer;

    uint16_t nDelayLoop2 = ((1 / frequence) / 100) / 0.0000005;

    for (int i = 0; i < (duree * frequence); ++i)
    {
        for (int i = 0; i <= allumer; ++i)
        {
            PORTB = SON_ALLUME;
            _delay_loop_2(nDelayLoop2);
        }
        for (int i = 0; i <= fermer; ++i)
        {
            PORTB = SON_ETEINT;
            _delay_loop_2(nDelayLoop2);
        }
    }
}