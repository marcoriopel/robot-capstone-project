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
#include "son.h"

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

    uint8_t instruction; //Variable pour entreposer 
    uint8_t operande;

    uint8_t nIterations = 0;
    uint8_t tampon;
    uint16_t adresseBoucle;
    int iBoucle;

   for (int i = 0; i < (size - 2)/2; ++i)
   {  
       memoire.lecture(adresse++, &instruction);
       transmissionUART(instruction);
       memoire.lecture(adresse++, &operande);
       transmissionUART(operande);

       _delay_ms(2000);

       if (instruction == 0x01) //Debut
        {
            progEstCommence = true;
        }
        else if (progEstCommence)
        {
            switch (instruction)
            {
                
                case 0x02: for (int i = 0; i < operande; ++i)   //attendre (att)
                           {  
                                _delay_ms(25);
                           } 
                    break;

                case 0x44: allumerDEL(VERT); //allumer la DEL (dal)
                    break;

                case 0x45: allumerDEL(ETEINT); //eteindre la DEL (det)
                    break;

                case 0x48: allumerSon(operande); //jouer la sonorite (sgo)
                    break;

                case 0x09: arreterSon(); //arreter de jouer la sonorite (sar)
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

                case 0xC0: nIterations = operande; //debut de boucle (dbc)
                           adresseBoucle = adresse;
                           iBoucle = i;
                   break;

                case 0xC1: if (nIterations != 0) //fin de boucle (fbc)
                           {
                                --nIterations;
                                
                                adresse = adresseBoucle;
                                i = iBoucle;
                           }
                    break;

                case 0xFF: progEstCommence = false; //pour sortir du while si on se trouve a l'instruction de fin
                           allumerDEL(ROUGE);
                    break;

                default: allumerDEL(ROUGE);
                    break;
            }
        }
   }

   

    return 0;
}