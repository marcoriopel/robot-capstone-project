/*
 * Nom: memoire.h
 * auteur: Samuel Ouvrard
 * cree le 13 mars 2019
 * Version: 1.1
 */



/* 
 * ####################################################
 * #####             Fonctions USART              #####
 * #####                                          #####
 * #####  Le reste de cette section contient les  #####
 * #####   fonctions que nous jugeons utiles par  #####
 * #####        rapport a l'utilisation du        ##### 
 * #####                 USART                    #####
 * ####################################################
 */


#pragma once

#include <avr/io.h>


/*
*    fonction qui initialise les registres du USART
*    pour permettre la reception et la transmission
*    avec serieViaUsb
*/
void initialisationUART(void);

/*
*    fonction qui retourne le caractere transmit par 
*    serieViaUsb vers le CPU du atmega324pa
*/
uint8_t receptionUART(void);

/*
*    fonction qui transmet le caractere recu par 
*    le CPU du atmega324pa vers le serieViaUsb
*/
void transmissionUART(uint8_t donnee);