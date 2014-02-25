#include "projetgeometrie.h"

ProjetGeometrie::ProjetGeometrie(Geometrie* geometrie)
{
    ui.setupUi(this);
	m_couleurTrait = Qt::blue;

    m_geometrie = geometrie;
    m_viewGraph = new QGraphicsView(m_geometrie);

    ui.DessinLayout->addWidget(m_viewGraph);
	ui.CheckBoxGrille->setChecked(true);
//Connexions des boutons
	ui.BoutonCrayon->setToolTip("Outil Crayon");
	ui.BoutonCompas->setToolTip("Outil Compas");
	ui.BoutonRegle->setToolTip("Outil Règle");
	ui.BoutonPoint->setToolTip("Outil Point");
	ui.BoutonEquerre->setToolTip("Outil Équerre");
	ui.BoutonPleinEcran->setToolTip("Revenir en écran scindé");
	ui.BoutonCouleur->setToolTip("Afficher la palette de couleurs");

    //Boutons outils
    connect(ui.BoutonPleinEcran, SIGNAL(clicked(bool)), this, SLOT(sortieFullScreen()));

    connect(ui.BoutonCrayon, SIGNAL(clicked(bool)), this, SLOT(Crayon()));
    connect(ui.BoutonEquerre, SIGNAL(clicked(bool)), this, SLOT(Equerre()));
    connect(ui.BoutonRegle, SIGNAL(clicked(bool)), this, SLOT(Regle()));
    connect(ui.BoutonCompas, SIGNAL(clicked(bool)), this, SLOT(Compas()));
    connect(ui.BoutonPoint, SIGNAL(clicked(bool)), this, SLOT(Point()));
    connect(ui.BoutonTexte, SIGNAL(clicked(bool)), this, SLOT(zoneTexte()));
	connect(ui.spinBoxEpaisseur, SIGNAL(valueChanged(int)), this, SLOT(Epaisseur(int)));
    connect(ui.CheckBoxGrille, SIGNAL(clicked(bool)), this, SLOT(Grille(bool)));
	connect(ui.BoutonCouleur, SIGNAL(clicked(bool)), this, SLOT(Couleur()));
//Instruments DockWidget
    //Crayon
    connect(ui.SpinBoxCrayonPositionX, SIGNAL(valueChanged(int)), this, SLOT(CrayonPositionX(int)));
    connect(ui.SpinBoxCrayonPositionY, SIGNAL(valueChanged(int)), this, SLOT(CrayonPositionY(int)));
    connect(ui.CheckBoxCrayonTransparence, SIGNAL(clicked(bool)), this, SLOT(CrayonTransparence(bool)));
    connect(ui.SpinBoxCrayonOrientation, SIGNAL(valueChanged(double)), this, SLOT(CrayonOrientation(double)));
    //Regle
    connect(ui.SpinBoxReglePositionX, SIGNAL(valueChanged(int)), this, SLOT(ReglePositionX(int)));
    connect(ui.SpinBoxReglePositionY, SIGNAL(valueChanged(int)), this, SLOT(ReglePositionY(int)));
    connect(ui.CheckBoxRegleTransparence, SIGNAL(clicked(bool)), this, SLOT(RegleTransparence(bool)));
    connect(ui.SpinBoxRegleOrientation, SIGNAL(valueChanged(double)), this, SLOT(RegleOrientation(double)));
    connect(ui.BoutonRegleTracerOK, SIGNAL(clicked(bool)), this, SLOT(RegleTracer()));
    //Equerre
    connect(ui.SpinBoxEquerrePositionX, SIGNAL(valueChanged(int)), this, SLOT(EquerrePositionX(int)));
    connect(ui.SpinBoxEquerrePositionY, SIGNAL(valueChanged(int)), this, SLOT(EquerrePositionY(int)));
    connect(ui.CheckBoxEquerreTransparence, SIGNAL(clicked(bool)), this, SLOT(EquerreTransparence(bool)));
    connect(ui.SpinBoxEquerreOrientation, SIGNAL(valueChanged(double)), this, SLOT(EquerreOrientation(double)));
    connect(ui.BoutonEquerreTracerOK, SIGNAL(clicked(bool)), this, SLOT(EquerreTracer()));
    //Compas
    connect(ui.SpinBoxCompasPositionX, SIGNAL(valueChanged(int)), this, SLOT(CompasPositionX(int)));
    connect(ui.SpinBoxCompasPositionY, SIGNAL(valueChanged(int)), this, SLOT(CompasPositionY(int)));
    connect(ui.SpinBoxCompasEcartement, SIGNAL(valueChanged(int)), this, SLOT(CompasEcartement(int)));
    connect(ui.SpinBoxCompasOrientation, SIGNAL(valueChanged(double)), this, SLOT(CompasOrientation(double)));

    connect(ui.BoutonCompasTracerOK, SIGNAL(clicked(bool)), this, SLOT(CompasFinTracer()));
    connect(ui.SpinBoxCompasTracerArc, SIGNAL(valueChanged(double)), this, SLOT(CompasAngleArriver(double)));
}

ProjetGeometrie::~ProjetGeometrie()
{
}

//****************************************SLOTS****************************************//
//Outils
void ProjetGeometrie::sortieFullScreen()
{
    emit clickSortieFullScreen();
	update();
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

void ProjetGeometrie::Grille(bool b)
{

}

void ProjetGeometrie::restorePoint()
{
	QApplication::restoreOverrideCursor();
	ui.BoutonPoint->setChecked(false);
}

void ProjetGeometrie::Epaisseur(int e)
{
	m_geometrie->update();
}


void ProjetGeometrie::restoreCursor()
{
	QApplication::restoreOverrideCursor();
	ui.BoutonTexte->setChecked(false);
}

void ProjetGeometrie::zoneTexte()
{

}

//Couleurs
void ProjetGeometrie::Couleur()
{
    m_couleurTrait = QColorDialog::getColor(Qt::white, this);
	m_geometrie->update();
}

//Instruments
//Crayon
void ProjetGeometrie::CrayonPositionX(int x)
{

}

void ProjetGeometrie::CrayonPositionY(int y)
{

}

void ProjetGeometrie::CrayonTransparence(bool b)
{

}

void ProjetGeometrie::CrayonOrientation(double orientation)
{

}
//Règle
void ProjetGeometrie::ReglePositionX(int x)
{

}

void ProjetGeometrie::ReglePositionY(int y)
{

}

void ProjetGeometrie::RegleTransparence(bool b)
{

}

void ProjetGeometrie::RegleOrientation(double orientation)
{

}

void ProjetGeometrie::RegleTracer()
{

}
//Equerre
void ProjetGeometrie::EquerrePositionX(int x)
{

}

void ProjetGeometrie::EquerrePositionY(int y)
{

}

void ProjetGeometrie::EquerreTransparence(bool b)
{

}

void ProjetGeometrie::EquerreOrientation(double orientation)
{

}

void ProjetGeometrie::EquerreTracer()
{

}
//Compas
void ProjetGeometrie::CompasPositionX(int x)
{

}

void ProjetGeometrie::CompasPositionY(int y)
{

}

void ProjetGeometrie::CompasEcartement(int ecartement)
{

}

void ProjetGeometrie::CompasOrientation(double orientation)
{

}

void ProjetGeometrie::CompasFinTracer()
{
    ui.SpinBoxCompasTracerArc->setValue(0);
}

void ProjetGeometrie::CompasAngleArriver(double angleArriver)
{

}
