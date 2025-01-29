#include "CArmada.h"

#define FILENAME "../ws/flotille.txt"

void testConstructeur();
void testAjouterBateau();
void testGetArmadaFromFile();
void testPlacerAleatoirement();
void testGetEffectif();
void testGetNbreTotCases();
void testGetBateau();

int main()
{
  testConstructeur();
  testAjouterBateau();
  testGetArmadaFromFile();
  testPlacerAleatoirement();
  testGetEffectif();
  testGetNbreTotCases();
  testGetBateau();

  cout << "getTotalEffectif est testé par l'intermédiaire de toutes les autres classes" << endl;

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
  ofstream file(FILENAME);
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
  ofstream file2(FILENAME);
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
  ofstream file3(FILENAME);
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
  ofstream file4(FILENAME);
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

  cout << "Cas limite : Placement aléatoire des bateaux qui remplissent toute la grille (Peut échouer)" << endl;

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

  cout << "------------------------------" << endl;
}

void testGetEffectif()
{
  cout << "Test de la méthode getEffectif" << endl;

  cout << "Cas normal : 0 bateaux coulés" << endl;
  CArmada a1 = CArmada();
  CBateau b1 = CBateau("Voilier", {0, 0}, 2);
  CBateau b2 = CBateau("Croiseur", {0, 0}, 3);

  a1.ajouterBateau(b1);
  a1.ajouterBateau(b2);

  if (a1.getEffectif() != 2)
  {
    cout << "Erreur : l'armada devrai contenir 2 bateaux non coulés" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "Cas normal : 1 bateau coulé" << endl;
  
  CArmada a2 = CArmada();
  b1.tirAdverse(make_pair(0, 0));
  b1.tirAdverse(make_pair(0, 1));
  a2.ajouterBateau(b1);
  a2.ajouterBateau(b2);

  if (a2.getEffectif() != 1)
  {
    cout << "Erreur : l'armada devrai contenir 1 bateau non coulé" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : 2 bateaux coulés" << endl;

  CArmada a3 = CArmada();
  b2.tirAdverse(make_pair(0, 0));
  b2.tirAdverse(make_pair(0, 1));
  b2.tirAdverse(make_pair(0, 2));

  a3.ajouterBateau(b1);
  a3.ajouterBateau(b2);

  if (a3.getEffectif() != 0)
  {
    cout << "Erreur : l'armada devrai contenir 0 bateau non coulé" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Armada vide" << endl;

  CArmada a4 = CArmada();

  if (a4.getEffectif() != 0)
  {
    cout << "Erreur : l'effectif de l'armada devrai être de 0" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}

void testGetNbreTotCases()
{
  cout << "Test de la méthode getNbreTotCases" << endl;

  cout << "Cas normal : 2 bateaux de 2 cases" << endl;
  CArmada a1 = CArmada();
  CBateau b1 = CBateau("Voilier", {0, 0}, 2);
  CBateau b2 = CBateau("Croiseur", {0, 0}, 2);

  a1.ajouterBateau(b1);
  a1.ajouterBateau(b2);

  if (a1.getNbreTotCases() != 4)
  {
    cout << "Erreur : l'armada devrai contenir 4 cases" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : 0 bateaux" << endl;

  CArmada a2 = CArmada();

  if (a2.getNbreTotCases() != 0)
  {
    cout << "Erreur : l'armada devrai contenir 0 cases" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}

void testGetBateau()
{
  cout << "Test de la méthode getBateau" << endl;

  CArmada a1 = CArmada();
  CBateau b1 = CBateau("Voilier", {0, 0}, 2);
  CBateau b2 = CBateau("Croiseur", {0, 0}, 2);
  b2.tirAdverse(make_pair(0, 0));
  b2.tirAdverse(make_pair(0, 1));
  a1.ajouterBateau(b1);
  a1.ajouterBateau(b2);

  cout << "Cas normal : Récupération du premier bateau" << endl;
  if (a1.getBateau(0)->getNom() != "Voilier")
  {
    cout << "Erreur : le premier bateau devrai être le voilier" << endl;
  }
  else if (a1.getBateau(0) == &b1)
  {
    cout << "Erreur : les bateaux ne sont pas copiés lors de l'insertion dans l'armada" << endl;
  } 
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Récupération d'un bateau coulé" << endl;
  if (a1.getBateau(1)->getNom() != "Croiseur")
  {
    cout << "Erreur : le deuxième bateau devrai être le croiseur" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Récupération d'un bateau inexistant" << endl;
  if (a1.getBateau(2) != nullptr)
  {
    cout << "Erreur : le troisième bateau ne devrai pas exister" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}
