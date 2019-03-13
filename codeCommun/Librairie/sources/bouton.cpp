/*
 * Nom: bouton.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "bouton.h"
#include <avr/interrupt.h>


bool debounce()
{
    if (PIND & 0x04)
    {
        _delay_ms(10); // On met un delay de 10ms pour assurer la fonction debounce
        if (PIND & 0x04)
        {
            return true;
        }
    }
    return false;
}



void initInterruptionBouton (uint8_t type, uint8_t vector) 
{
    // bloque toutes les interruptions.
    cli ();

    // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)
    DDRD = 0b11111011; 


    // ajuste le registre EIMSK pour permettre les interruptions externes
    switch (vector)
    {
        case 0 : EIMSK |= (1 << INT0); break;  // vecteur INT0_vect
        case 1 : EIMSK |= (1 << INT1); break;  // vecteur INT1_vect
        case 2 : EIMSK |= (1 << INT2); break;  // vecteur INT2_vect

        default : EIMSK |= (1 << INT0); break; // vecteur INT0_vect
    }


    // ajuste le registre EICRA pour definir ce qui declenchera l'interruption
    switch (type)
    {   
        case 0 : EICRA |= 0 << (ISC01 + vector * 2) | 1 << (ISC00 + vector * 2); break;   // rising edge du bouton-poussoir
        case 1 : EICRA |= 0 << (ISC01 + vector * 2) | 1 << (ISC00 + vector * 2); break;   // any edge du bouton-poussoir
        case 2 : EICRA |= 1 << (ISC01 + vector * 2) | 0 << (ISC00 + vector * 2); break;   // falling edge du bouton-poussoir

        default : EICRA |= 1 << (ISC01 + vector * 2) | 1 << (ISC00 + vector * 2); break;  // rising edge du bouton-poussoir
    }


    // permet de recevoir à nouveau des interruptions.
    sei ();

}

