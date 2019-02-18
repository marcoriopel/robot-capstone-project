/*
 * Nom: pb1.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 28 janvier 2019
 * Version: 1.1
 * 
 * 
 * Il faut brancher le fil a la lumiere del et aux pins 0 et 1 du port A pour que le programme fonctionne correctement
 * 
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum etat
{
    S0,
    S1,
    S2,
    S3,
    S4
};

const uint8_t SORTIE = 0b11111111;
const uint8_t LUMIERE_ROUGE = 0b00000001;
const uint8_t LUMIERE_VERTE = 0b00000010;
const uint8_t LUMIERE_ETEINTE = 0b00000000;
const uint16_t UNE_SECONDE = 7812;

volatile uint8_t etat = S0;
volatile bool minuterieEstExpiree = false;
volatile bool boutonEstPousse = false; 


void changerEtat()
{
    if (etat == S2)
    {
        if (boutonEstPousse)
        {
            etat = S3;
        }
        else
        {
            etat = S4;
        }
    }
    else ++etat;
}

void initialisation ( void ) 
{
    // On utilise cli pour bloquer toutes les interruptions pendant l'initialisation.
    cli ();


    DDRD = 0b11011011; // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)
    DDRA = SORTIE;     // On formate le port A pour que toutes les pin soient en sortie



    // Cette procédure ajuste le registre EIMSK de l’ATmega324PA pour permettre les interruptions externes.
    EIMSK |= (1 << INT0) ;


    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA

    EICRA |= 0 << ISC01 | 1 << ISC00;

    // sei permet de recevoir à nouveau des interruptions.
    sei ();

}

void partirMinuterie ( uint16_t duree ) 
{

    minuterieEstExpiree = false;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0;

    OCR1A = duree;

    TCCR1A = 0 ;

    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10) ;

    TCCR1C = 0;

    TIMSK1 = 1 << OCIE1A ;

}

ISR ( TIMER1_COMPA_vect ) 
{

    minuterieEstExpiree = true;

}

// Interruption pour le bouton-poussoir
ISR (INT0_vect) 
{

    // laisser un delai avant de confirmer la réponse du bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms ( 30 );

    // se souvenir ici si le bouton est pressé ou relâché
    if (PIND & 0x04 && etat == S2)
    {
        boutonEstPousse = true;
    }

    // Signale l'interruption pour le bouton-poussoir
    EIFR |= (1 << INTF0) ;

}

void allumerLumiere()
{
        switch (etat)
    {

        case S0:
            PORTA = LUMIERE_ETEINTE;
            break;

        case S1:
            PORTA = LUMIERE_ROUGE;
            break;
        
        case S2:
            PORTA = LUMIERE_ETEINTE;
            break;
        
        case S3:
            PORTA = LUMIERE_VERTE;
            break;

        case S4:
            PORTA = LUMIERE_ROUGE;
            break;
        
    }  
}

int main()
{
    initialisation();

    _delay_ms(10000);
    changerEtat();

    PORTA = LUMIERE_ROUGE;
    _delay_ms(100);
    changerEtat();

    PORTA = LUMIERE_ETEINTE;
    partirMinuterie(UNE_SECONDE);

    do 
    {
        
    } while ( minuterieEstExpiree == false && boutonEstPousse == false );

    cli ();
    
    changerEtat();
    allumerLumiere ();

    

    return 0;    
}