/*
+---------------+-------+---------+---------------+
| Etat          | Input | Output  | Next State    |
+---------------+-------+---------+---------------+
| INIT          | 0     | Rouge   | INIT          |
+---------------+-------+---------+---------------+
| INIT          | 1     | Rouge   | FIRSTPRESS    |
+---------------+-------+---------+---------------+
| FIRSTPRESS    | 1     | Ambre   | FIRSTPRESS    |
+---------------+-------+---------+---------------+
| FIRSTPRESS    | 0     | Ambre   | FIRSTUNPRESS  |
+---------------+-------+---------+---------------+
| FIRSTUNPRESS  | 0     | Vert    | FIRSTUNPRESS  |
+---------------+-------+---------+---------------+
| FIRSTUNPRESS  | 1     | Vert    | SECONDPRESS   |
+---------------+-------+---------+---------------+
| SECONDPRESS   | 1     | Rouge   | SECONDPRESS   |
+---------------+-------+---------+---------------+
| SECONDPRESS   | 0     | Rouge   | SECONDUNPRESS |
+---------------+-------+---------+---------------+
| SECONDUNPRESS | 0     | Eteinte | SECONDUNPRESS |
+---------------+-------+---------+---------------+
| SECONDUNPRESS | 1     | Eteinte | THIRDPRESS    |
+---------------+-------+---------+---------------+
| THIRDPRESS    | 1     | Vert    | THIRDPRESS    |
+---------------+-------+---------+---------------+
| THIRDPRESS    | 0     | Vert    | INIT          |
+---------------+-------+---------+---------------+
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

const int DEBOUNCEDELAYMS = 10;
const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const uint8_t LUMIERE_ROUGE = 0b10101010;
const uint8_t LUMIERE_VERTE = 0b01010101;
const uint8_t LUMIERE_FERMEE = 0;
const int DELAY_ONE_MS = 1000;
enum States
{
    INIT,
    FIRSTPRESS,
    FIRSTUNPRESS,
    SECONDPRESS,
    SECONDUNPRESS,
    THIRDPRESS
};
States state = INIT;
bool etaitAppuye = false;

bool estAppuye()
{
    return PIND & 0x04;
}

bool debounce()
{
    if (estAppuye())
    {
        _delay_ms(DEBOUNCEDELAYMS);
        if (estAppuye())
        {
            return true;
        }
    }
    return false;
}

void doAction(States state)
{
    switch (state)
    {
    case INIT:
    {
        PORTA = LUMIERE_ROUGE;
        break;
    }
    case FIRSTPRESS:
    {
        PORTA = LUMIERE_VERTE;
        _delay_ms(2);
        PORTA = LUMIERE_ROUGE;
        _delay_ms(1);
        break;
    }
    case FIRSTUNPRESS:
    {
        PORTA = LUMIERE_VERTE;
        break;
    }
    case SECONDPRESS:
    {
        PORTA = LUMIERE_ROUGE;
        break;
    }
    case SECONDUNPRESS:
    {
        PORTA = LUMIERE_FERMEE;
        break;
    }
    case THIRDPRESS:
    {
        PORTA = LUMIERE_VERTE;
        break;
    }
    }
}

void stateSwitch(States &state)
{
    switch (state)
    {
    case INIT:
    {
        state = FIRSTPRESS;
        break;
    }
    case FIRSTPRESS:
    {
        state = FIRSTUNPRESS;
        break;
    }
    case FIRSTUNPRESS:
    {
        state = SECONDPRESS;
        break;
    }
    case SECONDPRESS:
    {
        state = SECONDUNPRESS;
        break;
    }
    case SECONDUNPRESS:
    {
        state = THIRDPRESS;
        break;
    }
    case THIRDPRESS:
    {
        state = INIT;
        break;
    }
    }
}


int main()
{
    DDRD = ENTREE;
    DDRA = SORTIE;
    while (true)
    {
        doAction(state);

        if ((estAppuye()) && !etaitAppuye)
        {
            _delay_ms(10);
            if (estAppuye())
            {
                etaitAppuye = true;
                stateSwitch(state);
            }
        }
        if (!(estAppuye()) && etaitAppuye)
        {
            _delay_ms(10);
            if (!(estAppuye()))
            {
                etaitAppuye = false;
                stateSwitch(state);
            }
        }
    }
    return 0;
}