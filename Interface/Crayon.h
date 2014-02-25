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

class ProjetGeometrie;

///////////////////////////////////////////////////////////////////////////
//! \class Crayon
//!
//! \brief Classe servant à effectuer les transformations sur le compas en modifiant son fichier XML.
///////////////////////////////////////////////////////////////////////////
class Crayon : public Instrument
{
public:
    Crayon(ProjetGeometrie * projetGeometrie);

    void setTransparence(bool transparence);
    void translation(double positionX , double positionY);
    void setAngle(double angle);

    void paint(QPainter * dessin, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

private:
    int m_hauteurPointe;
    int m_epaisseur;
};

#endif
