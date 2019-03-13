/*
 * Nom: memoire.h
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */



/* 
 * ####################################################
 * #####             Fonctions Memoire            #####
 * #####                                          #####
 * #####  Le reste de cette section contient les  #####
 * #####   fonctions que nous jugeons utiles par  #####
 * #####        rapport a l'utilisation de        ##### 
 * #####                la memoire                #####
 * ####################################################
 */

#pragma once

#include "memoire_24.h"


/*
*    fonction qui efface le contenu de la memoire 
*    le premier charactere de la memoire est mis au caractere de
*    fin "0xFF"
*/
void effacerMemoire();

/*
*    fonction qui affiche les nOctets premiers octets de la memoire 
*/
void afficherMemoire(int nOctets);

