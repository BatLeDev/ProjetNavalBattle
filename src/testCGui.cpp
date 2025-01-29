#include "CGui.h"

void testConstructeur1();
void testConstructeur2();
void testConstructeurCopy();
void testOperateurAffectation();
void testOperateurAffichage();
void testDestructeur();
void testAfficherGagner();
void testAfficherPerdu();
void testSetPosition();
void testPositionnerBateaux();
void testChoisirAttaque();

int main()
{
  testConstructeur1();
  testConstructeur2();
  testConstructeurCopy();
  testOperateurAffectation();
  testOperateurAffichage();
  testDestructeur();
  testAfficherGagner();
  testAfficherPerdu();
  testSetPosition();
  testPositionnerBateaux();
  testChoisirAttaque();

  return 0;
}

void testConstructeur1()
{
  cout << "Test Construction d'un Gui 'vide'" << endl;

  CGui g1 = CGui();
  cout << "Erreur attendu car les pointeurs sont nulls" << endl;
  cout << g1 << endl;
  
  cout << "------------------------------" << endl;
}

void testConstructeur2()
{
  cout << "Test Construction d'un Gui avec des pointeurs" << endl;

  cout << "Cas normal : Pointeurs existants" << endl;
  CArmada *pArmada = new CArmada();
  CCoups *pCoups = new CCoups();

  CGui g2 = CGui(pArmada, pCoups);
  cout << g2 << endl;

  cout << "Cas normal : Pointeurs nulls" << endl;
  CGui g3 = CGui(nullptr, nullptr);
  cout << g2 << endl;

  cout << "------------------------------" << endl;
}

void testConstructeurCopy()
{
  cout << "Test Construction d'un Gui par copie" << endl;

  CArmada *pArmada = new CArmada();
  pArmada->getArmadaFromFile();
  CCoups *pCoups = new CCoups();

  CGui g1 = CGui(pArmada, pCoups);
  CGui g2 = CGui(g1);
  cout << g2 << endl;
  cout << "Si sur la grille on ne vois que des bateaux en 0,0, c'est normal, ils ne sont pas encore placés" << endl;

  cout << "------------------------------" << endl;
}

void testOperateurAffectation()
{
  cout << "Test de l'Opérateur d'affectation" << endl;

  CArmada *pArmada = new CArmada();
  pArmada->getArmadaFromFile();
  CCoups *pCoups = new CCoups();

  CGui g1 = CGui(pArmada, pCoups);
  CGui g2 = CGui();
  g2 = g1;
  cout << g2 << endl;
  cout << "Si sur la grille on ne vois que des bateaux en 0,0, c'est normal, ils ne sont pas encore placés" << endl;

  cout << "------------------------------" << endl;
}

void testOperateurAffichage()
{
  cout << "Opérateur d'affichage" << endl;

  CArmada *pArmada = new CArmada();
  CBateau *pBateau = new CBateau("Porte-avion", {1, 3}, 5);
  CBateau *pBateau2 = new CBateau("Croiseur", {4, 0}, 10);
  pBateau2->tirAdverse(make_pair(4, 0));
  pBateau2->tirAdverse(make_pair(4, 1));
  pArmada->ajouterBateau(*pBateau);
  pArmada->ajouterBateau(*pBateau2);

  CCoups *pCoups = new CCoups();

  CGui g1 = CGui(pArmada, pCoups);
  cout << g1 << endl;
  cout << "On devrai voir pour la grille du joueur un bateau en 1,3 de taille 5 et un bateau sur toute la ligne 4 ayant été touché sur les 2 premières colonnes" << endl;

  cout << "------------------------------" << endl;
}

void testDestructeur()
{
  cout << "Test du destructeur" << endl;

  CArmada *pArmada = new CArmada();
  pArmada->getArmadaFromFile();
  CCoups *pCoups = new CCoups();

  CGui *g1 = new CGui(pArmada, pCoups);
  pArmada = nullptr;
  pCoups = nullptr;
  cout << "On devrai voir une destruction de CGui, de CCoups et de CArmada" << endl;
  delete g1;

  cout << "------------------------------" << endl;
}

