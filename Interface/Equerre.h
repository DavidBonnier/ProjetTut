///////////////////////////////////////////////////////////////////////////
//! \file Equerre.h
//!
//! \brief Déclaration des fonctions pour la gestion des transformations géométriques de l'équerre.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#ifndef EQUERRE_H_
#define EQUERRE_H_

#include <QDomDocument>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QTextStream>
#include <QMouseEvent>
#include <QString>
#include <QPointF>

#include "math.h"
#include "Regle.h"

class Geometrie;

///////////////////////////////////////////////////////////////////////////
//! \class Equerre
//!
//! \brief Classe servant à effectuer les transformations sur l'équerre en modifiant son fichier XML.
///////////////////////////////////////////////////////////////////////////
class Equerre : public Regle
{
public:
    Equerre(Geometrie * geometrie);
    ~Equerre();

    void setTransparence(bool transparence);
    void translation(double positionX , double positionY);
    void setAngle(double angle);

    QPointF Thales(double longueur, double largeur, double transp, int x, int y);

    void dessinerEquerre(QPainter& dessin);
	void MagnetiserEquerre (QList <Figure *> tableauFigure);
};

#endif
