/*
 * Cette classe représente un bateau caractérisé par :
 *      	- le nombre de cases (m_taille) qu'il occupe sur la grille
 *        - un nom (porte-avion, croiseur, ...)
 *        - le point de départ de sa position HORIZONTALE sur la grille (appelé point d'ancrage du bateau sur la grille)
 *
 * Il mémorise également dans un tableau de booléens les dégâts occasionnés sur le bateau
 * (une case est à faux si elle n'est pas touchée par un tir adverse).
 */

#ifndef CBATEAU_H
#define CBATEAU_H

#include "BiblioStd.h"

class CBateau {

	private:
		int m_taille;             // nombre de cases occupées (horizontalement) sur la grille
		string m_nom;             // nom du bateau
		pair<int,int> m_position; // coordonnées du point d'ancrage (m_potision.first = ligne, m_position.second = colonne)
		bool *m_pDegats;          // tableau des dégâts de taille m_taille (case à faux si pas de dégât)

	public:
		CBateau();             // construction par défaut : "neant", (0,0), 0, NULL
    CBateau(string n, pair<int, int> p, int t); // constructeur, le bateau n'a encore aucune case touchée (m_pDegats de taille t à faux partout)
    
    // Règle des 3
    CBateau(const CBateau& b); // constructeur de copie
    CBateau& operator=(const CBateau& b); // opérateur d'affectation
    ~CBateau();            // destructeur

    bool estCoule();       // renvoie vrai si toutes les cases du bateau sont touchées (m_taille cases à vrai dans m_pDegats)
    bool getDegats(int i); // renvoie vrais si la case i est touchée (0 <= i < m_taille)
    bool tirAdverse(pair<int, int> p); // renvoie vrai si le tir touche une case du bateau (Si la case étais déjà touchée, renvoie faux) et met à jour m_pDegats

    string getNom();       // Accesseur : renvoie le nom du bateau
    int getTaille();       // Accesseur : renvoie le nombre de cases occupées par le bateau
    pair<int, int> getPosition();   // Accesseur : renvoie les coordonnées du point d'ancrage du bateau

    void setPosition(int i, int j); // Modificateur : nouveau point d'encrage en ième ligne et jème colonne

    friend ostream& operator<<(ostream& os, CBateau & theB); // Surcharge de l'opérateur << pour afficher à l'écran les caractéristiques du bateau
};

#endif // CBATEAU_H
