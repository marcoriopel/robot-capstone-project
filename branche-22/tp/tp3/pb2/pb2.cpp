/*
 * Nom: pb1.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 14 janvier 2019
 * Version: 1.1
 */

//max ampere .4-.5
//5 volt
//section 16 de la doc

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

const uint8_t SORTIE = 0b11111111;
const uint8_t MOTEUR_ALLUME = 0b00000011;
const uint8_t MOTEUR_ETEINT = 0b00000000;
int frequence60HZ = 60;
int frequence400HZ = 400;

enum etat
{
    S60HZ_0,
    S60HZ_25,
    S60HZ_50,
    S60HZ_75,
    S60HZ_100,
    S400HZ_0,
    S400HZ_25,
    S400HZ_50,
    S400HZ_75,
    S400HZ_100,
};

// allume le moteur pour 1 seconde selon le poucentage 
void allumerMoteur60Hz(int pourcentage)
{
    int allumer = pourcentage;
    int fermer = 100 - allumer;

    for (int i = 0; i < 60; ++i)
    {
        for (int i = 0; i <= allumer; ++i)
        {
            PORTB = MOTEUR_ALLUME;
            _delay_us(166);
        }
        for (int i = 0; i <= fermer; ++i)
        {
            PORTB = MOTEUR_ETEINT;
            _delay_us(166);
        }
    }
}

void allumerMoteur400Hz(int pourcentage)
{
    int allumer = pourcentage;
    int fermer = 100 - allumer;

    for (int i = 0; i < 400; ++i)
    {
        for (int i = 0; i <= allumer; ++i)
        {
            PORTB = MOTEUR_ALLUME;
            _delay_us(25);
        }
        for (int i = 0; i <= fermer; ++i)
        {
            PORTB = MOTEUR_ETEINT;
            _delay_us(25);
        }
    }
}

int main()
{
    
    PORTB = MOTEUR_ETEINT;
    DDRB = 0b11111111;

    int etat = S60HZ_0;

    for (;;)
    {
        switch (etat)
        {
        case S60HZ_0:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur60Hz(0);
                etat = S60HZ_25;
            }

        case S60HZ_25:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur60Hz(25);
                etat = S60HZ_50;
            }

        case S60HZ_50:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur60Hz(50);
                etat = S60HZ_75;
            }

        case S60HZ_75:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur60Hz(75);
                etat = S60HZ_100;
            }

        case S60HZ_100:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur60Hz(100);
                etat = S400HZ_0;
            }

        case S400HZ_0:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur400Hz(0);
                etat = S400HZ_25;
            }

        case S400HZ_25:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur400Hz(25);
                etat = S400HZ_50;
            }

        case S400HZ_50:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur400Hz(50);
                etat = S400HZ_75;
            }

        case S400HZ_75:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur400Hz(75);
                etat = S400HZ_100;
            }

        case S400HZ_100:
            for (int i = 0; i < 2; ++i)
            {
                allumerMoteur400Hz(100);
                etat = S60HZ_0;
            }
        }
    }
    
   return 0;
}