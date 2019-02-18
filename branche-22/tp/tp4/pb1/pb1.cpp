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
    S4,
    S5
};

const uint8_t SORTIE = 0b11111111;
const uint8_t LUMIERE_ROUGE = 0b00000001;
const uint8_t LUMIERE_VERTE = 0b00000010;
const uint8_t LUMIERE_ETEINTE = 0b00000000;
volatile uint8_t etat = S0;
volatile bool estAppuye = false;


void changerEtat()
{
    if (++etat == 6)
    {
        etat = S0;
    }
}

void initialisation ( void ) 
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...

    cli ();


    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables

    DDRD = 0b11111011; // On formate le port D pour que la pin 2 soit en lecture (bouton-poussoir)
    DDRA = SORTIE;     // On formate le port A pour que toutes les pin soient en sortie



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

// placer le bon type de signal d'interruption

// à prendre en charge en argument

ISR (INT0_vect) 
{

    // laisser un delai avant de confirmer la réponse du

    // bouton-poussoir: environ 30 ms (anti-rebond)

    _delay_ms ( 30 );

    // se souvenir ici si le bouton est pressé ou relâché

    if (estAppuye && !(PIND & 0x04))
    {
        estAppuye = false;
        changerEtat();
    }
    else if (!estAppuye && (PIND & 0x04))
    {
        estAppuye = true;
        changerEtat();
    }
    else 

    // changements d'états tels que ceux de la

    // semaine précédente

    // Voir la note plus bas pour comprendre cette instruction et son rôle

    EIFR |= (1 << INTF0) ;

}

void allumerLumiere()
{
        switch (etat)
    {

        case S0:
            PORTA = LUMIERE_ROUGE;
            break;

        case S1:
            while (PIND & 0x04)
                {
                    PORTA = ~PORTA; // On inverse la polarite des pin 0 et 1 du port A pour creer la couleur ambre
                }
            break;
        
        case S2:
            PORTA = LUMIERE_VERTE;
            break;
        
        case S3:
            PORTA = LUMIERE_ROUGE;
            break;

        case S4:
            PORTA = LUMIERE_ETEINTE;
            break;

        case S5:
            PORTA = LUMIERE_VERTE;
            break;
        
    }  
}

int main()
{
    initialisation();

    while(true)
    {
        allumerLumiere();
    }

    return 0;    
}