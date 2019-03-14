#include <son.h>
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
int main()
{
    
    DDRB = 0xFF;
    PORTB = (0b00000100);
    /*while(true)
    {
        PORTB ^= 0b1100;
        _delay_ms(5);
    }*/

    allumerSon(53);
    _delay_ms(1500);



    return 0;
}