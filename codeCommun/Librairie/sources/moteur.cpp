/*
 * Nom: moteur.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

#pragma once

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "moteur.h"

const uint8_t MOTEUR_ALLUME = 0b00000011;
const uint8_t MOTEUR_ETEINT = 0;


void ajustementPWM ( uint8_t pourcentageRoueA, uint8_t pourcentageRoueB ) 
{

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

    // page 177 de la description technique du ATmega324PA)

    OCR1A = (255 * pourcentageRoueA) / 100 ;

    OCR1B = (255 * pourcentageRoueB) / 100 ;


    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A |= (1 << COM1A1) | (0 << COM1A0) | (1 << COM1B1) | (0 << COM1B0) | (1 << WGM10) ;

    TCCR1B |=  (1 << CS11) ;

    TCCR1C |= 0;

}



void ajustementDirectionRoues ( bool roueAAvance, bool roueBAvance ) 
{
    PORTD |=   roueAAvance << PIND7 | roueAAvance << PIND6;
    PORTD &= ~(roueAAvance << PIND7 | roueAAvance << PIND6);
}



void allumerMoteur(int pourcentage, int frequence, double duree) //Duree en secondes
{
    int allumer = pourcentage;
    int fermer = 100 - allumer;

    uint16_t nDelayLoop2 = ((1 / frequence) / 100) / 0.0000005;

    for (int i = 0; i < (duree * frequence); ++i)
    {
        for (int i = 0; i <= allumer; ++i)
        {
            PORTB = MOTEUR_ALLUME;
            _delay_loop_2(nDelayLoop2);
        }
        for (int i = 0; i <= fermer; ++i)
        {
            PORTB = MOTEUR_ETEINT;
            _delay_loop_2(nDelayLoop2);
        }
    }
}