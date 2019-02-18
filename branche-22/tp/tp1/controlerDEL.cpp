/*
 * Nom: controlerDEL.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 9 janvier 2019
 * Version: 1.1
 */

 #include <avr/io.h> 
 #include "controlerDEL.h"

int controlerDEL()
{
  unsigned long compteur = 0; 
  uint8_t sortie = 0; 

  for(;;)  
  {
    compteur++;  
    int etat = compteur >> 17;
    
    switch (etat)
    {
        case VERT :  sortie = 1;
                     break;
        case ROUGE : sortie = 2;
                     break;
        case AMBRE : sortie = compteur;
                     break;
        case RESET : compteur = 0;
                     break;
    }

    PORTA = sortie;      
  }
  return 0;
}