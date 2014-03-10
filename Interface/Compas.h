///////////////////////////////////////////////////////////////////////////
//! \file Compas.h
//!
//! \brief Déclaration des fonctions pour la gestion des transformations géométriques du compas.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#ifndef COMPAS_H_
#define COMPAS_H_

#include <QDomDocument>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QTextStream>
#include <QMouseEvent>
#include "instrument.h"

class Geometrie;

///////////////////////////////////////////////////////////////////////////
//! \class Compas
//!
//! \brief Classe servant à effectuer les transformations sur le compas en modifiant son fichier XML.
///////////////////////////////////////////////////////////////////////////
class Compas : public Instrument
{
public:
    Compas(Geometrie * geometrie);
    ~Compas();

	inline int getEcart(){return m_ecartement;}

    double angleEcartement(double ecart, double longueurBranche);
    int hauteurCompas(double ecart, int longueurBranche);

    void tracer(double angleArriver);
    void finTracer();

    void setEcartement(double ecartement);

    void setTransparence(bool transparence);
    void translation(double positionX , double positionY);
    void setAngle(double angle);

    void dessinerCompas(QPainter& dessin);
	void sourisEcart(QMouseEvent *posSouris);
	void MagnetiserCompas (QList <Figure *> tableauFigure);

private:
    int m_hauteurPointe;
    int m_hauteurBase;
    int m_ecartement;

};

#endif
