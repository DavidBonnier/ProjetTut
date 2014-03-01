///////////////////////////////////////////////////////////////////////////
//! \file Crayon.h
//!
//! \brief Déclaration des fonctions pour la gestion des transformations géométriques du crayon.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#ifndef CRAYON_H_
#define CRAYON_H_

#include <QDomDocument>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QTextStream>
#include <QMouseEvent>
#include "math.h"
#include "instrument.h"

class Geometrie;

///////////////////////////////////////////////////////////////////////////
//! \class Crayon
//!
//! \brief Classe servant à effectuer les transformations sur le compas en modifiant son fichier XML.
///////////////////////////////////////////////////////////////////////////
class Crayon : public Instrument
{
public:
    Crayon(Geometrie * geometrie);

    void setTransparence(bool transparence);
    void translation(double positionX , double positionY);
    void setAngle(double angle);

    void dessinerCrayon(QPainter& dessin);

private:
    int m_hauteurPointe;
    int m_largeur;
};

#endif
