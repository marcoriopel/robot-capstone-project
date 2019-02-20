#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const uint8_t LUMIERE_ROUGE = 0b10101010;
const uint8_t LUMIERE_VERTE = 0b01010101;
const uint8_t LUMIERE_FERMEE = 0;
const int DEBOUNCEDELAYMS = 10;

enum States
{
    INIT,
    S1, //Bouton enfonce et compteur qui roule
    S2, //Bouton relache ou compteur a 120 atteint
    S3, //Carte mere ne fait rien pour 2 secondes
    S4, //Lumiere rouge s'allume
    S5, //Lumiere verte pour 1 seconde
};

States state = INIT;
bool etaitAppuye = false;

bool estAppuye()
{
    return !(PIND & 0x02);
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
        break;
    }
    case PRESS:
    {
        PORTA = LUMIERE_VERTE;
        _delay_ms(2);
        PORTA = LUMIERE_ROUGE;
        _delay_ms(1);
        break;
    }
    case UNPRESS:
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

//Declaration d'un compteur
uint16_t compteur;


//Fonction pour savoir si le bouton-poussoir est appuye
bool estAppuye()
{
    return !(PIND & 0x04);
}


//Utilisation d'un debounce pour s'assurer que le bouton est bel et bien appuye
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

int main()
{
    while(true)
    {
        //On met le compteur a 0 a chaque debut de boucle
        compteur = 0;

        //Boucle jusqu'a ce que quelqu'un appuie sur le bouton-poussoir
        do{}while(!debounce());

        //Incrementation du compteur tant que le bouton est appuye ou jusqu'a ce que le compteur atteigne 120
        while(debounce() && compteur < 120)
        {
            compteur++;
            _delay_ms(100);
        }

        //Lumiere verte allumee pour 1/2 seconhttps://www.facebook.com/de puis deux secondes avec rien
        PORTB = LUMIERE_VERTE;
        _delay_ms(500);
        PORTB = LUMIERE_FERMEE;
        _delay_ms(2000);

        for(uint8_t i = 0; i <= compteur/2; i++)
        {
            PORTB = LUMIERE_ROUGE;
            _delay_ms(250)
            PORTB = LUMIERE_FERMEE;
            _delay_ms(250);
            PORTB = LUMIERE_ROUGE;
            _delay_ms(250);
            PORTB = LUMIERE_FERMEE;
            _delay_ms(250);
        }
        PORTB = LUMIERE_VERTE;
        _delay_ms(1000);
    }
}