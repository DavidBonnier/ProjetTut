///////////////////////////////////////////////////////////////////////////
//! \file point.h
//!
//! \brief Classe servant à la création des points.s
//!
//! Hérite de Figure pour le stockage en svg. deux accesseurs pour accéder aux deux lignes qui forment le point.
//!
//! \date 21/02/2014
//! \version 1.0
///////////////////////////////////////////////////////////////////////////

#ifndef POINT_H
#define POINT_H

#include "figure.h"
#include <QLineF>

class Point : public Figure
{
public:
    Point(QPoint pointBase, int largeurPoint = 10);
    Point(QLineF ligneHorizontal, QLineF ligneVertical);
    ~Point();

    inline QLineF getHorizontalLine(){return m_ligneHorizontal;}
    inline QLineF getVerticalLine(){return m_ligneVertical;}

    void setLargeurPoint(int largeurPoint);
    void setPointBase(QPoint pointBase);

private:
    int m_largeurPoint;
    QPoint m_pointBase;
    QLineF m_ligneHorizontal;
    QLineF m_ligneVertical;

    void MAJLigne();
};

#endif // POINT_H
