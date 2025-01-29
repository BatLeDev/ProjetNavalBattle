#include "CGui.h"

void testConstructeur1();
void testConstructeur2();
void testConstructeurCopy();
void testOperateurAffectation();
void testOperateurAffichage();
void testDestructeur();

int main()
{
  testConstructeur1();
  testConstructeur2();
  testConstructeurCopy();
  testOperateurAffectation();
  testOperateurAffichage();
  testDestructeur();

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

  cout << "Cas anormal : Pointeurs nulls" << endl;
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
