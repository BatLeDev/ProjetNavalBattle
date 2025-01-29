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
  bool ret = false;
  if (m_pArmada == nullptr)
  {
    cout << "Erreur : pointeur non initialisé" << endl;
  } else {
    ret = m_pArmada->placerAleatoirement();
  }
  return ret;
}

/**********************************************/

pair<int, int> CGui::choisirAttaque()
{
  int x, y;
  cout << "Entrez les coordonnées de votre attaque (sous la forme 'ligne colonne') : ";
  
  while (!(cin >> x >> y) || x < 0 || x >= (TAILLE_GRILLE - 1) || y < 0 || y >= (TAILLE_GRILLE - 1))
  {
    cout << "Erreur : coordonnées invalides, veuillez réessayer : ";
    cin.clear();
    cin.ignore(); // Cette ligne viens vider le buffer d'entrée, sinon j'ai une boucle infinie
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
  if (m_pArmada == nullptr || m_pCoups == nullptr)
  {
    cout << "Erreur : pointeurs non initialisés" << endl;
    return;
  }

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

  // Affichage simple des grilles, l'une en dessous de l'autre
  /*
    affiherLaGrille(os, "joueur")
    afficherLaGrille(os, "adversaire")
  */

  /*
    Pour un affichage plus élégant, je me suis permi un prompt a ChatGPT (seul code généré par IA dans ce travail)
    Je lui ai demandé de reformater la sortie de la fonction membre afficherLaGrille pour obtenir un affichage des 2 grilles cote a cote
    J'ai essayé de rajouter des commentaires au code généré pour comprendre son fonctionnement et je l'ai légèrement modifié pour le simpifier
  */
  stringstream ssJoueur, ssAdv; // Dans un premier temps, on récupère la sortie de la fonction dans des flux de chaines de caractères, pour mieux les formater par la suite
  afficherLaGrille(ssJoueur, "joueur");
  afficherLaGrille(ssAdv, "adversaire");

  // Grace a la méthode getline qui permet, comme pour un fichier, de lire les lignes d'un flux, 
  // on sauvegarde dans des vecteurs chaque ligne des 2 grilles
  vector<string> lignesJoueur, lignesAdv;
  string ligne;
  while (getline(ssJoueur, ligne))
  {
    lignesJoueur.push_back(ligne);
  }
  while (getline(ssAdv, ligne))
  {
    lignesAdv.push_back(ligne);
  }

  size_t nbLignes = lignesJoueur.size(); // Le format de la fonction membre size de size_t, qui correspond globalement a un int (pas exactectement)

  for (size_t i = 0; i < nbLignes; ++i) // Pour chaque lignes, on les fusionnes pour ne recréé plus qu'une seul ligne, séparé par une tabulation
  {
    // os << lignesJoueur[i] << "\t\t" << lignesAdv[i] << endl; // '\t' est le caractère de tabulation sous linux
    os << lignesJoueur[i] << "    " << BG_TEXT(" ", BG_WHITE) << "    " << lignesAdv[i] << endl;
  }
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
  if (jouOuAdv != "joueur" && jouOuAdv != "adversaire")
  {
    cout << "Erreur : mot clé inconnu" << endl;
    return;
  }

  if (jouOuAdv == "joueur")
  {
    // os << "Grille du joueur : " << endl;
    os << STYLED_TEXT("-- Grille du joueur --", STYLE_BOLD, COLOR_GREEN) << endl;
  }
  else if (jouOuAdv == "adversaire")
  {
    // os << "Grille de l'adversaire : " << endl;
    os << STYLED_TEXT("-- Grille adverse --", STYLE_BOLD, COLOR_RED) << endl;
  }

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
      char c = (jouOuAdv == "joueur") ? m_grilleJou[i][j] : m_grilleAdv[i][j];
      
      if (c == 'B')
      {
        os << COLORED_TEXT(c, COLOR_YELLOW) << " ";
      }
      else if (c == 'X')
      {
        os << COLORED_TEXT(c, COLOR_RED) << " ";
      }
      else if (c == 'O')
      {
        os << COLORED_TEXT(c, COLOR_BLUE) << " ";
      }
      else
      {
        os << c << " ";
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
 * Respect de la règle des 3 car m_pArmada et m_pCoups sont des pointeurs
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
  // os << "------------------ Plateau de jeu : ------------------" << endl;
  os << STYLED_TEXT("----------------- Plateau de jeu : -----------------", STYLE_BOLD, COLOR_BLUE) << endl;
  theG.remplirDeuxGrilles(os);
  return os;
}
