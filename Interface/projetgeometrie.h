///////////////////////////////////////////////////////////////////////////
//! \file projetgeometrie.h
//!
//! \brief Déclaration des variables, fonctions pour la gestion de la géométrie en plein écran.
//!
//! Toutes les fonctions relatives à la géométrie (les instruments, les tracés, les spinbox...) sont déclarées ici.
//!
//! \date 01/02/2014
//! \version 4.2
///////////////////////////////////////////////////////////////////////////

#ifndef PROJETGEOMETRIE_H
#define PROJETGEOMETRIE_H

#include <QtWidgets/QWidget>
#include "ui_projetgeometrie.h"
#include "Geometrie.h"
#include <qcolordialog.h>
///////////////////////////////////////////////////////////////////////////
//! \class ProjetGeometrie
//!
//! \brief Classe principale gère les connections entre le ui
//!  et le programme
///////////////////////////////////////////////////////////////////////////
class ProjetGeometrie : public QWidget
{
    Q_OBJECT

public:
    ProjetGeometrie();
    ~ProjetGeometrie();
    Geometrie* m_geometrie;
    Ui::ProjetGeometrieClass ui;
    QColor m_couleurTrait;

signals:
    void clickSortieFullScreen();
    void clickRegle();
    void clickEquerre();
    void clickCrayon();
    void clickCompas();

public slots :
    //Outils
	void restoreCursor();
	void restorePoint();
    void sortieFullScreen();
    void Crayon();
    void Equerre();
    void Regle();
    void Compas();
    void Point();
    void zoneTexte();

    void Epaisseur();
    void Grille(bool b);
	void Magne(bool b);
    void Couleur();
//Intruments
    //Crayon
    void CrayonPositionX(int x);
    void CrayonPositionY(int y);
    void CrayonTransparence(bool b);
    void CrayonOrientation(double orientation);
    //Regle
    void ReglePositionX(int x);
    void ReglePositionY(int y);
    void RegleTransparence(bool b);
    void RegleOrientation(double orientation);
    void RegleTracer();
    void RegleFinTracer();
    //Equerre
    void EquerrePositionX(int x);
    void EquerrePositionY(int y);
    void EquerreTransparence(bool b);
    void EquerreOrientation(double orientation);
    void EquerreTracer();
    void EquerreFinTracer();
    //Compas
    void CompasPositionX(int x);
    void CompasPositionY(int y);
    void CompasEcartement(int ecartement);
    void CompasOrientation(double orientation);
    void CompasFinTracer();
    void CompasAngleArriver(double angleArriver);
};

#endif // PROJETGEOMETRIE_H