void testAfficherGagner()
{
  cout << "Test de la méthode afficheGagne" << endl;
  cout << "On devrait voir un message de victoire" << endl;

  CGui g1 = CGui();
  g1.afficheGagne();

  cout << "------------------------------" << endl;
}

void testAfficherPerdu()
{
  cout << "Test de la méthode affichePerdu" << endl;
  cout << "On devrait voir un message de défaite" << endl;

  CGui g1 = CGui();
  g1.affichePerdu();

  cout << "------------------------------" << endl;
}

void testSetPosition()
{
  cout << "Test de la méthode setArmadaCoups" << endl;

  CArmada *pArmada = new CArmada();
  CBateau *pBateau = new CBateau("Porte-avion", {1, 3}, 5);
  CBateau *pBateau2 = new CBateau("Croiseur", {4, 0}, 10);
  pBateau2->tirAdverse(make_pair(4, 0));
  pBateau2->tirAdverse(make_pair(4, 1));
  pArmada->ajouterBateau(*pBateau);
  pArmada->ajouterBateau(*pBateau2);
  CCoups *pCoups = new CCoups();

  CGui g1 = CGui();
  cout << "Affichage avant setArmadaCoups : On devrai avoir une erreur" << endl;
  cout << g1 << endl;

  g1.setArmadaCoups(pArmada, pCoups);
  cout << g1 << endl;
  cout << "On devrait voir pour la grille du joueur un bateau en 1,3 de taille 5 et un bateau sur toute la ligne 4 ayant été touché sur les 2 premières colonnes" << endl;

  cout << "------------------------------" << endl;
}

void testPositionnerBateaux()
{
  cout << "Test de la méthode positionnerBateaux" << endl;

  CArmada *pArmada = new CArmada();
  CBateau *pBateau1 = new CBateau("Porte-avion", {0, 0}, 3);
  CBateau *pBateau2 = new CBateau("Croiseur", {0, 0}, 10);
  pArmada->ajouterBateau(*pBateau2);
  pArmada->ajouterBateau(*pBateau2);
  pArmada->ajouterBateau(*pBateau1);
  CCoups *pCoups = new CCoups();

  CGui g1 = CGui();
  cout << "On devrait voir un message d'erreur car les pointeurs sont nulls" << endl;
  if (g1.positionnerBateaux()) 
  {
    cout << "Erreur : Normalement, ça devrai vous afficher une erreur" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  CGui g2 = CGui(pArmada, pCoups);
  cout << "Les bateaux devrai êtres placé aléatoirement sur la grille, il dois y avoir 1 bateaux de taille 3 et 2 de taille 10" << endl;
  if (g2.positionnerBateaux()) 
  {
    cout << "Ok" << endl;
  }
  else
  {
    cout << "Erreur : Normalement, ça devrai vous afficher une erreur" << endl;
  }
  cout << g2 << endl;

  cout << "------------------------------" << endl;
}

void testChoisirAttaque()
{
  cout << "Test de la méthode choisirAttaque" << endl;

  CGui g1 = CGui();
  cout << "Cas normal : coordonnées valides (Entrez '1 3')" << endl;
  if (g1.choisirAttaque() == make_pair(1, 3))
  {
    cout << "Ok" << endl;
  }
  else
  {
    cout << "Erreur : Les coordonnées de la pair devrai être 1 3" << endl;
  }

  cout << "Cas d'erreur : coordonnées invalides (Entrez '25 4' puis '1 3')" << endl;
  if (g1.choisirAttaque() == make_pair(1, 3))
  {
    cout << "Erreur : Normalement, ça devrai vous redemmander jusqu'a avoir des coordonnées valides" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas d'erreur : coordonnées invalides (Entrez 'Salut !' puis '0 0')" << endl;
  if (g1.choisirAttaque() == make_pair(0, 0))
  {
    cout << "Erreur : Normalement, ça devrai vous redemmander jusqu'a avoir des coordonnées valides" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }
}
