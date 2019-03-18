#include <avr/io.h>
#include <moteur.h>
#define F_CPU 8000000UL
#include <util/delay.h>
int main()
{
    DDRD = 0b11111111;
    ajustementDirectionRoues(true, true);
    ajustementPWM(50,50);
    _delay_ms(5000);
    return 0;

}