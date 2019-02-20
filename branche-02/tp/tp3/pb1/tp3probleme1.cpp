#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

const int DUREE = 1500;
const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const uint8_t LUMIERE_ROUGE = 0b10101010;
const uint8_t LUMIERE_VERTE = 0b01010101;
const uint8_t LUMIERE_FERMEE = 0;

void pwm(const int periodeB, const int a, const uint8_t couleur)
{
    PORTA = couleur;
    for (int i = 0; i < a; i++)
    {
        _delay_ms(1 / 1500);
    }
    PORTA = ENTREE;
    for (int i = 0; i < 1500 - a; i++)
    {
        _delay_ms(1 / 1500);
    }
}

int main()
{
    DDRD = ENTREE;
    DDRA = SORTIE;
    while (true)
    {
        int a = DUREE;
        for (int i = 0; i < DUREE; i++)
        {
            pwm(DUREE, a, LUMIERE_VERTE);
            a--;
        }
        a = DUREE;
        for (int i = 0; i < DUREE; i++)
        {
            pwm(DUREE, a, LUMIERE_ROUGE);
            a--;
        }
    }
}