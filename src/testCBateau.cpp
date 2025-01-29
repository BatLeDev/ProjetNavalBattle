#include "CBateau.h"

void testConstructeur1();
void testConstructeur2EtAccesseurs();
void testCopyConstructeur();
void testOperatorAffectation();
void testDestructeur();
void testSetPosition();
void testTirAdverse();
void testGetDegats();
void testEstCoule();

int main()
{
  testConstructeur1();
  testConstructeur2EtAccesseurs();
  testCopyConstructeur();
  testOperatorAffectation();
  testDestructeur();
  testSetPosition();
  testTirAdverse();
  testGetDegats();
  testEstCoule();

  return 0;
}

void testConstructeur1()
{
  cout << "Construction d'un bateau 'vide'" << endl;

  CBateau b1 = CBateau();
  cout << b1 << endl;

  if (b1.getNom() != "neant")
  {
    cout << "Erreur : nom du bateau incorrect" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }
  cout << "------------------------------" << endl;
}

void testConstructeur2EtAccesseurs()
{
  cout << "Construction d'un bateau 'porte-avion' de taille 5 en (2,3)" << endl;

  CBateau b2 = CBateau("porte-avion", {2, 3}, 5);
  cout << b2 << endl;
  pair<int, int> p = b2.getPosition();

  if (b2.getNom() != "porte-avion") // nom
  {
    cout << "Erreur : nom du bateau incorrect" << endl;
  }
  else if (b2.getTaille() != 5) // taille
  {
    cout << "Erreur : taille du bateau incorrecte" << endl;
  }
  else if (p.first != 2 || p.second != 3) // position
  {
    cout << "Erreur : position du bateau incorrecte" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}

void testCopyConstructeur()
{
  cout << "Test du constructeur de copie" << endl;

  CBateau b8 = CBateau("voilier", {5, 2}, 4);
  b8.tirAdverse({5, 2}); // Tire sur la 1ere case du bateau
  CBateau b9 = CBateau(b8);
  b8.tirAdverse({5, 3}); // Tire sur la 2ème case du bateau 8 (ne doit pas affecter le bateau 9)

  cout << "Cas normal : Copie d'un bateau" << endl;
  cout << b9 << endl;

  // nom
  if (b9.getNom() != "voilier")
  {
    cout << "Erreur : nom du bateau incorrect" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  // m_pDegats
  cout << "Cas normal : Les dégats du bateau sont copiés" << endl;
  if (!b9.getDegats(0))
  {
    cout << "Erreur : le bateau devrai avoir un dégât sur sa première case" << endl;
  } else if (b9.getDegats(1))
  {
    cout << "Erreur : le bateau ne devrai pas avoir de dégât sur sa deuxième case" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}

void testOperatorAffectation()
{
  cout << "Test de l'opérateur d'affectation" << endl;

  CBateau b10 = CBateau("voilier", {5, 2}, 4);
  b10.tirAdverse({5, 2}); // Tire sur la 1ere case du bateau

  CBateau b11 = CBateau("sous-marin", {3, 4}, 3);
  b11.tirAdverse({3, 5}); // Tire sur la 2ème case du bateau

  cout << "Cas normal : Affectation d'un bateau" << endl;
  b11 = b10;
  cout << b11 << endl;

  // nom
  if (b11.getNom() != "voilier")
  {
    cout << "Erreur : nom du bateau incorrect" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  // m_pDegats
  cout << "Cas normal : Les dégats du bateau sont copiés" << endl;
  if (!b11.getDegats(0))
  {
    cout << "Erreur : le bateau devrai avoir un dégât sur sa première case" << endl;
  } else if (b11.getDegats(1))
  {
    cout << "Erreur : le bateau ne devrai pas avoir de dégât sur sa deuxième case" << endl;
  } else {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}

void testDestructeur()
{
  cout << "Test du destructeur" << endl;

  CBateau* b12 = new CBateau("voilier", {5, 2}, 4);

  cout << "Cas normal : Destruction d'un bateau" << endl;
  cout << "Le bateau doit se détruire :" << endl;
  delete b12;

  cout << "------------------------------" << endl;
}

void testSetPosition()
{
  cout << "Test de la méthode setPosition" << endl;

  CBateau b3 = CBateau("voilier", {5, 2}, 4);

  cout << "Cas normal : Déplacement du bateau en (7,4)" << endl;
  b3.setPosition(7, 4);
  pair<int, int> p = b3.getPosition();
  if (p.first != 7 || p.second != 4)
  {
    cout << "Erreur : position du bateau incorrecte" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Déplacement du bateau en (9,6) (en bordure de grille)" << endl;
  b3.setPosition(9, 6);
  p = b3.getPosition();
  if (p.first != 9 || p.second != 6)
  {
    cout << "Erreur : position du bateau incorrecte" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas d'erreur : Déplacement du bateau en (9,7) (hors grille)" << endl;
  cout << "Erreur attendue :" << endl;
  b3.setPosition(9, 7);
  p = b3.getPosition();
  if (p.first != 9 || p.second != 6)
  {
    cout << "Erreur : le bateau n'aurai pas du bouger" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}

void testTirAdverse()
{
  cout << "Test de la méthode tirAdverse" << endl;

  CBateau b4 = CBateau("sous-marin", {3, 4}, 3);

  cout << "Cas normal : Tir en (3,5) (touche une case du bateau)" << endl;
  if (!b4.tirAdverse({3, 5}))
  {
    cout << "Erreur : le tir aurait du toucher le bateau" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas normal : Tir en (3,8) (ne touche pas le bateau)" << endl;
  if (b4.tirAdverse({3, 8}))
  {
    cout << "Erreur : le tir n'aurait pas du toucher le bateau" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Tir en (3,6) (touche le bout du bateau)" << endl;
  if (!b4.tirAdverse({3, 6}))
  {
    cout << "Erreur : le tir aurait du toucher le bateau" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Tir en (3,5) (case déjà touchée)" << endl;
  if (b4.tirAdverse({3, 5}))
  {
    cout << "Erreur : le tir n'aurait pas du toucher le bateau, car le bateau étais déjà touché ici" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas d'erreur : Tir en dehors de la grille" << endl;
  cout << "Erreur attendue :" << endl;
  b4.tirAdverse({-3, 8});


  cout << "Le test de la prise de dégats est fait via le test de getDegats" << endl;
  cout << "------------------------------" << endl;
}

void testGetDegats()
{
  cout << "Test de la méthode getDegats" << endl;

  CBateau b5 = CBateau("sous-marin", {3, 4}, 3);

  cout << "Cas normal : Dégats d'une case touché" << endl;
  b5.tirAdverse({3, 5}); // Tire sur la 2eme case du bateau
  if (!b5.getDegats(1)) // Check de l'indice 1 = 2ème case du bateau
  {
    cout << "Erreur : la case touchée n'est pas considérée comme touchée" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas normal : Dégats d'une case non touché" << endl;
  if (b5.getDegats(0)) // Check de l'indice 0 = 1ère case du bateau
  {
    cout << "Erreur : la case non touchée est considérée comme touchée" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Dégats de la dernière case du bateau" << endl;
  if (b5.getDegats(2)) // Check de l'indice 2 = 3ème case du bateau
  {
    cout << "Erreur : la dernière case du bateau est considérée comme non touchée" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas d'erreur : Dégats d'une case hors bateau" << endl;
  cout << "Erreur attendue :" << endl;
  b5.getDegats(7);

  cout << "------------------------------" << endl;
}

void testEstCoule()
{
  cout << "Test de la méthode estCoule" << endl;

  CBateau b6 = CBateau("sous-marin", {3, 4}, 2);
  CBateau b7 = CBateau("sous-marin", {3, 4}, 3);

  cout << "Cas normal : Bateau non coulé" << endl;
  if (b6.estCoule())
  {
    cout << "Erreur : le bateau est considéré comme coulé alors qu'il ne l'est pas" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas normal : Bateau coulé" << endl;
  b6.tirAdverse({3, 4}); // Tire sur la 1ère case du bateau
  b6.tirAdverse({3, 5}); // Tire sur la 2ème case du bateau

  if (!b6.estCoule())
  {
    cout << "Erreur : le bateau est considéré comme non coulé alors qu'il est sencé l'etre" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "Cas limite : Bateau presque coulé" << endl;
  b7.tirAdverse({3, 4}); // Tire sur la 1ère case du bateau
  b7.tirAdverse({3, 5}); // Tire sur la 2ème case du bateau
  if (b7.estCoule())
  {
    cout << "Erreur : le bateau est considéré comme coulé alors qu'il ne l'est pas" << endl;
  }
  else
  {
    cout << "Ok" << endl;
  }

  cout << "------------------------------" << endl;
}
