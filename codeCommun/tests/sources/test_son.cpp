#include <son.h>
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
int main()
{
    
    DDRB = 0xFF;
    PORTB = (0b00000100);

    allumerSon(53);
    _delay_ms(1500);
    allumerSon(46);
    _delay_ms(1500);
    allumerSon(55);
    _delay_ms(1500);
    allumerSon(62);
    _delay_ms(1500);
    allumerSon(45);
    arreterSon();
    return 0;
}