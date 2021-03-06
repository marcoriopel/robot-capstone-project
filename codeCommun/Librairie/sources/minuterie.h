/*
 * Nom: minuterie.h
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */


/* 
 * ####################################################
 * #####            Fonctions Minuterie           #####
 * #####                                          #####
 * #####  Le reste de cette section contient les  #####
 * #####   fonctions que nous jugeons utiles par  #####
 * #####       rapport a l'utilisation d'une      ##### 
 * #####                 minuterie                #####
 * ####################################################
 */



/*
 *    Le parametre a utilise dans ISR est: TIMER0_OVF0_vect
 *    et la fonction ISR se code ainsi:
 * 
 *    _______________________________________________
 *    |                                             |
 *    |  ++overflowsCounter;                        |
 *    |  if (overflowsCounter >= overflowsCompare)  |
 *    |  {                                          |
 *    |     minuterieEstExpiree = true;             |
 *    |  }                                          |
 *    |_____________________________________________|
 * 
 */

#pragma once


void partirMinuterie_1 ( uint8_t secondes ); 



/*
 *    Le parametre a utilise dans ISR est: TIMER1_COMPA_vect
 *    et la fonction se code en une seule ligne:
 *    minuterieEstExpiree = true;
 */
void partirMinuterie_2 ( uint8_t duree ); 

