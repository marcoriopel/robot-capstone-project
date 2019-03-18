/*
 * Nom: moteur.h
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */



/* 
 * ####################################################
 * #####             Fonctions Moteur             #####
 * #####                                          #####
 * #####  Le reste de cette section contient les  #####
 * #####   fonctions que nous jugeons utiles par  #####
 * #####        rapport a l'utilisation des       ##### 
 * #####            des moteurs du robot          #####
 * ####################################################
 */



/*
*    Ajustement du signal PWM pour chacune des roues 
*    du robot en fonction d'un pourcentage respectif
*/
#pragma once


void ajustementPWM (uint8_t pourcentageRoueA, uint8_t pourcentageRoueB); 



/*
*    Ajustement de la direction des roues du robot en fonction 
*/
void ajustementDirectionRoues ( bool roueAAvance, bool roueBAvance ); 



/*
*   allume le moteur selon le poucentage, la frequence et la duree delimite par l'usager
*/
void allumerMoteur(uint8_t pourcentage, int frequence, double duree);
