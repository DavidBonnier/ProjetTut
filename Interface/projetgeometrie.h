#ifndef PROJETGEOMETRIE_H
#define PROJETGEOMETRIE_H

#include <QtWidgets/QWidget>
#include "ui_projetgeometrie.h"
#include "Geometrie.h"
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
    ProjetGeometrie(Geometrie *geometri);
    ~ProjetGeometrie();
    Geometrie* geometrie;
    Ui::ProjetGeometrieClass ui;

signals:
    void clickSortieFullScreen();
    void clickRegle();
    void clickEquerre();
    void clickCrayon();
    void clickCompas();

public slots :
    //Outils
    void sortieFullScreen();
    void Crayon();
    void Equerre();
    void Regle();
    void Compas();
    void Point();
    void zoneTexte();

    void Epaisseur(bool b);
    void Grille(bool b);
    //Couleur
    void Noir();
    void Bleu();
    void Vert();
    void Rouge();
    void Jaune();
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
};

#endif // PROJETGEOMETRIE_H
