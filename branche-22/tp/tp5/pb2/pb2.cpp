/*
 * Nom: pb1.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 6 février 2019
 * Version: 1.1
 * 
 */

#include "memoire_24.h"

void initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premier registres pour vous éviter des complications

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la reception et la transmission par le UART0

    UCSR0A |= 0;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, none parity

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0C &= ~((1 << UPM01) | (1 << UPM00) | (1 << USBS0));
}

// De l'USART vers le PC

void transmissionUART(uint8_t donnee)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)));
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

int main()
{
    initialisationUART();

    char mots[21] = "Le robot en INF1900\n";

    uint8_t i, j;

    for (i = 0; i < 100; i++)
    {

        for (j = 0; j < 20; j++)
        {

            transmissionUART(mots[j]);
        }
    }

    return 0;
}