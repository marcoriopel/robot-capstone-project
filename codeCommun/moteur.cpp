/*
 * Nom: bouton.h
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */



void ajustementPWM ( uint8_t pourcentageOCR1A, pourcentageOCR1B ) 
{

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

    // page 177 de la description technique du ATmega324PA)

    OCR1A = (255 * pourcentageOCR1A) / 100 ;

    OCR1B = (255 * pourcentageOCR1B) / 100 ;


    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A |= (1 << COM1A1) | (0 << COM1A0) | (1 << COM1B1) | (0 << COM1B0) | (1 << WGM10) ;

    TCCR1B |=  (1 << CS11) ;

    TCCR1C |= 0;

}