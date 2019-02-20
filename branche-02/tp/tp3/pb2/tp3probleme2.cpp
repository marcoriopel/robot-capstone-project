#define F_CPU 8'000'000UL
#include <avr/io.h>
#include <util/delay.h>

const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const int SECONDESPARETAT = 2;

void pwm60(const int a) //17ms pcq 1/60
{
    const int nCycle = 133'333;
    PORTA = 0b10101010;
    _delay_loop_2(a*nCycle/4);
    PORTA = ENTREE;
    _delay_loop_2((1-a)*nCycle/4);
}

void pwm400(const int a) // 2.5ms pcq 1/400
{
     const int nCycle = 20'000;
    PORTA = 0b10101010;
    _delay_loop_2(a*nCycle/4);
    PORTA = ENTREE;
    _delay_loop_2((1-a)*nCycle/4);
}

int main()
{
    DDRA = SORTIE;
    while (true)
    {
      for(int i = 0; i < 60 * SECONDESPARETAT; i++)
      {
          pwm60(i);
      }
      for(int i = 0; i < 400 * SECONDESPARETAT; i++)
      {
          pwm400(i);
      }
    }
}