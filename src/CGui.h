/*
 */

#ifndef CGUI_H
#define CGUI_H

#include "BiblioStd.h"
#include "CArmada.h"
#include "CCoups.h"

class CGui : public CBaseJeu
{
  private:
    char m_grilleJou[TAILLE_GRILLE - 1][TAILLE_GRILLE - 1]; // Grille du joueur
    char m_grilleAdv[TAILLE_GRILLE - 1][TAILLE_GRILLE - 1]; // Grille de l'adversaire
    CArmada* m_pArmada; // Pointeur vers l'unique armada du joueur
    CCoups* m_pCoups; // Pointeur vers l'unique structure d'enregistrement des tirs

    virtual void remplirDeuxGrilles(ostream &os) = 0;                // méthode abstraite
    virtual void afficherLaGrille(ostream &os, string jouOuAdv) = 0; // méthode abstraite

  public:
    CGui(); // Constructeur par défaut initialisant m_pArmada et m_pCoups à NULL
    CGui(CArmada* pArmada, CCoups* pCoups); // Constructeur avec les pointeurs vers m_pArmada et m_pCoups

    // Règle des 3 (Car possède des donnée membre pointeur)
    CGui(const CGui &b);                  // constructeur de copie
    CGui &operator=(const CGui &b);       // opérateur d'affectation
    virtual ~CGui();                              // destructeur

    void setArmadaCoups(CArmada *pArmada, CCoups *pCoups); // Modificateur : mise à jour des attributs
    void remplirDeuxGrilles(ostream &os); // Génère et affiche les grilles des 2 joueurs, du point de vue du joueur
    void afficherLaGrille(ostream &os, string jouOuAdv); // affiche la grille du "joueur" ou "adversaire" avec les légendes

    virtual bool positionnerBateaux() = 0;       // Méthode appelée au début du jeu pour placer tous les bateaux sur la grille
    virtual pair<int, int> choisirAttaque() = 0; // Demande à l'utilisateur des coordonnées de tir
    virtual void afficheGagne() = 0;             // Affiche un message de victoire
    virtual void affichePerdu() = 0;             // Affiche un message d'échec

    friend ostream &operator<<(ostream &os, CGui &theG); // Surcharge de l'opérateur << pour afficher le plateau de jeu
};

#endif // CGUI_H
