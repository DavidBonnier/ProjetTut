#include "interfaceTut.h"

Interface::Interface(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	util = new User();

	connect(ui.actionNouvel_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(NouvelUtil()));
	connect(ui.actionSupprimer_un_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(SupprimerUtil()));

	connect(ui.PleinecranCours, SIGNAL(triggered(bool)), this,SLOT(Fullscreen_Cahiers()));
	connect(ui.PleinEcranEval, SIGNAL(triggered(bool)), this,SLOT(Fullscreen_Cahiers()));
	connect(ui.PleinEcranExo, SIGNAL(triggered(bool)), this,SLOT(Fullscreen_Cahiers()));
	connect(ui.GeomPleinEcran, SIGNAL(triggered(bool)), this,SLOT(Fullscreen_Geom()));

	connect(ui.actionQuitter, SIGNAL(triggered(bool)),this,SLOT(close()));
}

Interface::~Interface()
{
}

// Enregistrement
void Interface::NouvelUtil()
{
	util->Enregistrement();
}
 // Suppression
void Interface::SupprimerUtil()
{
	util->RemoveUtil();
}

// Mise en plein écran
void Interface::FullScreen_Cahiers()
{
	ui.Onglets->showFullScreen();
}

void Interface::FullScreen_Geom()
{
	ui.Geom->showFullScreen();
}

// Fermeture du programme
void Interface::closeEvent(QCloseEvent *event)
{
	event->ignore();
	util->StockageVector();
	event->accept();
}
