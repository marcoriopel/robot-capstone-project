#include <avr/io.h>
#include <moteur.h>
#define F_CPU 8000000UL
#include <util/delay.h>
int main()
{
    DDRD = 0b11111111;
    ajustementDirectionRoues(true, true); //Les roues avancent
    ajustementPWM(50, 50);

    /*_delay_ms(4000);
    ajustementPWM(50, 0);
    _delay_ms(2400);
    ajustementPWM(0, 0);
    _delay_ms(1000);
    ajustementPWM(0, 50);
    _delay_ms(2400);
    ajustementPWM(0, 0);*/

    return 0;
}