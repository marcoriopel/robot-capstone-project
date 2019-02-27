/*
 * Nom: bouton.h
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */



/* 
 * ####################################################
 * #####             Fonctions Bouton             #####
 * #####                                          #####
 * #####  Le reste de cette section contient les  #####
 * #####   fonctions que nous jugeons utiles par  #####
 * #####        rapport a l'utilisation du        #####
 * #####              bouton-poussoir             #####
 * ####################################################
 */

enum type
{
    RISING_EDGE;
    ANY_EDGE;
    FALLING_EDGE;
};

enum vecteur
{
    INT0_vect;
    INT1_vect;
    INT2_vect;
};


/*
*    Debounce pour s'assurer de prendre une seule valeur lorsque le bouton est enfonce
*/
bool debounce();



/*
*    Initialisation de la routine d'interruption 
*    
*    type
*    (rising edge - type = 0 / any edge - type = 1 / falling edge - type = 2)
*
*    vector
*    (INT0_vect - vector = 0 / INT1_vect - type = 1 / INT2_vect - type = 2)
*/
void initInterruptionBouton (type type = RISING_EDGE, vecteur vecteur = INT0_vect);  




