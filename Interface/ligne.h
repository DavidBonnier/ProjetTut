///////////////////////////////////////////////////////////////////////////
//! \file ligne.h
//!
//! \brief Classe servant à la création de ligne et héritant de Figure pour pouvoir la tracer.
//!
//! Classe comme QLineF qui hérite de Figure pour les tracés.
//!
//! \date 01/02/2014
//! \version 4.2
///////////////////////////////////////////////////////////////////////////

#ifndef LIGNE_H
#define LIGNE_H

#include <QLineF>
#include "figure.h"

///////////////////////////////////////////////////////////////////////////
//! \class Ligne
//!
//! \brief Classe qui permet le tracer d'une Ligne.
///////////////////////////////////////////////////////////////////////////
class Ligne : public Figure
{
public:
    Ligne(QLineF ligne);
    Ligne(QPointF numero1, QPointF numero2);
    Ligne(double x1, double y1, double x2, double y2);

    inline QLineF getQLine() {return m_ligne;}
    inline void setQLine(QLineF ligne) {m_ligne = ligne;}

    void setPoint1 (QPointF numero1);
    void setPoint2 (QPointF numero2);
    void setAngle (double angle);

private:
    QLineF m_ligne;
};

#endif // LIGNE_H
