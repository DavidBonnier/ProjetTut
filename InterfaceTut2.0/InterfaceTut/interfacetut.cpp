#include "interfaceTut.h"

Interface::Interface(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	util = new User();
	printer = new QPrinter;

	txtZoneIsClicked = false;

	actionZoneTexte = new QAction(0);

	// Toolbar
	actionZoneTexte->setIcon(QIcon("Resources/Texte.gif"));
	ui.mainToolBar->addAction(actionZoneTexte);
	ui.mainToolBar->setMovable(false);
	
	// Les raccourcis
	ui.actionCopier->setShortcut(tr("Ctrl+C"));
	ui.actionColler->setShortcut(tr("Ctrl+V"));
	ui.actionCouper->setShortcut(tr("Ctrl+X"));
	ui.actionApercu_avant_impression->setShortcut(tr("Alt+P"));
	ui.actionImprimer->setShortcut(tr("Ctrl+P"));
	ui.actionAnnuler->setShortcut(tr("Ctrl+Z"));
	ui.actionRefaire->setShortcut(tr("Ctrl+Y"));
	ui.actionSauvegarder->setShortcut(tr("Ctrl+S"));
	ui.actionSauvegarder_Sous->setShortcut(tr("F12"));
	ui.actionNouvel_Utilisateur->setShortcut(tr("Ctrl+N"));
	ui.actionSupprimer_un_Utilisateur->setShortcut(tr("Ctrl+D"));
	ui.actionChanger_d_Utilisateur->setShortcut(tr("Ctrl+E"));
	ui.actionRaccourcis_Clavier->setShortcut(tr("Ctrl+H"));
	ui.actionPrise_en_main_du_logiciel->setShortcut(tr("F1"));
	ui.actionQuitter->setShortcut(tr("Alt+F4"));

	// connect
	connect(ui.actionNouvel_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(NouvelUtil()));
	connect(ui.actionChanger_d_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(ChangerUtil()));
	connect(ui.actionSupprimer_un_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(SupprimerUtil()));

	connect(actionZoneTexte, SIGNAL(triggered(bool)),this,SLOT(ZoneDeTexte()));

	connect(ui.actionApercu_avant_impression, SIGNAL(triggered(bool)),this,SLOT(ApercuAvtImpr()));
	connect(ui.actionImprimer, SIGNAL(triggered(bool)),this,SLOT(Impression()));

	connect(ui.PleinEcranCours, SIGNAL(pressed()), ui.Onglets,SLOT(Fullscreen_Cahiers()));
	connect(ui.PleinEcranEval, SIGNAL(pressed()), ui.Onglets,SLOT(Fullscreen_Cahiers()));
	connect(ui.PleinEcranExo, SIGNAL(pressed()), ui.Onglets,SLOT(Fullscreen_Cahiers()));
	connect(ui.GeomPleinEcran, SIGNAL(pressed()), ui.Geom,SLOT(Fullscreen_Geom()));

	connect(ui.actionRaccourcis_Clavier, SIGNAL(triggered(bool)),this,SLOT(AffichageRaccourcis()));

	connect(ui.actionQuitter, SIGNAL(triggered(bool)),this,SLOT(close()));
	
}

Interface::~Interface()
{
}

// Changement d'Utilisateur
void Interface::ChangerUtil()
{
	util->Connexion();
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
	ui.centralWidget->showFullScreen();
}

void Interface::FullScreen_Geom()
{
	ui.Geom->resize(ui.centralWidget->width(), ui.centralWidget->height());
}

// Fermeture du programme
void Interface::closeEvent(QCloseEvent *event)
{
	event->ignore();
	util->StockageVector();
	event->accept();
}

// Zone de texte
void Interface::ZoneDeTexte()
{
	txt = new QTextEdit(ui.Onglets->currentWidget());
	txt->show();
}

