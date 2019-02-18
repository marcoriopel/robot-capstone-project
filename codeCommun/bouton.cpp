/*
 * Nom: bouton.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

#include "bouton.h"



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



void initialisationInterruptionBouton_1 ( void ) 
{
    // cli est une routine qui bloque toutes les interruptions.
    cli ();


    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables

    DDRD = 0b11111011; // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)



    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0) ;


    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA

    EICRA |= 1 << ISC01 | 1 << ISC00;

    // sei permet de recevoir à nouveau des interruptions.
    
    sei ();

}



void initialisationInterruptionBouton_2 ( void ) 
{
    // cli est une routine qui bloque toutes les interruptions.
    cli ();


    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables

    DDRD = 0b11111011; // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)


    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0) ;


    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA

    EICRA |= 0 << ISC01 | 1 << ISC00;

    // sei permet de recevoir à nouveau des interruptions.

    sei ();

}
