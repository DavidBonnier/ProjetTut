#ifndef PROJETGEOMETRIE_H
#define PROJETGEOMETRIE_H

#include <QtWidgets/QWidget>
#include "ui_projetgeometrie.h"

class ProjetGeometrie : public QWidget
{
	Q_OBJECT

public:
	ProjetGeometrie(QWidget *parent = 0);
	~ProjetGeometrie(); //bonjour

private:
	Ui::ProjetGeometrieClass ui;
};

#endif // PROJETGEOMETRIE_H
