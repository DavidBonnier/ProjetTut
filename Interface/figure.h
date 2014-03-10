///////////////////////////////////////////////////////////////////////////
//! \file figure.h
//!
//! \brief Déclaration de la classe Figure.
//!
//! Classe dérivant de QWidget.
//! Elle est utilisée pour pouvoir héritée tout les figures de la même classe (Arc, Ligne, Point).
//! Une seule donnée pour savoir si le tracer la définition des données est fini.
//!
//! \date 01/02/2014
//! \version 4.2
///////////////////////////////////////////////////////////////////////////
///
#ifndef FIGURE_H
#define FIGURE_H

#include <QWidget>

///////////////////////////////////////////////////////////////////////////
//! \class Figure
//!
//! \brief Classe utiliser que pour stocker toutes les figures dans Geometrie.
///////////////////////////////////////////////////////////////////////////
class Figure : public QWidget
{
    Q_OBJECT
public:
    Figure(QWidget *parent = 0);

    inline void setFin(bool finTracer){m_finTracer = finTracer;}
    inline bool getFin(){return m_finTracer;}

private:
    bool m_finTracer;
};

#endif // FIGURE_H
