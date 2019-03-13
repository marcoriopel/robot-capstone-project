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

/*
*    fonctione pour effacer le contenu de la memoire 
*    chaque bit de la memoire est mis au caractere de
*    terminaison de chaine "\0"
*/
void effacerMemoire(Memoire24CXXX memoire);

void afficherMemoire(Memoire24CXXX memoire, int nOctets);