// Le cliquer - déposer
bool Interface::eventFilter(QObject* obj, QEvent *event)
{
	if(obj == txt )
	{
		if(event->type() == QEvent::MouseButtonPress)
		{
			QMessageBox* suppression_ok = new QMessageBox(QMessageBox::NoIcon, tr("Gestion des utilisateurs "), "La suppression s'est déroulée avec succès. ");
			suppression_ok->setIconPixmap(QPixmap("Resources/supprUti.png"));
			suppression_ok->show();
			if(!txtZoneIsClicked)
				txtZoneIsClicked = true;
			else
				txtZoneIsClicked = false;
			return true;
		}
	}
	else
		return QWidget::eventFilter( obj, event );
}

// le mouse press event (pour le déplacement des zones de texte)
void Interface::mousePressEvent(QMouseEvent* mouse)
{
	if(txtZoneIsClicked)
	{
		QMessageBox* suppression_ok = new QMessageBox(QMessageBox::NoIcon, tr("Gestion des utilisateurs "), "La suppression s'est déroulée avec succès. ");
		suppression_ok->setIconPixmap(QPixmap("Resources/supprUti.png"));
		suppression_ok->show();
		txt->pos().setX(mouse->pos().x());
		txt->pos().setY(mouse->pos().y());
	}
}

// Boite de dialogue raccourcis
void Interface::AffichageRaccourcis()
{
	QMessageBox* shortcuts = new QMessageBox(QMessageBox::NoIcon, "Raccourcis clavier ", "<p><em>Gestion des utilisateurs : </em></p><p></p><p> <strong> - Ctrl + N </strong>: Ajout d'un utilisateur.</p> <p><strong> - Ctrl + D </strong>: Suppression d'un utilisateur.</p><p> <strong> - Ctrl + E </strong>: Changer d'utilisateur. </p><p></p><p> <em> Édition : </em> </p><p> <strong> - Ctrl + C </strong>: Copier. </p><p> <strong> - Ctrl + V </strong>: Coller.</p><p> <strong> - Ctrl + X </strong>: Couper. </p><p> <strong> - Ctrl + Z </strong>: Annuler. </p><p> <strong> - Ctrl + Y </strong>: Refaire. </p><p></p><p> <em> Autres : </p><p></p><p> <strong> - Ctrl + S </strong>: Sauvegarder. </p><p> <strong> - F12 </strong>: Sauvegarder Sous. </p><p> <strong> - Ctrl + P </strong>: Imprimer. </p><p> <strong> - Alt + P </strong>: Aperçu avant impression. </p><p> <strong> - F1 </strong>: Affichage de l'aide. </p><p> <strong> - Ctrl + H </strong>: Affichage de cette boîte de dialogue. </p><p> <strong> - Alt + F4 </strong>: Quitter le programme.");
	shortcuts->setIconPixmap(QPixmap("Resources/raccourcisClavier.png"));
	shortcuts->show();
}

// lancement de la documentation html jointe
void Interface::Aide()
{

}

// aperçu avant impression
void Interface::ApercuAvtImpr()
{
	QPrintPreviewDialog *printDialog = new QPrintPreviewDialog(printer);
    connect(printDialog, SIGNAL(paintRequested(QPrinter *)), this, SLOT(doSomething(QPrinter *)));
	printDialog->setWindowTitle("Aperçu avant impression");
    printDialog->exec();
}

// imprimer
void Interface::Impression()
{
	 QPrintDialog *dialog = new QPrintDialog(printer, this);
     dialog->setWindowTitle(tr("Imprimez votre travail"));
     if (dialog->exec() != QDialog::Accepted)
         return;
	
	QPainter painter;
    painter.begin(printer);
    double xscale = printer->pageRect().width()/double(ui.Onglets->width());
    double yscale = printer->pageRect().height()/double(ui.Onglets->height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer->paperRect().x() + printer->pageRect().width()/2,
                    printer->paperRect().y() + printer->pageRect().height()/2);
    painter.scale(scale, scale);
    painter.translate(-width()/2, -height()/2);
 
    ui.Onglets->render(&painter);
}