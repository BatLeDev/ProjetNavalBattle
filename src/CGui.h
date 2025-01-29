#ifndef CGUI_H
#define CGUI_H

#include "BiblioStd.h"
#include "CBaseJeu.h"
#include "CArmada.h"
#include "CCoups.h"

class CGui : public CBaseJeu
{
  private:
    char m_grilleJou[TAILLE_GRILLE - 1][TAILLE_GRILLE - 1]; // Grille du joueur
    char m_grilleAdv[TAILLE_GRILLE - 1][TAILLE_GRILLE - 1]; // Grille de l'adversaire
    CArmada *m_pArmada; // Pointeur vers l'unique armada du joueur
    CCoups *m_pCoups; // Pointeur vers l'unique structure d'enregistrement des tirs

    virtual void remplirDeuxGrilles(ostream &os);                // Génère et affiche les grilles des 2 joueurs, du point de vue du joueur
    virtual void afficherLaGrille(ostream &os, string jouOuAdv); // affiche la grille du "joueur" ou "adversaire" avec les légendes

  public:
    CGui(); // Constructeur par défaut initialisant m_pArmada et m_pCoups à NULL
    CGui(CArmada *pArmada, CCoups *pCoups); // Constructeur avec les pointeurs vers m_pArmada et m_pCoups

    // Règle des 3 (Car possède des donnée membre pointeur)
    CGui(const CGui &g);                  // constructeur de copie
    CGui &operator=(const CGui &g);       // opérateur d'affectation
    virtual ~CGui();                              // destructeur

    void setArmadaCoups(CArmada *pArmada, CCoups *pCoups); // Modificateur : mise à jour des attributs
    virtual bool positionnerBateaux();       // Méthode appelée au début du jeu pour placer tous les bateaux sur la grille
    virtual pair<int, int> choisirAttaque(); // Demande à l'utilisateur des coordonnées de tir
    virtual void afficheGagne();             // Affiche un message de victoire
    virtual void affichePerdu();             // Affiche un message d'échec

    friend ostream &operator<<(ostream &os, CGui &theG); // Surcharge de l'opérateur << pour afficher le plateau de jeu
};

// Couleurs pour l'affichage (Code fourni par Raphael, merci a lui :) )

#define STYLE_BOLD "1"

#define COLOR_RED "31"
#define COLOR_GREEN "32"
#define COLOR_YELLOW "33"
#define COLOR_BLUE "34"
#define COLOR_MAGENTA "35"
#define COLOR_CYAN "36"
#define COLOR_WHITE "37"
#define COLOR_GRAY "90"
#define BG_WHITE "47"

#define COLORED_TEXT(msg, color) "\033[" << color << "m" << msg << "\033[0m"
#define BG_TEXT(msg, bg) "\033[" << bg << "m" << msg << "\033[0m"
#define COLORED_BG_TEXT(msg, color, bg) "\033[" << color << ";" << bg << "m" << msg << "\033[0m"
#define STYLED_TEXT(msg, style, color) "\033[" << style << ";" << color << "m" << msg << "\033[0m"
#define STYLED_BG_TEXT(msg, style, color, bg) "\033[" << style << ";" << color << ";" << bg << "m" << msg << "\033[0m"

#endif // CGUI_H
