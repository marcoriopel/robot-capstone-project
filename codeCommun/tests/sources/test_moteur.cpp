#include <avr/io.h>
#include <moteur.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#define MON_PORT PORTB
#define MON_DDR DDRB
const uint8_t DDR_SORTIE = 0xff
int main()
{
    MON_DDR = DDR_SORTIE;
    // MON_PORT = 0b11000000;
    _delay_ms(1000);
    ajustementDirectionRoues(true, true);
    ajustementPWM(50,50);


    _delay_ms(1000);
    //ajustementDirectionRoues(false, false);
    return 0;

}