#include <avr/io.h>
#include <stdint.h>
#include "memoire.h"
#include "memoire_24.h"
#include <minuterie.h>
#include <moteur.h>
#include <DEL.h>
#include <can.h>




uint8_t* instruction; //Variable pour entreposer 
uint8_t* operande;
uint16_t adresse = 0x02;

int main()
{
    Memoire24CXXX memoire;
    bool progEstCommence = false;

    while(*instruction != '\xFF')
    {
        memoire.lecture(adresse++, instruction);
        memoire.lecture(adresse++, operande);

        if (*instruction == '\x01') //Debut
        {
            progEstCommence = true;
        }
        
        while (progEstCommence) //Fin
        {
            switch (*instruction)
            {
                case '\x02': //attendre (att)
                    break;

                case '\x84': allumerDEL(VERT); //allumer la DEL (dal)
                    break;

                case '\x85': allumerDEL(ETEINT); //eteindre la DEL (det)
                    break;

                case '\x88': //jouer la sonorite (sgo)
                    break;

                case '\x09': //arreter de jouer la sonorite (sar)
                    break;

                case '\x60': //arreter les moteurs (mar)
                    break;

                case '\x61': //arreter les moteurs (mar)
                    break;

                case '\x62': //avancer (mav)
                    break;

                case '\x63': //reculer (mre)
                    break;

                case '\x64': //touner a droite (trd)
                    break;

                case '\x65': //tourner a gauche (trg)
                    break;

                case '\xC0': //debut de boucle (dbc)
                    break;

                case '\xC1': //fin de boucle (fbc)
                    break;
                
            }
        }
    }
}