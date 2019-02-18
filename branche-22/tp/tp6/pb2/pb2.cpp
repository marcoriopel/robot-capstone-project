/*
 * Nom: pb1.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 13 février 2019
 * Version: 1.1
 * 
 * Il faut brancher le fil a la lumiere del et aux pins 0 et 1 
 * du port B pour que le programme fonctionne correctement
 * 
 * Il faut brancher le fil rouge et noir d'alimentation du 
 * breadboard a VCC et GND respectivement
 * 
 * Il faut brancher le fil de donnee a la pin 0 du port A
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const uint8_t LUMIERE_VERTE = 0b00000010;
const uint8_t LUMIERE_ROUGE = 0b00000001;
const uint8_t LUMIERE_ETEINTE = 0;



int main()
{
    DDRA = ENTREE;
    DDRB = SORTIE;

    can convertisseur;

    while (true)
    {
        uint8_t pos = 0;
        uint16_t quantiteLumiere = convertisseur.lecture(pos);

        

        if (quantiteLumiere >= 0x0000 && quantiteLumiere <= 0x0133) //faible intensite de lumiere recu
        {
            PORTB = LUMIERE_VERTE;
        }
        else if(quantiteLumiere > 0x0133 && quantiteLumiere <= 0x026D) //moyenne intensite de lumiere recu
        {
            PORTB = LUMIERE_VERTE;
            _delay_ms(2);
            PORTB = LUMIERE_ROUGE;
            _delay_ms(1);
        }
        else if(quantiteLumiere > 0x026D && quantiteLumiere <= 0x03FF) //grande intensite de lumiere recu
        {
            PORTB = LUMIERE_ROUGE;
        }
        else
            PORTB = LUMIERE_ETEINTE;
    }
    return 0;
}