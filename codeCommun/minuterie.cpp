/*
 * Nom: minuterie.h
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

void partirMinuterie ( uint16_t duree ) 
{
    bool minuterieEstExpiree = false;

    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée

    TCNT1 = 0;

    OCR1A = duree;

    TCCR1A = 0 ;

    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10) ;

    TCCR1C = 0;

    TIMSK1 = 1 << OCIE1A ;
}

void initialisationInterruptionMinuterie ( void ) 
{
    // On utilise cli pour bloquer toutes les interruptions pendant l'initialisation.
    cli ();

    DDRD = 0b11011011; // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)

    // Cette procédure ajuste le registre EIMSK de l’ATmega324PA pour permettre les interruptions externes.
    EIMSK |= (1 << INT0) ;

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA

    EICRA |= 0 << ISC01 | 1 << ISC00;

    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}