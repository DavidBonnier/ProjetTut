///////////////////////////////////////////////////////////////////////////
//! \file Geometrie.h
//!
//! \brief Déclaration des fonctions de tracer en générale (Instrument, Figure)
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRIE_H_
#define GEOMETRIE_H_

#include "Compas.h"
#include "Crayon.h"
#include "Equerre.h"
#include "Regle.h"

#include "arc.h"
#include "ligne.h"
#include "point.h"

#include <QDomDocument>
#include <QFile>
#include <QMessageBox>
#include <QPainter>
#include <QTextStream>
#include <QMouseEvent>
#include <QtSvg/QSvgGenerator>
#include <QtSvg/QSvgRenderer>
#include <QList>
#include <QTextEdit>

#include "figure.h"

class ProjetGeometrie;

///////////////////////////////////////////////////////////////////////////
//! \class Geometrie
//!
//! \brief Classe permettant l'affichage des instruments et des Figures que l'on trace.
//! Elle recoit les signaux pour les appliquer à ceux-ci.
///////////////////////////////////////////////////////////////////////////
class Geometrie : public QWidget
{
	Q_OBJECT
public:
    Geometrie(ProjetGeometrie * projetGeometrie);
    ~Geometrie();

    ProjetGeometrie * m_projetGeometrie;

    Compas* compas;
    Crayon* crayon;
    Equerre* equerre;
    Regle* regle;

    QList <Figure *> tableauFigure;

    bool gererRegle();
    bool gererEquerre();
    bool gererCompas();
    bool gererCrayon();

    bool modifCompas;
    bool modifCrayon;
    bool modifEquerre;
    bool modifRegle;

	//Affichage de la grille
	bool grille, magne_actif;

    int id_txtSelectionne, id_point;
    bool clickTxt, txtSelectionne;
	bool clickPoint;
	
    QTextEdit* txt;
    QVector<QTextEdit *> stockTxt;

    QString generationSVG();
	
    //Gère le dessin des intruments
    void paintEvent (QPaintEvent *event);
	void mousePressEvent(QMouseEvent *clic);
	void mouseMoveEvent(QMouseEvent *move);
    bool eventFilter(QObject * obj, QEvent * e);

	int largeurViewport; 
	int hauteurViewport;

	//variables nécessaires au magnétisme
	int m_txMagnetAng;
	int m_txMagnetDist;

private:
    char ordreInstruments[4]; //Tableau de positions

    void dessinerFigure(QPainter * peintre);
    QRect * m_rectangleViewport;

    int m_nbGraduation;

signals:
	void curseur();
	void pointcree();
};

#endif
