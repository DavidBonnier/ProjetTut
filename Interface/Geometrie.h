///////////////////////////////////////////////////////////////////////////
//! \file Geometrie.h
//!
//! \brief Définition des fonctions servant à gérer tous les instruments.
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
//! \brief Classe permettant l'affichage des instruments. Elle recoit les signaux pour les appliquer à ceux-ci.
///////////////////////////////////////////////////////////////////////////
class Geometrie : public QWidget
{
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
	bool grille;

    int id_txtSelectionne;
    bool clickTxt, txtSelectionne;
    QTextEdit* txt;
    QVector<QTextEdit *> stockTxt;

    //Gère le dessin des intruments
    void paintEvent (QPaintEvent *event);
	void mousePressEvent(QMouseEvent *clic);
	void mouseMoveEvent(QMouseEvent *move);
    bool eventFilter(QObject * obj, QEvent * e);

private:
    char ordreInstruments[4]; //4 instruments, une info quel intrument, une quelle position

    void dessinerFigure(QPainter* dessinTrait);
    QString * nomFichier;
    QString * nomFichierTemp;
};

#endif
