#include "CGui.h"

/**********************************************/
/*                Constructeurs               */
/**********************************************/

/*
 * Constructeur par défaut
 * Définit simplement les données membres a NULL
 */
CGui::CGui()
{
  m_pArmada = NULL;
  m_pCoups = NULL;
}

/*
 * Constructeur avec les pointeurs vers m_pArmada et m_pCoups
 * @param pArmada pointeur vers l'armada du joueur
 * @param pCoups pointeur vers la structure d'enregistrement des tirs
 */
CGui::CGui(CArmada *pArmada, CCoups *pCoups)
{
  m_pArmada = pArmada;
  m_pCoups = pCoups;
}

/*
 * Constructeur de copie
 * @param g référence vers l'objet à copier
 */
CGui::CGui(const CGui &g)
{
  for (int i = 0; i < TAILLE_GRILLE - 1; ++i)
  {
    for (int j = 0; j < TAILLE_GRILLE - 1; ++j)
    {
      m_grilleJou[i][j] = g.m_grilleJou[i][j];
      m_grilleAdv[i][j] = g.m_grilleAdv[i][j];
    }
  }
  m_pArmada = new CArmada(*g.m_pArmada);
  m_pCoups = new CCoups(*g.m_pCoups);
}

/**********************************************/

/*
 * Modificateur : mise à jour des attributs
 * @param pArmada pointeur vers l'armada du joueur
 * @param pCoups pointeur vers la structure d'enregistrement des tirs
 */
void CGui::setArmadaCoups(CArmada *pArmada, CCoups *pCoups)
{
  m_pArmada = pArmada;
  m_pCoups = pCoups;
}

/**********************************************/

/*
 * Méthode appelée au début du jeu pour placer tous les bateaux sur la grille
 * @return true si les bateaux ont été placés, false sinon
 */
bool CGui::positionnerBateaux()
{
  bool ret = m_pArmada->placerAleatoirement();
  return ret;
}

/**********************************************/

pair<int, int> CGui::choisirAttaque()
{
  int x, y;
  cout << "Entrez les coordonnées de votre attaque (ligne, colonne) : ";
  cin >> x >> y;

  while (x < 0 || x >= (TAILLE_GRILLE - 1) || y < 0 || y >= (TAILLE_GRILLE - 1))
  {
    cout << "Erreur : coordonnées invalides, veuillez réessayer : ";
    cin >> x >> y;
  }
  return make_pair(x, y);
}

/**********************************************/

void CGui::afficheGagne()
{
  cout << "------------------------------------" << endl;
  cout << "      GG bonhomme ta gangé !!!      " << endl;
  cout << "------------------------------------" << endl;
}

void CGui::affichePerdu()
{
  cout << "------------------------------------" << endl;
  cout << "     C'est si triste, ta perdu...   " << endl;
  cout << "------------------------------------" << endl;
}

/**********************************************/

/*
 * Modificateur : Remplis les grilles m_grilleJou et m_grilleAdv
 * Remplis la grille m_grilleJou :
 *    - 'B' pour les bateaux cases des bateaux non touchés
 *    - 'X' pour les cases des bateaux touchés
 *    - 'O' pour les cases où l'adversaire a fait plouf
 * 
 * Remplis la grille m_grilleAdv :
 *    - 'X' pour les cases où le joueur a touché des bateaux
 *    - 'O' pour les cases où le joueur a fait plouf
 * @param os flux de sortie
 */
