#include <avr/io.h>
#include <stdint.h>
#include "memoire_24.h"
#include "memoire.h"
#include "minuterie.h"
#include "moteur.h"
#include "DEL.h"
#include "can.h"
#include "UART.h"
#include <util/delay.h>


int main()
{
    initialisationUART();

    Memoire24CXXX memoire;
    uint16_t adresse = 0x00;

    uint8_t* size0;
    memoire.lecture(adresse++, size0);
    transmissionUART(*size0);
    uint8_t* size1;
    memoire.lecture(adresse++, size1);
    transmissionUART(*size1);
    uint16_t size = (*size0 << 8) | *size1;

    bool progEstCommence = false;

    uint8_t* instruction; //Variable pour entreposer 
    uint8_t* operande;

   for (int i = 0; i < (size - 2)/2; ++i)
   {
       memoire.lecture(adresse++, instruction);
       transmissionUART(*instruction);
       memoire.lecture(adresse++, operande);
       transmissionUART(*operande);

       if (*instruction == 0x01) //Debut
        {
            progEstCommence = true;
        }
        else if (progEstCommence)
        {
            switch (*instruction)
            {
                
                case 0x02: //attendre (att)
                    break;

                case 0x44: allumerDEL(VERT); //allumer la DEL (dal)
                    break;

                case 0x45: allumerDEL(ETEINT); //allumerDEL(ETEINT); //eteindre la DEL (det)
                    break;

                case '\x48': //jouer la sonorite (sgo)
                    break;

                case '\x09': //arreter de jouer la sonorite (sar)
                    break;

                case '\x60': //arreter les moteurs (mar)
                    break;

                case '\x61': //arreter les moteurs (mar)
                    break;

                case 0x62: //avancer (mav)
                    ajustementDirectionRoues(true, true); //Les roues avancent
                    ajustementPWM(*operande/255,*operande/255);
                    break;

                case '\x63': //reculer (mre)
                    ajustementDirectionRoues(false, false); //Les roues avancent
                    ajustementPWM(*operande/255,*operande/255);
                    break;

                case '\x64': //touner a droite (trd)
                    break;

                case '\x65': //tourner a gauche (trg)
                    break;

                case '\xC0': //debut de boucle (dbc)
                    break;

                case '\xC1': //fin de boucle (fbc)
                    break;

                case '\xFF': progEstCommence = false; //pour sortir du while si on se trouve a l'instruction de fin
                    break;

                default: //allumerDEL(ROUGE);
                    break;
            }
        }
   }

    return 0;
}