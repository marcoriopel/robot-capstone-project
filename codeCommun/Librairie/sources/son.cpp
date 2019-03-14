/*
 * Nom: son.cpp
 * auteur: Marc-Olivier Riopel
 * cree le 13 mars 2019
 * Version: 1.0
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "son.h"

void allumerSon(int position)
{
    uint8_t premierePosition = 45;
    
    static uint16_t frequences[] = {110,
                                    117,
                                    123,
                                    131,
                                    139,
                                    147,
                                    156,
                                    165,
                                    175,
                                    185,
                                    196,
                                    208,
                                    220,
                                    233,
                                    247,
                                    262,
                                    277,
                                    294,
                                    311,
                                    330,
                                    349,
                                    370,
                                    392,
                                    415,
                                    440,
                                    466,
                                    494,
                                    523,
                                    554,
                                    587,
                                    622,
                                    659,
                                    698,
                                    740,
                                    784,
                                    831,
                                    880};

    uint8_t positionDansTableau = position - premierePosition;

    TCNT0 = 0; //On reset le compteur si le OCR0A est plus petit que le TCNT0
    TCCR0A |= (1 << COM0A0) | (1 << WGM01); //Active 0C0A quand on a un compare match
    TCCR0B |= (1 << CS02);

    static uint16_t compteur = F_CPU / 256;

    OCR0A = compteur / (frequences[positionDansTableau] * 2) - 1;
}

void arreterSon()
{
    TCCR0A &= ~(1 << COM0A1) & ~(1 << COM0A0);
}