void CGui::remplirDeuxGrilles(ostream &os)
{
  // Remplissage initial des grilles
  for (int i = 0; i < TAILLE_GRILLE - 1; ++i)
  {
    for (int j = 0; j < TAILLE_GRILLE - 1; ++j)
    {
      m_grilleJou[i][j] = '-';
      m_grilleAdv[i][j] = '-';
    }
  }

  //-------------------------------------------------------------------
  // Remplissage de la grille m_grilleJou
  int effectif = m_pArmada->getEffectifTotal();

  for (int i = 0; i < effectif; i++) // Parcours des bateaux et check si touché
  {
    CBateau* bateau = m_pArmada->getBateau(i);
    pair<int, int> position = bateau->getPosition();
    int taille = bateau->getTaille();

    for (int j = 0; j < taille; j++)
    {
      if (bateau->getDegats(j))
      {
        m_grilleJou[position.first][position.second + j] = 'X';
      }
      else
      {
        m_grilleJou[position.first][position.second + j] = 'B';
      }
    }
  }

  // Parcours des coups plouf adverses
  int nbPloufs = m_pCoups->getTaille("ploufAdverse");
  for (int i = 0; i < nbPloufs; i++)
  {
    pair<int, int> p = m_pCoups->getPair("ploufAdverse", i);
    m_grilleJou[p.first][p.second] = 'O';
  }

  //-------------------------------------------------------------------
  // Remplissage de la grille m_grilleAdv
  // Parcours des coups touchés du joueur
  int nbTouche = m_pCoups->getTaille("touche");
  for (int i = 0; i < nbTouche; i++)
  {
    pair<int, int> p = m_pCoups->getPair("touche", i);
    m_grilleAdv[p.first][p.second] = 'X';
  }

  // Parcours des coups plouf du joueur
  nbPloufs = m_pCoups->getTaille("dansLEau");
  for (int i = 0; i < nbPloufs; i++)
  {
    pair<int, int> p = m_pCoups->getPair("dansLEau", i);
    m_grilleAdv[p.first][p.second] = 'O';
  }

  afficherLaGrille(os, "joueur");
  afficherLaGrille(os, "adversaire");
}

/**********************************************/

/*
 * Génère un flux de sortie pour afficher un plateau de jeu d'un joueur
 * La grille contiens les 'légendes' des lignes et colonnes
 * @param os flux de sortie
 * @param jouOuAdv mot clé "joueur" ou "adversaire"
 */
void CGui::afficherLaGrille(ostream &os, string jouOuAdv)
{
  os << "Grille du " << jouOuAdv << " : " << endl;
  os << "  ";
  for (int i = 0; i < TAILLE_GRILLE - 1; i++)
  {
    os << i << " ";
  }
  os << endl;

  for (int i = 0; i < TAILLE_GRILLE - 1; i++)
  {
    os << i << " ";
    for (int j = 0; j < TAILLE_GRILLE - 1; j++)
    {
      if (jouOuAdv == "joueur")
      {
        os << m_grilleJou[i][j] << " ";
      }
      else if (jouOuAdv == "adversaire")
      {
        os << m_grilleAdv[i][j] << " ";
      }
      else
      {
        os << "Erreur : mot clé inconnu" << endl;
      }
    }
    os << endl;
  }
}

/**********************************************/

/*
 * Destructeur
 * Libère la mémoire allouée pour m_pArmada et m_pCoups
 * Respect de la règle des 3 car m_pArmada et m_pCoups sont des pointeurs
 */
CGui::~CGui()
{
  cout << "Destructeur de CGui, adr = " << this << endl;
  if (m_pArmada != nullptr)
  {
    delete m_pArmada;
    m_pArmada = nullptr;
  }
  if (m_pCoups != nullptr)
  {
    delete m_pCoups;
    m_pCoups = nullptr;
  }
}

/*
 * Surcharge de l'opérateur d'affectation
 * Respect de la règle des 3 car m_pDegats est un pointeur (tableau dynamique)
 * @param b le bateau à copier
 */
CGui &CGui::operator=(const CGui &bToCopy)
{
  if (this != &bToCopy)
  {
    // Copie de m_grilleJou et m_grilleAdv
    for (int i = 0; i < TAILLE_GRILLE - 1; ++i)
    {
      for (int j = 0; j < TAILLE_GRILLE - 1; ++j)
      {
        m_grilleJou[i][j] = bToCopy.m_grilleJou[i][j];
        m_grilleAdv[i][j] = bToCopy.m_grilleAdv[i][j];
      }
    }

    // Copie de m_pArmada
    if (m_pArmada != nullptr)
    {
      delete m_pArmada;
    }
    m_pArmada = new CArmada(*bToCopy.m_pArmada);

    // Copie de m_pCoups
    if (m_pCoups != nullptr)
    {
      delete m_pCoups;
    }
    m_pCoups = new CCoups(*bToCopy.m_pCoups);
  }
  return *this;
}

ostream &operator<<(ostream &os, CGui &theG)
{
  os << "--------------- Plateau de jeu : ---------------" << endl;
  theG.remplirDeuxGrilles(os);
  return os;
}
