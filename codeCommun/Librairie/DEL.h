/*
 * Nom: dell.h
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */


/* 
 * ####################################################
 * #####             Fonctions Dell               #####
 * #####                                          #####
 * #####  Le reste de cette section contient les  #####
 * #####   fonctions que nous jugeons utiles par  #####
 * #####        rapport a l'utilisation du        ##### 
 * #####           de la lumiere dell             #####
 * #####       (La DEL doit être branchée         #####
 * #####        à PIN0 et PIN1 du port B)         #####
 * ####################################################
 */

enum couleur
{
    ROUGE,
    VERT,
    AMBRE,
    ETEINT
};

/*
 *    Allumer la lumiere dell de la couleur voulue
 *    selon l'enum DEL {ROUGE, VERT, AMBRE, ETEINT}
 *    si on allume la DEL de couleur ambre il faut 
 *    que la fonction soit dans une boucle infinie
 */
void allumerDEL(couleur couleur);

/*
 *    Allume la lumiere dell de la couleur selon 
 *    l'intensite de lumiere percu par la cellule 
 *    photovoltaique
 *
 *    ROUGE  si faible intensite
 *    AMBREE si moyenne intensite
 *    VERTE  si forte intensite
 */
void detecterLum();
