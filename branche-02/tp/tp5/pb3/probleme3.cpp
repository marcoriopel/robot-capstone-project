#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"


void initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premier registres pour vous éviter des complications

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la reception et la transmission par le UART0

    UCSR0A = 0;

    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);

    // Format des trames: 8 bits, 1 stop bits, none parity

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0C &= ~((1 << UPM00) | (1 << UPM01) | (1 << USBS0));
}



void transmissionUART(uint8_t donnee)
{
    while (!(UCSR0A & (1 << UDRE0))); 

    UDR0 = donnee;
}

int main()
{

    initialisationUART();

    Memoire24CXXX memoire;
    uint8_t adresse = 0x00;
    uint8_t tableau[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*\x00";
    uint8_t* tampon;


    while(*tampon != 0xFF)
    {
        memoire.lecture(adresse++, tampon);
         transmissionUART(*tampon);
    }

    return 0;
}