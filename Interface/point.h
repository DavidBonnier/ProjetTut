///////////////////////////////////////////////////////////////////////////
//! \file point.h
//!
//! \brief Classe servant à la création des points.
//!
//! Hérite de Figure pour le tracer et donc le stockage en svg.
//! Deux accesseurs pour accéder aux deux lignes qui forment le point.
//!
//! \date 21/02/2014
//! \version 2.0
///////////////////////////////////////////////////////////////////////////

#ifndef POINT_H
#define POINT_H

#include "figure.h"
#include <QLineF>

///////////////////////////////////////////////////////////////////////////
//! \class Point
//!
//! \brief Classe qui permet le tracer d'un point.
///////////////////////////////////////////////////////////////////////////
class Point : public Figure
{
public:
    Point(QPoint pointBase, int largeurPoint = 10);
    Point(QLineF ligneHorizontal, QLineF ligneVertical);

    inline QLineF getHorizontalLine(){return m_ligneHorizontal;}
    inline QLineF getVerticalLine(){return m_ligneVertical;}
    void setLargeurPoint(int largeurPoint);
    void setPointBase(QPoint pointBase);

private:
    int m_largeurPoint;
    QPoint m_pointBase;
    QLineF m_ligneHorizontal;
    QLineF m_ligneVertical;

    void MAJLignes();
};

#endif // POINT_H
