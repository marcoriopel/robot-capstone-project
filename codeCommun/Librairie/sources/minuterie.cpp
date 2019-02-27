/*
 * Nom: minuterie.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

#pragma once

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "minuterie.h"

const double NB_OVERFLOWS_SECONDE = 30.64;
volatile double overflowsCompare1 = 0;
volatile bool minuterie1EstExpiree = false;
volatile double overflowsCompare2 = 0;
volatile bool minuterie2EstExpiree = false;

void partirMinuterie_1 ( uint8_t secondes )
{
    overflowsCompare1 = NB_OVERFLOWS_SECONDE * secondes


    // normal mode du timer 0 avec horloge divisée par 1024
    // interruption a chaque fois que le TCNT0 atteint la valeur MAX (255) avec le 

    TCNT0 = 0;

    OCR0A = 0;

    TCCR0A = 0 ;

    TCCR0B = (1 << CS02) | (1 << CS00) ;

    TCCR0C = 0;

    TIMSK0 = 1 << TOIE0 ;
}

void partirMinuterie_2 ( uint8_t secondes ) 
{
    overflowsCompare2 = NB_OVERFLOWS_SECONDE * secondes;

    // normal mode du timer 2 avec horloge divisée par 1024
    // interruption a chaque fois que le TCNT2 atteint la valeur MAX (255) avec le 

    TCNT2 = 0;

    OCR2A = 0;

    TCCR2A = 0 ;

    TCCR2B = (1 << CS22) | (1 << CS20) ;

    TCCR2C = 0;

    TIMSK2 = 1 << TOIE0 ;
}


