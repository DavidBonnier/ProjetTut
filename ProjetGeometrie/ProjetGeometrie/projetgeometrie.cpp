#include "projetgeometrie.h"

ProjetGeometrie::ProjetGeometrie(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
//Connection des boutons
	//Boutons outils
	connect(ui.BoutonPleinEcran, SIGNAL(triggered(bool)), this, SLOT(PleinEcran()));
	connect(ui.BoutonCrayon, SIGNAL(triggered(bool)), this, SLOT(Crayon()));
	connect(ui.BoutonEquerre, SIGNAL(triggered(bool)), this, SLOT(Equerre()));
	connect(ui.BoutonRegle, SIGNAL(triggered(bool)), this, SLOT(Regle()));
	connect(ui.BoutonCompas, SIGNAL(triggered(bool)), this, SLOT(Compas()));
	connect(ui.BoutonPoint, SIGNAL(triggered(bool)), this, SLOT(Point()));
	connect(ui.BoutonTexte, SIGNAL(triggered(bool)), this, SLOT(Texte()));
	connect(ui.BoutonEpaisseur, SIGNAL(triggered(bool)), this, SLOT(Epaisseur()));
	connect(ui.CheckBoxGrille, SIGNAL(clicked(bool)), this, SLOT(Grille()));
	//Boutons couleurs
	connect(ui.BoutonNoir, SIGNAL(triggered(bool)), this, SLOT(Noir()));
	connect(ui.BoutonBleu, SIGNAL(triggered(bool)), this, SLOT(Bleu()));
	connect(ui.BoutonVert, SIGNAL(triggered(bool)), this, SLOT(Vert()));
	connect(ui.BoutonJaune, SIGNAL(triggered(bool)), this, SLOT(Jaune()));
	connect(ui.BoutonRouge, SIGNAL(triggered(bool)), this, SLOT(Rouge()));
//Instruments
	//Crayon
	connect(ui.SpinBoxCrayonPositionX, SIGNAL(valueChanged(double)), this, SLOT(CrayonPositionX(double)));
	connect(ui.SpinBoxCrayonPositionY, SIGNAL(valueChanged(double)), this, SLOT(CrayonPositionY(double)));
	connect(ui.CheckBoxCrayonTransparence, SIGNAL(clicked(bool)), this, SLOT(CrayonTransparence()));
	connect(ui.SpinBoxCrayonOrientation, SIGNAL(valueChanged(int)), this, SLOT(CrayonOrientation(int)));
	//Regle
	connect(ui.SpinBoxReglePositionX, SIGNAL(valueChanged(double)), this, SLOT(ReglePositionX(double)));
	connect(ui.SpinBoxReglePositionY, SIGNAL(valueChanged(double)), this, SLOT(ReglePositionY(double)));
	connect(ui.CheckBoxRegleTransparence, SIGNAL(clicked(bool)), this, SLOT(RegleTransparence()));
	connect(ui.SpinBoxRegleOrientation, SIGNAL(valueChanged(int)), this, SLOT(RegleOrientation(int)));
	connect(ui.BoutonRegleTracerOK, SIGNAL(clicked(bool)), this, SLOT(RegleTracer()));
	//Equerre
	connect(ui.SpinBoxEquerrePositionX, SIGNAL(valueChanged(double)), this, SLOT(EquerrePositionX(double)));
	connect(ui.SpinBoxEquerrePositionY, SIGNAL(valueChanged(double)), this, SLOT(EquerrePositionY(double)));
	connect(ui.CheckBoxEquerreTransparence, SIGNAL(clicked(bool)), this, SLOT(EquerreTransparence()));
	connect(ui.SpinBoxEquerreOrientation, SIGNAL(valueChanged(int)), this, SLOT(EquerreOrientation(int)));
	connect(ui.BoutonEquerreTracerOK, SIGNAL(clicked(bool)), this, SLOT(EquerreTracer()));
	//Compas
	connect(ui.SpinBoxCompasPositionX, SIGNAL(valueChanged(double)), this, SLOT(CompasPositionX(double)));
	connect(ui.SpinBoxCompasPositionY, SIGNAL(valueChanged(double)), this, SLOT(CompasPositionY(double)));
	connect(ui.CheckBoxCompasTransparence, SIGNAL(clicked(bool)), this, SLOT(CompasTransparence()));
	connect(ui.SpinBoxCompasEcartement, SIGNAL(valueChanged(int)), this, SLOT(CompasEcartement(int)));
	connect(ui.SpinBoxCompasOrientation, SIGNAL(valueChanged(int)), this, SLOT(CompasOrientation(int)));
}

ProjetGeometrie::~ProjetGeometrie()
{

}


//****************************************SLOTS*******************************
//Outils
void ProjetGeometrie::PleinEcran()
{

}

void ProjetGeometrie::Crayon()
{

}

void ProjetGeometrie::Equerre()
{

}

void ProjetGeometrie::Regle()
{

}

void ProjetGeometrie::Compas()
{

}

void ProjetGeometrie::Point()
{

}

void ProjetGeometrie::Texte()
{

}

void ProjetGeometrie::Epaisseur()
{

}

void ProjetGeometrie::Grille()
{

}

//Couleurs
void ProjetGeometrie::Noir()
{
	int noir[3] = {0,0,0};
	geometrie->figures->setColor(noir);
}

void ProjetGeometrie::Bleu()
{
	int bleu[3] = {0,0,255};
	geometrie->figures->setColor(bleu);
}

void ProjetGeometrie::Vert()
{
	int vert[3] = {0,255,0};
	geometrie->figures->setColor(vert);
}

void ProjetGeometrie::Jaune()
{
	int jaune[3] = {0,255,255};
	geometrie->figures->setColor(jaune);
}

void ProjetGeometrie::Rouge()
{
	int rouge[3] = {255,0,0};
	geometrie->figures->setColor(rouge);
}

//Instruments
//Crayon
void ProjetGeometrie::CrayonPositionX(double x)
{
	geometrie->instruments->translation(x, 0);
}

void ProjetGeometrie::CrayonPositionY(double y)
{
	geometrie->instruments->translation(0, y);
}

void ProjetGeometrie::CrayonTransparence()
{
	geometrie->instruments->transparence = true;
}

void ProjetGeometrie::CrayonOrientation(int orientation)
{
	geometrie->instruments->rotation(orientation);
}
//Règle
void ProjetGeometrie::ReglePositionX(double x)
{

}

void ProjetGeometrie::ReglePositionY(double y)
{

}

void ProjetGeometrie::RegleTransparence()
{

}

void ProjetGeometrie::RegleOrientation(int orientation)
{

}

void ProjetGeometrie::RegleTracer()
{

}
//Equerre
void ProjetGeometrie::EquerrePositionX(double x)
{

}

void ProjetGeometrie::EquerrePositionY(double y)
{

}

void ProjetGeometrie::EquerreTransparence()
{

}

void ProjetGeometrie::EquerreOrientation(int orientation)
{

}

void ProjetGeometrie::EquerreTracer()
{

}
//Compas
void ProjetGeometrie::CompasPositionX(double x)
{

}

void ProjetGeometrie::CompasPositionY(double y)
{

}

void ProjetGeometrie::CompasTransparence()
{

}

void ProjetGeometrie::CompasEcartement(int ecartement)
{

}

void ProjetGeometrie::CompasOrientation(int orientation)
{

}