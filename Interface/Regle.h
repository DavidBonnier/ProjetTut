///////////////////////////////////////////////////////////////////////////
//! \file Regle.h
//!
//! \brief Déclaration des fonctions pour la gestion des transformations géométriques de la règle.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#ifndef REGLE_H_
#define REGLE_H_

#include <QDomDocument>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QTextStream>
#include <QMouseEvent>
#include "math.h"

#include "instrument.h"
#include "ligne.h"

class Geometrie;

///////////////////////////////////////////////////////////////////////////
//! \class Regle
//!
//! \brief Classe servant à effectuer les transformations sur la règle en modifiant son fichier XML.
///////////////////////////////////////////////////////////////////////////
class Regle : public Instrument
{
public:
    Regle();
    Regle(Geometrie * geometrie);
    ~Regle();

    void tracer(double graduation1 , double graduation2);
    void setGraduation(int graduation);

    void setTransparence(bool transparence);
    void translation(double positionX , double positionY);
    void setAngle(double angle);

    void dessinerRegle(QPainter& dessin);
    void finTracer();
	void MagnetiserRegle (QList <Figure *> tableauFigure);

protected:
    int m_graduation;
    void InitialisationRegle();
};

#endif
