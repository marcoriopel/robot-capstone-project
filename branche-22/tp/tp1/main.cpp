/*
 * Nom: main.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 9 janvier 2019
 * Version: 1.1
 */

 #define F_CPU 8000000UL
 #include <avr/io.h> 
 #include "controlerDEL.h" 
 #include "activerInterrupteur.h" 

const uint8_t sortie = 0b11111111;

int main()
{
  //DDRA = sortie; 
  //controlerDEL();

  DDRB = sortie;
  PORTB = 0b00000000;
  activierInterrupteur();

  return 0;
}