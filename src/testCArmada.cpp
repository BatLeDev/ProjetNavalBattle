#include "CArmada.h"

void testConstructeur();
void testAjouterBateau();
void testGetArmadaFromFile();
void testPlacerAleatoirement();

int main()
{
  testConstructeur();
  testAjouterBateau();
  testGetArmadaFromFile();
  testPlacerAleatoirement();

  return 0;
}

void testConstructeur()
{
  cout << "Construction d'une Armada" << endl;

  CArmada a1 = CArmada();
  if (a1.getEffectifTotal() != 0)
  {
    cout << "Erreur : l'armada devrai etre vide" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}

void testAjouterBateau()
{
  cout << "Test de la méthode ajouterBateau" << endl;

  CArmada a1 = CArmada();
  CBateau b1 = CBateau("Porte-avion", {0, 0}, 5);

  a1.ajouterBateau(b1);

  cout << "Cas normal : Ajout d'un bateau" << endl;
  if (a1.getEffectifTotal() != 1)
  {
    cout << "Erreur : l'armada devrai contenir un bateau" << endl;
  } else {
    cout << "Ok" << endl;
  }

  // Cas pour moi, pour comprendre la différence entre référence et adresse
  /*
    cout << "Cas normal : manipulations de références et d'adresses" << endl;
    CBateau* b2 = new CBateau("Sous-marin", {0, 0}, 3); // Création d'un bateau dynamique, il faut le supprimer manuellement, on récuère son adresse dans un pointeur *
    a1.ajouterBateau(*b2); // On ajoute le bateau à l'armada, * devant b2 permet de récupérer le bateau et non l'adresse du bateau
    if (a1.getEffectifTotal() != 2)
    {
      cout << "Erreur : l'armada devrai contenir deux bateaux" << endl;
    } else {
      cout << "Ok" << endl;
    }
    delete b2; // On libère la mémoire du bateau dynamique
  */

  cout << "Cas limite : Ajout du même bateau" << endl;
  a1.ajouterBateau(b1);
  if (a1.getEffectifTotal() != 2)
  {
    cout << "Erreur : l'armada devrai contenir deux bateaux" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}

void testGetArmadaFromFile()
{
  cout << "Test de la méthode getArmadaFromFile" << endl;

  cout << "Cas normal : Lecture du fichier flotille.txt" << endl;
  // Remplissage du fichier flotille.txt
  ofstream file("flotille.txt");
  file << "Porte-avion 1 4" << endl;
  file << "Croiseur 2 3" << endl;
  file << "Torpilleur 2 2" << endl;
  file.close();

  CArmada a1 = CArmada();
  a1.getArmadaFromFile();

  if (a1.getEffectifTotal() != 5)
  {
    cout << "Erreur : l'armada devrai contenir 5 bateaux" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Lecture du fichier flotille.txt vide" << endl;
  // Remplissage du fichier flotille.txt
  ofstream file2("flotille.txt");
  file2.close();

  CArmada a2 = CArmada();
  a2.getArmadaFromFile();

  if (a2.getEffectifTotal() != 0)
  {
    cout << "Erreur : l'armada devrai être vide" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Lecture du fichier flotille.txt avec des commentaires" << endl;
  // Remplissage du fichier flotille.txt
  ofstream file3("flotille.txt");
  file3 << "# Porte-avion 1 4" << endl;
  file3 << "Croiseur 2 3" << endl;
  file3 << "Torpilleur 2 2" << endl;
  file3.close();

  CArmada a3 = CArmada();
  a3.getArmadaFromFile();

  if (a3.getEffectifTotal() != 4)
  {
    cout << "Erreur : l'armada devrai contenir 4 bateaux" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "Cas d'erreur : Lecture du fichier flotille.txt avec des erreurs" << endl;
  // Remplissage du fichier flotille.txt
  ofstream file4("flotille.txt");
  file4 << "Porte-avion 1 4" << endl;
  file4 << "2 Croiseur5" << endl;
  file4 << "   # il y a des espaces avant le commentaire" << endl;

  cout << "2 erreurs attendues :" << endl;
  CArmada a4 = CArmada();
  a4.getArmadaFromFile();

  if (a4.getEffectifTotal() != 1)
  {
    cout << "Erreur : l'armada devrai contenir 1 bateau" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}

void testPlacerAleatoirement()
{
  cout << "Test de la méthode placerAleatoirement" << endl;

  cout << "Cas normal : Placement aléatoire des bateaux" << endl;
  CBateau b1 = CBateau("Porte-avion", {0, 0}, 7);
  CBateau b2 = CBateau("Croiseur", {0, 0}, 10);

  CArmada a1 = CArmada();
  a1.ajouterBateau(b1);
  a1.ajouterBateau(b2);
  a1.ajouterBateau(b2);

  if (a1.placerAleatoirement())
  {
    cout << "Ok" << endl;
  } else {
    cout << "Erreur : le placement des bateaux devrai être possible" << endl;
  }

  cout << "Cas limite : Placement aléatoire des bateaux qui remplissent 100/100 de la grille (Peut échouer)" << endl;

  CArmada a2 = CArmada();
  for (int i = 0; i < 10; i++) {
    a2.ajouterBateau(b2);
  }

  if (a2.placerAleatoirement())
  {
    cout << "Ok" << endl;
  } else {
    cout << "Erreur : le placement des bateaux devrai être possible" << endl;
  }

  cout << "Cas d'erreur : Placement aléatoire des bateaux impossible" << endl;

  CArmada a3 = CArmada();
  for (int i = 0; i<11; i++) {
    a3.ajouterBateau(b1);
  }

  if (a3.placerAleatoirement())
  {
    cout << "Erreur : le placement des bateaux devrai être impossible" << endl;
  } else {
    cout << "Ok" << endl;
  }
}
