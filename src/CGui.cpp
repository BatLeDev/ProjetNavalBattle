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