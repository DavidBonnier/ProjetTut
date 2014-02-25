///////////////////////////////////////////////////////////////////////////
//! \file Geometrie.h
//!
//! \brief Définition des fonctions servant à gérer tous les instruments.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRIE_H_
#define GEOMETRIE_H_

#include <QPainter>
#include <QTextStream>
#include <QMouseEvent>
#include <QGraphicsScene>

#include "figure.h"

///////////////////////////////////////////////////////////////////////////
//! \class Geometrie
//!
//! \brief Classe permettant l'affichage des instruments. Elle recoit les signaux pour les appliquer à ceux-ci.
///////////////////////////////////////////////////////////////////////////
class Geometrie : public QGraphicsScene
{
	Q_OBJECT
public:
    Geometrie();
    ~Geometrie();

    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
};

#endif
