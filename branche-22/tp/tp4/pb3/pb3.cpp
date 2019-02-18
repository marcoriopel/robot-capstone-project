/*
 * Nom: pb1.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 30 janvier 2019
 * Version: 1.1
 * 
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t SORTIE = 0b11111111;

void ajustementPWM ( uint8_t pourcentage ) 
{

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6

    // page 177 de la description technique du ATmega324PA)

    OCR1A = (255 * pourcentage) / 100 ;

    OCR1B = (255 * pourcentage) / 100 ;


    // division d'horloge par 8 - implique une frequence de PWM fixe

    TCCR1A |= (1 << COM1A1) | (0 << COM1A0) | (1 << COM1B1) | (0 << COM1B0) | (1 << WGM10) ;

    TCCR1B |=  (1 << CS11) ;

    TCCR1C |= 0;

}


int main()
{
    DDRD = SORTIE;
    PORTD = 0x00;

    uint8_t pourcentageMoteur = 100;
    while(pourcentageMoteur >= 0)
    {
        ajustementPWM(pourcentageMoteur);
        _delay_ms(2000);
        if (pourcentageMoteur != 0)
        {
             pourcentageMoteur -= 25; 
        }
    }

    return 0;    
}