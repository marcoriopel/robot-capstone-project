/*
 * Nom: activerInterrupteur.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 9 janvier 2019
 * Version: 1.1
 */

 #define F_CPU 8000000UL
 #include <avr/io.h>
 #include <util/delay.h>
 #include "activerInterrupteur.h" 


int activierInterrupteur()
{
  DDRD = 0b11111011;

  for(;;)
  {
    if ( PIND & 0x04 )
    {
      _delay_ms(10);
      if ( PIND & 0x04 )
      {
        PORTB = 0b00000001;
        while ( PIND & 0x04 )
        {
          PORTB = ~PORTB;
        }
        PORTB = 0b00000000;
      }
    }
  }

  return 0;
}