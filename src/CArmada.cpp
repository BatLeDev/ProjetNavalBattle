#include "CArmada.h"

/*
 * Ajoute un bateau à la liste des bateaux de l'armada avec la méthode push_back de la class vector
 * unBat est passé par référence (car présence de &) pour éviter de copier inutilement le bateau, 
 * car la méthode push_back créé également une copie
 * 
 * @param &unBat référence vers le bateau à ajouter
 */
void CArmada::ajouterBateau(CBateau& unBat) 
{
  m_listeBateaux.push_back(unBat); // La méthode push_back créé une copie du bateau et l'ajoute à la liste
}

/**********************************************/

/*
 * Lis le fichier flotille.txt présent dans le dossier ./data
 * et ajoute les bateau à la liste m_listeBateaux en position 0,0
 * Ce fichier contient la liste complète de tous les bateaux au format :
 * nomDuBateau<ESPACE>nombreSurGrille<ESPACE>nombreCasesHorizontales
 * 
 * Les lignes commençant par un # sont ignorées
 */
void CArmada::getArmadaFromFile() 
{
  const char* nomFich = "../data/flotille.txt"; // Fichier source

  ifstream fluxIn(nomFich, ios::in); // Constructeur de la classe ifstream pour lire le fichier

  while (!fluxIn.eof()) // lecture du fichier ligne par ligne
  {
    string ligne;
    getline(fluxIn, ligne, '\n'); // Lecture de la ligne (jusqu'a '\n' qui est ignoré et pas ajouté à ligne)

    if (ligne[0] == '#' || ligne.empty()) continue;  // Ignore les lignes commençant par # ou vides


    // Séparation des données
    istringstream tmp(ligne);
    string nomDuBateau;
    int nombreSurGrille;
    int nombreCasesHorizontales;

    if (!(tmp >> nomDuBateau >> nombreSurGrille >> nombreCasesHorizontales)) // tmp renvoie faux si la ligne contiens des types de données incorrectes
    {
      cout << "Erreur : la ligne est mal formatée : \"" << ligne << "\"" << endl;
      continue;
    }

    cout << "Import du bateau : " << ligne << endl;

    if (nombreCasesHorizontales > TAILLE_GRILLE-1) {
      cout << "Erreur : le bateau " << nomDuBateau << " est trop grand pour la grille" << endl;
    }
    else if (nombreSurGrille < 1) {
      cout << "Erreur : le bateau " << nomDuBateau << " doit être présent au moins une fois sur la grille" << endl;
    }
    else if (nombreCasesHorizontales < 2) {
      cout << "Erreur : le bateau " << nomDuBateau << " doit avoir au moins 2 cases" << endl;
    } else {
      CBateau b(nomDuBateau, {0, 0}, nombreCasesHorizontales);
      for (int i = 0; i < nombreSurGrille; i++) // On ajoute le bateau autant de fois que demandé
      {
        ajouterBateau(b);
      }
    }
    
  }

  fluxIn.close();
}

/**********************************************/

/*
 * Parcours la liste des bateaux et les positionnent aléatoirement sur la grille
 * Le nombre d'essai max est définis par la constante MAXESSAIS
 * 
 * @return false si le placement est impossible
 */
bool CArmada::placerAleatoirement() 
{
  bool result = true;
  srand(time(NULL));
  int effectif = getEffectifTotal();

  for (int i = 0; i < effectif; i++) // Parcour tous les bateau de la liste
  {
    CBateau* bateau = &m_listeBateaux[i];
    int essais = 0;
    bool place = false; // Passe a vrais quand le bateau sera positionné
    while (!place && essais < MAXESSAIS) // Tant que le nombre d'essais n'est pas atteint
    {
      // Génère un nombre aléatoire entre 0 et TAILLE_GRILLE-1 pour la ligne (si grille 10x10, entre 0 et 9)
      int ligne = rand() % (TAILLE_GRILLE-1);
      
      // Génère un nombre aléatoire entre 0 et (TAILLE_GRILLE - tailleDuBateau) pour la colonne
      // si grille 10x10 et bateau de taille 3 la colonne sera entre 0 et 7, 
      // Limites : le bateau peut etre en 0-3 ou 7-9
      int colonne = rand() % (TAILLE_GRILLE - bateau->getTaille());

      // On cherche a savoir si cette position est correcte pour le bateau, ou si il y a une collision
      bool collision = false;
      int j = 0;
      while (j < i && !collision) // Parcour des bateaux déjà placés
      {
        CBateau* autre = &m_listeBateaux[j];
        if (autre->getPosition().first == ligne) // Check si les bateaux sont sur la même ligne
        {
          int debutAutre = autre->getPosition().second; // Début du bateau déjà placé sur la ligne
          int finAutre = debutAutre + autre->getTaille() - 1; // Fin du bateau déjà placé sur la ligne
          int finBateau = colonne + bateau->getTaille() - 1; // Fin du bateau à placer sur la ligne
          if (
            (colonne >= debutAutre && colonne <= finAutre) || // Si le début du bateau est dans un autre bateau
            (finBateau >= debutAutre && finBateau <= finAutre) // Si la fin du bateau est dans un autre bateau
          )
          {
            collision = true;
          }
        }
        j++;
      }

      if (!collision) // Si il n'y a pas de collision
      {
        bateau->setPosition(ligne, colonne); // On place le bateau
        place = true;
      }
      essais++;
    }

    if (!place) // Si le bateau n'a pas pu être placé
    {
      result = false;
      break;
    }
  }

  return result;
}

/**********************************************/

/*
 * Compte le nombre de bateau non coulés
 * @return le nombre de bateau non coulés
 */
int CArmada::getEffectif()
{
  int effectif = 0;
  int effectifTotal = getEffectifTotal();

  for (int i = 0; i < effectifTotal; i++)
  {
    if (!m_listeBateaux[i].estCoule())
    {
      effectif++;
    }
  }
  return effectif;
}

/**********************************************/

/*
 * Récuère la taille de m_listeBateaux
 * @return le nombre total de bateaux
 */
int CArmada::getEffectifTotal()
{
  return m_listeBateaux.size();
}

/**********************************************/

/*
 * Calcul le nombre de cases total occupées par les bateaux de l'armada
 * @return le nombre total de cases occupées par les bateaux de l'armada
 */
int CArmada::getNbreTotCases()
{
  int total = 0;
  for (int i = 0; i < getEffectifTotal(); i++)
  {
    total += m_listeBateaux[i].getTaille();
  }
  return total;
}

/**********************************************/

/*
 * Renvoie l'adresse du bateau à l'index i
 * @param i index du bateau à récupérer
 * @return l'adresse du bateau à l'index i
 */
CBateau* CArmada::getBateau(int i)
{
  if (i < 0 || i >= getEffectifTotal()) return nullptr;
  return &m_listeBateaux[i]; // Ici le & permet de récupérer l'adresse du bateau
}
