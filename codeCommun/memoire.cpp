/*
 * Nom: dell.cpp
 * auteur: Marc-Alain Tetreault & Samuel Ouvrard
 * cree le 18 fevrier 2019
 * Version: 1.1
 */

#include "memoire_24.h"

void effacerMemoire()
{
    Memoire24CXXX memoire;

    const int TAILLE_MEMOIRE = 5242888; //taille de la memoire en bits
    for (int i = 0; i < TAILLE_MEMOIRE; i++)
    {
        memoire.ecriture(i, "\0")
    }
}