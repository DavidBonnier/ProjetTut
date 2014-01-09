#ifndef PROJETGEOMETRIE_H
#define PROJETGEOMETRIE_H

#include <QtWidgets/QWidget>
#include "ui_projetgeometrie.h"
#include "Geometrie.h"

class ProjetGeometrie : public QWidget
{
	Q_OBJECT

public:
	ProjetGeometrie(QWidget *parent = 0);
	~ProjetGeometrie();
	Geometrie* geometrie;

private:
	Ui::ProjetGeometrieClass ui;

public slots :
	//Outils
	void PleinEcran();
	void Crayon();
	void Equerre();
	void Regle();
	void Compas();
	void Point();
	void Texte();
	void Epaisseur();
	void Grille();
	//Couleur
	void Noir();
	void Bleu();
	void Vert();
	void Rouge();
	void Jaune();
//Intruments
	//Crayon
	void CrayonPositionX(double x);
	void CrayonPositionY(double y);
	void CrayonTransparence();
	void CrayonOrientation(int orientation);
	//Regle
	void ReglePositionX(double x);
	void ReglePositionY(double y);
	void RegleTransparence();
	void RegleOrientation(int orientation);
	void RegleTracer();
	//Equerre
	void EquerrePositionX(double x);
	void EquerrePositionY(double y);
	void EquerreTransparence();
	void EquerreOrientation(int orientation);
	void EquerreTracer();
	//Compas
	void CompasPositionX(double x);
	void CompasPositionY(double y);
	void CompasTransparence();
	void CompasEcartement(int ecartement);
	void CompasOrientation(int orientation);
};

#endif // PROJETGEOMETRIE_H
