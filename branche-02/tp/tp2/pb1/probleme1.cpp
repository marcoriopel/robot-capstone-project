/*
+----------+-------+---------+------------+
| Etat     | Input | Output  | Next State |
+----------+-------+---------+------------+
| INIT     | 1     | Eteinte | PRESSED1   |
+----------+-------+---------+------------+
| INIT     | 0     | Eteinte | INIT       |
+----------+-------+---------+------------+
| PRESSED1 | 1     | Eteinte | PRESSED2   |
+----------+-------+---------+------------+
| PRESSED1 | 0     | Eteinte | PRESSED1   |
+----------+-------+---------+------------+
| PRESSED2 | 1     | Eteinte | PRESSED3   |
+----------+-------+---------+------------+
| PRESSED2 | 0     | Eteinte | PRESSED2   |
+----------+-------+---------+------------+
| PRESSED3 | 1     | Eteinte | REDLIGHT   |
+----------+-------+---------+------------+
| PRESSED3 | 0     | Eteinte | PRESSED3   |
+----------+-------+---------+------------+
| REDLIGHT | 1     | Allumee | INIT       |
+----------+-------+---------+------------+
| REDLIGHT | 0     | Eteinte | REDLIGHT   |
+----------+-------+---------+------------+
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

    

const int DEBOUNCEDELAYMS = 10;
const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const uint8_t LUMIERE_ROUGE = 0b10101010;
const uint8_t LUMIERE_FERMEE = 0;
const int DELAY_ONE_MS = 1000;


bool debounce()
{
    if (PIND & 0x04)
    {
        _delay_ms(DEBOUNCEDELAYMS);
        if (PIND & 0x04)
        {
            while(PIND & 0x04);
            return true;
        }
    }
    return false;
}

enum states
{
    INIT,
    PRESSED1,
    PRESSED2,
    PRESSED3,
    REDLIGHT
};


int main()
{
    
    int state = INIT;
    DDRD = ENTREE;
    DDRA = SORTIE;

    while (true)
    {
        if (debounce())
        {
            switch(state)
            {
                case INIT: {
                    state = PRESSED1;
                    break;
                }
                case PRESSED1: {
                    state = PRESSED2;
                    break;
                }
                case PRESSED2: {
                    state = PRESSED3;
                    break;
                }
                case PRESSED3: {
                    state = REDLIGHT;
                    break;
                }
                case REDLIGHT: {
                    PORTA = LUMIERE_ROUGE;
                    _delay_ms(DELAY_ONE_MS);
                    PORTA = LUMIERE_FERMEE;
                    state = INIT;
                    break;
                }
            }
            while(debounce()){};
        }
        
    }
    return 0;
}