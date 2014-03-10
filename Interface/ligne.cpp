///////////////////////////////////////////////////////////////////////////
//! \file ligne.cpp
//!
//! \brief Création des lignes.
//!
//! Plusieurs constructeurs pour instialiser la QLineF.
//!
//! \date 01/02/2014
//! \version 1.0
///////////////////////////////////////////////////////////////////////////
#include "ligne.h"

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param ligne QLineF qui met à jour la donnée membre.
//!
//! \brief Constructeur de Ligne.
//!
//! \date 01/02/2014
///////////////////////////////////////////////////////////////////////
Ligne::Ligne(QLineF ligne)
{
    m_ligne = ligne;
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param numero1 QPointF qui est le premier point de la ligne.
//! \param numero2 QPointF qui est le second point de la ligne.
//!
//! \brief Constructeur de Ligne qui utilise le constructeur de QLineF.
//!
//! \date 01/02/2014
///////////////////////////////////////////////////////////////////////
Ligne::Ligne(QPointF numero1, QPointF numero2)
{
    m_ligne = QLineF(numero1, numero2);
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param x1 Double qui est le x du premier point de la ligne.
//! \param y1 Double qui est le y du premier point de la ligne.
//! \param x2 Double qui est le x du second point de la ligne.
//! \param y2 Double qui est le y du second point de la ligne.
//!
//! \brief Constructeur de Ligne qui utilise le constructeur de QLineF.
//!
//! \date 01/02/2014
///////////////////////////////////////////////////////////////////////
Ligne::Ligne(double x1, double y1, double x2, double y2)
{
    m_ligne = QLineF (x1, y1, x2, y2);
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param numero1 QPointF qui est le premier point de la ligne.
//!
//! \brief Appelle de la fonction de changement du premier point de QlineF.
//!
//! \date 01/02/2014
///////////////////////////////////////////////////////////////////////
void Ligne::setPoint1 (QPointF numero1)
{
    m_ligne.setP1(numero1);
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param numero2 QPointF qui est le second point de la ligne.
//!
//! \brief Appelle de la fonction de changement du second point de QlineF.
//!
//! \date 01/02/2014
///////////////////////////////////////////////////////////////////////
void Ligne::setPoint2 (QPointF numero2)
{
    m_ligne.setP2(numero2);
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param angle Double qui est l'angle de la ligne.
//!
//! \brief Appelle de la fonction de changement d'angle de QLineF.
//!
//! \date 01/02/2014
///////////////////////////////////////////////////////////////////////
void Ligne::setAngle (double angle)
{
    m_ligne.setAngle(angle);
}
