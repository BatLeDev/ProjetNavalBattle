#include "CBateau.h"

/*
 *  Constructeur par défaut
 */
CBateau::CBateau()
{
  m_taille = 0;
  m_nom = "neant";
  m_position = { 0, 0 };
  m_pDegats = NULL;
}

/*
 *  Constructeur avec paramètres
 */
CBateau::CBateau(string n, pair<int, int> p, int t)
{
  m_taille = t;
  m_nom = n;
  m_pDegats = new bool[t];
  for (int i = 0; i < t; i++) {
    m_pDegats[i] = false;
  }
  this->setPosition(p.first, p.second);
}

/**********************************************/

/*
 * Accesseur : renvoie le nom du bateau
 */
string CBateau::getNom()
{
  return m_nom;
}

/*
 * Accesseur : renvoie le nombre de cases occupées par le bateau
 */
int CBateau::getTaille()
{
  return m_taille;
}

/*
 * Accesseur : renvoie les coordonnées du point d'ancrage du bateau
 */
pair<int, int> CBateau::getPosition()
{
  return m_position;
}

/**********************************************/

/*
 * Modificateur : nouveau point d'encrage en ième ligne et jème colonne
 * Affihe une erreur si la position du bateau dépasse la grille ou est en dehors de la grille
 * @param i ligne
 * @param j colonne
 */
void CBateau::setPosition(int i, int j)
{
  if (i < 0 || i >= TAILLE_GRILLE || j < 0 || j+m_taille-1 >= TAILLE_GRILLE)
  {
    cout << "Erreur : position du bateau hors grille" << endl;
    return;
  }
  m_position = { i, j };
}

/**********************************************/

/*
 * @return true si toutes les cases du bateau sont touchées
 */
bool CBateau::estCoule()
{
  for (int i = 0; i < m_taille; i++)
  {
    if (!m_pDegats[i])
    {
      return false;
    }
  }
  return true;
}

/**********************************************/

/*
 * @param i indice de la case
 * @return true si la case i est touchée
 */
bool CBateau::getDegats(int i)
{
  if (i < 0 || i >= m_taille)
  {
    cout << "Erreur : indice de case invalide" << endl;
    return false;
  }
  return m_pDegats[i];
}

/**********************************************/

/*
 * @param p coordonnées du tir adverse
 * @return true si le tir touche une case du bateau (qui n'était pas déjà touchée) et met à jour m_pDegats
 */
bool CBateau::tirAdverse(pair<int, int> p)
{
  if (p.first < 0 || p.first >= TAILLE_GRILLE || p.second < 0 || p.second >= TAILLE_GRILLE)
  {
    cout << "Erreur : tir en dehors de la grille" << endl;
    return false;
  }

  if (p.first == m_position.first // Meme ligne
      && p.second >= m_position.second // Colonne >= au début du bateau
      && p.second < m_position.second + m_taille // Colonne < fin du bateau
      && !m_pDegats[p.second - m_position.second] // Case pas encore touchée
  ){
    m_pDegats[p.second - m_position.second] = true; // "Sauvegarde" les dégâts
    return true;
  }
  return false;
}

/**********************************************/

/*
 * Surcharge de l'opérateur << pour afficher à l'écran les caractéristiques du bateau
 */
ostream& operator<<(ostream& os, CBateau & theB)
{
  os << "Bateau " << theB.m_nom << " de taille " << theB.m_taille << " en position (" << theB.m_position.first << "," << theB.m_position.second << ") : ";
  for (int i = 0; i < theB.m_taille; i++)
  {
    os << theB.m_pDegats[i] << " ";
  }
  return os;
}

/**********************************************/

/*
 * Destructeur
 * Libère la mémoire allouée pour m_pDegats car c'est un tableau dynamique
 */
CBateau::~CBateau()
{
  cout << "Destructeur de CBateau, adr = " << this << endl;
  if (m_pDegats != NULL)
  {
    delete m_pDegats;
    m_pDegats = NULL;
  }
}
