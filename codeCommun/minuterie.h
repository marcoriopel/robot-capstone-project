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

void partirMinuterie ( uint16_t duree ) 


/*
 *    Le parametre a utilise dans ISR est: TIMER1_COMPA_vect
 *    et la fonction se code en une seule ligne:
 *    minuterieEstExpiree = true;
 */
void initialisationInterruptionMinuterie ( void ) 

