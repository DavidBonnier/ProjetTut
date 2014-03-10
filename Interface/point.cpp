///////////////////////////////////////////////////////////////////////////
//! \file point.cpp
//!
//! \brief Création des points.
//!
//! Plusieurs constructeurs pour instialiser les 2 lignes en croix.
//!
//! \date 21/02/2014
//! \version 1.0
///////////////////////////////////////////////////////////////////////////

#include "point.h"

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param pointBase QPoint qui est le point centrale de la croix.
//! \param largeurPoint Entier pour la taille du point en pixel de chaque côté.
//!
//! \brief Constructeur de Point paramètre par défault de 10 pour la largeur.
//!
//! Apelle de la fonction MAJLignes pour inititialiser les 2 lignes avec les paramètres.
//!
//! \date 23/02/2014
///////////////////////////////////////////////////////////////////////
Point::Point(QPoint pointBase, int largeurPoint)
{
    m_largeurPoint = largeurPoint;
    m_pointBase = pointBase;

    MAJLignes();
}

///////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//!
//! \param ligneHorizontal Premier paramètre diagonale qui penche vers la droite.
//! \param ligneVertical Second paramètre diagonale qui penche vers la gauche.
//!
//! \brief Constructeur de Point.
//!
//! Initialisation des 2 données membres qui sont des QlineF.
//!
//! \date 21/02/2014
///////////////////////////////////////////////////////////////////////
Point::Point(QLineF ligneHorizontal, QLineF ligneVertical)
{
    m_ligneHorizontal = ligneHorizontal;
    m_ligneVertical = ligneVertical;
}

///////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//!
//! \brief Destructeur de Point.
//!
//! \date 21/02/2014
///////////////////////////////////////////////////////////////////////
Point::~Point()
{
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param pointBase QPoint qui est le point centrale de la croix.
//!
//! \brief Mise a jour du point de base pour les tracés.
//!
//! Apelle de la fonction MAJLignes pour mettre à jour les 2 lignes avec les nouveaux paramètres.
//!
//! \date 23/02/2014
///////////////////////////////////////////////////////////////////////
void Point::setPointBase(QPoint pointBase)
{
    m_pointBase = pointBase;
    MAJLignes();
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param largeurPoint Entier qui est la moitier de la largeur du point.
//!
//! \brief Mise a jour de la largeur des tracés.
//!
//! Apelle de la fonction MAJLignes pour mettre à jour les 2 lignes avec les nouveaux paramètres.
//!
//! \date 23/02/2014
///////////////////////////////////////////////////////////////////////
void Point::setLargeurPoint(int largeurPoint)
{
    m_largeurPoint = largeurPoint;
    MAJLignes();
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \brief Fonction privée pour mettre a jour les lignes avec les données membres.
//!
//! Fonction qui met a jour les 2 diagonales avec les paramètes (m_pointBase et m_largeurPoint).
//!
//! \date 23/02/2014
///////////////////////////////////////////////////////////////////////
void Point::MAJLignes()
{
    m_ligneHorizontal = QLineF(m_pointBase.x() - m_largeurPoint, m_pointBase.y(), m_pointBase.x() + m_largeurPoint, m_pointBase.y());
    m_ligneVertical = QLineF(m_pointBase.x(), m_pointBase.y() - m_largeurPoint, m_pointBase.x(), m_pointBase.y() + m_largeurPoint);
}
