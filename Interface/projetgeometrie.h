#ifndef PROJETGEOMETRIE_H
#define PROJETGEOMETRIE_H

#include <QtWidgets/QWidget>
#include "ui_projetgeometrie.h"
#include "Geometrie.h"

#include "Crayon.h"
#include "Compas.h"
#include "Regle.h"
#include "Equerre.h"

#include <qcolordialog.h>

#include <QGraphicsScene>
#include <QGraphicsView>
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
    ProjetGeometrie(Geometrie* geometrie);
    ~ProjetGeometrie();
    Geometrie* m_geometrie;
    QGraphicsView * m_viewGraph;

    Ui::ProjetGeometrieClass ui;
    QColor m_couleurTrait;

private:
    Compas * m_compas;
    Regle * m_regle;
    Equerre * m_equerre;
    Crayon * m_crayon;


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
    void crayon(bool check);
    void equerre(bool check);
    void regle(bool check);
    void compas(bool check);
    void point(bool check);
    void zoneTexte(bool check);

    void Epaisseur(int e);
    void grille(bool b);
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
    //Equerre
    void EquerrePositionX(int x);
    void EquerrePositionY(int y);
    void EquerreTransparence(bool b);
    void EquerreOrientation(double orientation);
    void EquerreTracer();
    //Compas
    void CompasPositionX(int x);
    void CompasPositionY(int y);
    void CompasEcartement(int ecartement);
    void CompasOrientation(double orientation);
    void CompasFinTracer();
    void CompasAngleArriver(double angleArriver);
};

#endif // PROJETGEOMETRIE_H
