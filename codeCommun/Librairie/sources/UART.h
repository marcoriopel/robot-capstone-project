#pragma once

#include <avr/io.h>

void initialisationUART(void);

// Du PC vers le USART
uint8_t receptionUART(void);

// De l'USART vers le PC
void transmissionUART(uint8_t donnee);