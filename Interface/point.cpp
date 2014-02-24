///////////////////////////////////////////////////////////////////////////
//! \file point.cpp
//!
//! \brief Création des points.
//!
//! Le constructeur de Point est en fait constitué de deux lignes qui formeront une forme de croix à la position du clic.
//! Nous avons muni cette classe d'accesseurs pour pouvoir dessiner et accéder plus facilement aux données de cette classe.
//!
//! \date 21/02/2014
//! \version 1.0
///////////////////////////////////////////////////////////////////////////

#include "point.h"

Point::Point(QPoint pointBase, int largeurPoint)
{
    m_largeurPoint = largeurPoint;
    m_pointBase = pointBase;

    MAJLigne();
}

Point::Point(QLineF ligneHorizontal, QLineF ligneVertical)
{
    m_ligneHorizontal = ligneHorizontal;
    m_ligneVertical = ligneVertical;
}

Point::~Point()
{

}

void Point::setPointBase(QPoint pointBase)
{
    m_pointBase = pointBase;
    MAJLigne();
}

void Point::setLargeurPoint(int largeurPoint)
{
    m_largeurPoint = largeurPoint;
    MAJLigne();
}

void Point::MAJLigne()
{
    m_ligneHorizontal = QLineF(m_pointBase.x() - m_largeurPoint, m_pointBase.y(), m_pointBase.x() + m_largeurPoint, m_pointBase.y());
    m_ligneVertical = QLineF(m_pointBase.x(), m_pointBase.y() - m_largeurPoint, m_pointBase.x(), m_pointBase.y() + m_largeurPoint);
}
