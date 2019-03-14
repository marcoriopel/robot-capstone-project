/*
 * Nom: son.h
 * auteur: Marc-Olivier Riopel
 * cree le 13 mars 2019
 * Version: 1.0
 */

#pragma once


/* 
 * ####################################################
 * #####             Fonctions Son                #####
 * #####                                          #####
 * #####  Le reste de cette section contient les  #####
 * #####   fonctions que nous jugeons utiles par  #####
 * #####        rapport a l'utilisation des       ##### 
 * #####            des moteurs du robot          #####
 * ####################################################
 */


/*
*   allume le moteur selon le poucentage, la frequence et la duree delimite par l'usager
*/
void allumerSon(int position);

void arreterSon();
