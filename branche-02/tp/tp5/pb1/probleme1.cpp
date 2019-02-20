#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <memoire_24.h>

const uint8_t SORTIE = 0b11111111;
const uint8_t ENTREE = 0b00000000;
const uint8_t LUMIERE_ROUGE = 0b10101010;
const uint8_t LUMIERE_VERTE = 0b01010101;
const uint8_t LUMIERE_FERMEE = 0;
uint8_t tableau[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*\x00";
const uint8_t TAILLETABLEAU = sizeof(tableau) / sizeof(uint8_t);
bool isSame = true;


int main()
{

    DDRA = SORTIE;

    Memoire24CXXX memoire;

    memoire.ecriture(0x00, tableau,TAILLETABLEAU);

    uint8_t valeur[TAILLETABLEAU];

    _delay_ms(10);

    memoire.lecture(0x00, valeur, TAILLETABLEAU);

    for(int i = 0; i < TAILLETABLEAU; i++)
    {
        if(tableau[i] != valeur[i])
            isSame = false;
    }

    if (isSame)
        PORTA = LUMIERE_VERTE;
    else
        PORTA = LUMIERE_ROUGE;

    return 0;
}