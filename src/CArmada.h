/*
 *  Cette classe représente une armada de bateaux. Elle contiens donc une collection de bateaux m_listeBateaux
 *  Elle permet de lire la liste des bateaux disponible à partir d'un fichier texte et de les placer alléatoirement sur une grille carrée
 */

#ifndef CARMADA_H
#define CARMADA_H

#include "BiblioStd.h"
#include "CBateau.h"

class CArmada {

  private:
    vector<CBateau> m_listeBateaux; // Liste des bateaux de l'armada

  public:
    // Pas de constructeur => par défaut, le tableau m_listeBateaux est vide et sera automatiquement détruit (car construit automatiquement)

    void ajouterBateau(CBateau &unBat); // Ajoute un bateau à la liste des bateaux de l'armada avec la méthode push_back de la class vector
    void getArmadaFromFile();           // Lecture du fichier flotille.txt qui contient la liste complète de tous les bateaux et les place dans m_listeBateaux en 0,0
    bool placerAleatoirement();         // Place aléatoirement tous les bateau sur la grille, renvoie faux si le placement est impossible

    int getEffectif();          // Renvoie le nombre de bateau non coulé
    int getEffectifTotal();     // Renvoie le nombre total de bateaux
    int getNbreTotCases();      // Renvoie le nombre total de cases occupées par les bateaux de l'armada

    CBateau* getBateau(int i);  // Accesseur : renvoie l'adresse du ième bateau de la liste m_listeBateaux
};

#endif // CARMADA_H
