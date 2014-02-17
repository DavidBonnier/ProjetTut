/////////////////////////////////////////////////////////////////////////// 
//! \file interface.cpp
//! 
//! \brief Mise en place de toutes les fonctionnalités relatives à l'Interface. Connect/signals et slots. 
//! 
//! On a crée dans le .h une variable de type User qui va nous permettre d'accéder aux fonctions de cette classe. On cr‚e donc les slots qui correspondent.
//! Pour les autres fonctionnalités, l'impression et l'aperçu avant impression par exemple,  on met simplement en place les fonctions dans ce fichier.
//! \date 01/02/2014
//! \version 2.3
/////////////////////////////////////////////////////////////////////////// 

#include "interface.h"

Interface::Interface(QMainWindow *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setContextMenuPolicy(Qt::NoContextMenu);

    util = new User();
    geom = new Geometrie();
    projetGeom = new ProjetGeometrie(geom);
    ui.geomEcranScind->addWidget(projetGeom);

    projetGeom->ui.widget->hide();
    projetGeom->ui.ScrollAreaOptionsOutils->hide();

	printer = new QPrinter;
	container = new QWidget();
	layoutCours = new QVBoxLayout();	
	layoutEval = new QVBoxLayout();	
	layoutExo = new QVBoxLayout();	
	ui.scrollAreaCours->setWidget(container);
	ui.scrollAreaCours->setLayout(layoutCours);
	ui.scrollAreaExo->setWidget(container);
	ui.scrollAreaExo->setLayout(layoutExo);
	ui.scrollAreaEval->setWidget(container);
	ui.scrollAreaEval->setLayout(layoutEval);

	txtCours = new QTextEdit(ui.scrollAreaCours);
	txtExo = new QTextEdit(ui.scrollAreaExo);
	txtEval = new QTextEdit(ui.scrollAreaEval);
	ui.scrollAreaExo->setWidget(txtExo);
	ui.scrollAreaCours->setWidget(txtCours);
	ui.scrollAreaEval->setWidget(txtEval);
	layoutCours->addWidget(txtCours);
	layoutExo->addWidget(txtExo);
	layoutEval->addWidget(txtEval);

	widgetIsFullscreen= false;
	fontSize = 18;

	//Toolbar écran scindé
	actionTailleTexte = new QAction(0);
	actionCouleurTexte = new QAction(0);
	actionRegle = new QAction(0);
	actionEquerre = new QAction(0);
	actionCrayon = new QAction(0);
	actionTailleTexte->setToolTip("Outil Taille de police");
	actionCouleurTexte->setToolTip("Outil Couleur de police");
	actionRegle->setToolTip("Outil Règle");
	actionCrayon->setToolTip("Outil Crayon");
	actionEquerre->setToolTip("Outil Équerre");

    actionTailleTexte->setIcon(QIcon("Resources/fontSize.png"));
	actionCouleurTexte->setIcon(QIcon("Resources/fontColor.png"));
	actionRegle->setIcon(QIcon("Resources/regle.gif"));
	actionCrayon->setIcon(QIcon("Resources/crayon.gif"));
	actionEquerre->setIcon(QIcon("Resources/equerre.gif"));

	actionEquerre->setCheckable(false);
	actionRegle->setCheckable(false);
	actionCrayon->setCheckable(false);
	actionTailleTexte->setCheckable(false);
	actionCouleurTexte->setCheckable(false);

	ui.mainToolBar->addAction(actionTailleTexte);	
	ui.mainToolBar->addAction(actionCouleurTexte);
	ui.mainToolBar->addSeparator();
	ui.mainToolBar->addAction(actionCrayon);
	ui.mainToolBar->addAction(actionRegle);
	ui.mainToolBar->addAction(actionEquerre);
	ui.mainToolBar->setMovable(false);
	//-----------------------------------

	// Les raccourcis
	ui.actionCopier->setShortcut(tr("Ctrl+C"));
	ui.actionColler->setShortcut(tr("Ctrl+V"));
	ui.actionCouper->setShortcut(tr("Ctrl+X"));
	ui.actionApercu_avant_impression->setShortcut(tr("Alt+P"));
	ui.actionImprimer->setShortcut(tr("Ctrl+P"));
	ui.actionAnnuler->setShortcut(tr("Ctrl+Z"));
	ui.actionRefaire->setShortcut(tr("Ctrl+Y"));
	ui.actionOuvrir->setShortcut(tr("Ctrl+O"));
	ui.actionSauvegarder->setShortcut(tr("Ctrl+S"));
	ui.actionSauvegarder_Sous->setShortcut(tr("F12"));
	ui.actionConnexion->setShortcut(tr("Ctrl+B"));
	ui.actionNouvel_Utilisateur->setShortcut(tr("Ctrl+N"));
	ui.actionSupprimer_un_Utilisateur->setShortcut(tr("Ctrl+D"));
	ui.actionChanger_d_Utilisateur->setShortcut(tr("Ctrl+E"));
	ui.actionRaccourcis_Clavier->setShortcut(tr("Ctrl+H"));
	ui.actionPrise_en_main_du_logiciel->setShortcut(tr("F1"));
	ui.actionQuitter->setShortcut(tr("Alt+F4"));

	// connect
	connect(ui.actionConnexion, SIGNAL(triggered(bool)),this,SLOT(Connexion()));
	connect(ui.actionNouvel_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(NouvelUtil()));
	connect(ui.actionChanger_d_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(Connexion()));
	connect(ui.actionSupprimer_un_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(SupprimerUtil()));

	connect(actionTailleTexte, SIGNAL(triggered(bool)),this,SLOT(TailleDeTexte()));
	connect(actionCouleurTexte, SIGNAL(triggered(bool)),this,SLOT(CouleurDeTexte()));

	connect(ui.actionApercu_avant_impression, SIGNAL(triggered(bool)),this,SLOT(ApercuAvtImpr()));
	connect(ui.actionImprimer, SIGNAL(triggered(bool)),this,SLOT(Impression()));

	connect(ui.PleinEcranCours, SIGNAL(clicked(bool)), this,SLOT(FullScreen_Cahiers()));
	connect(ui.PleinEcranEval, SIGNAL(clicked(bool)), this,SLOT(FullScreen_Cahiers()));
	connect(ui.PleinEcranExo, SIGNAL(clicked(bool)), this,SLOT(FullScreen_Cahiers()));
	connect(projetGeom, SIGNAL(clickSortieFullScreen()), this, SLOT(FullScreen_Geom()));
	connect(ui.GeomPleinEcran, SIGNAL(clicked(bool)), this,SLOT(FullScreen_Geom()));
	connect(ui.pushButton, SIGNAL(clicked(bool)), this,SLOT(insererGeom()));
	connect(ui.actionImprimer, SIGNAL(triggered(bool)),this,SLOT(Impression()));
	connect(ui.actionDocumentation_Utilisateur, SIGNAL(triggered(bool)), this,SLOT(Aide()));

	connect(ui.actionRaccourcis_Clavier, SIGNAL(triggered(bool)),this,SLOT(AffichageRaccourcis()));

	connect(actionRegle, SIGNAL(triggered(bool)),this,SLOT(creerRegle()));
	connect(actionEquerre, SIGNAL(triggered(bool)),this,SLOT(creerEquerre()));
	connect(actionCrayon, SIGNAL(triggered(bool)),this,SLOT(creerCrayon()));

	connect(projetGeom, SIGNAL(clickRegle()), this, SLOT(showParamRegle()));
	connect(projetGeom, SIGNAL(clickCompas()), this, SLOT(showParamCompas()));
	connect(projetGeom, SIGNAL(clickEquerre()), this, SLOT(showParamEquerre()));
	connect(projetGeom, SIGNAL(clickCrayon()), this, SLOT(showParamCrayon()));

	connect(ui.actionGrille, SIGNAL(triggered(bool)), this, SLOT(afficherGrille()));

	connect(ui.actionQuitter, SIGNAL(triggered(bool)),this,SLOT(close()));
}

Interface::~Interface()
{
	delete util;
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 01/02/2014
//! 
//! 
//! Simple appel à la fonction de Connexion via l'instance de User. Ce slot est connecté à deux éléments: la connexion et le changement d'Utilisateur (qui n'est en fait que la connexion sous un autres identifiant).
/////////////////////////////////////////////////////////////////////////// 
void Interface::Connexion()
{
	util->Connexion();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 01/02/2014
//! 
//! Simple appel à la fonction Enregistrement déjà implémentée.
/////////////////////////////////////////////////////////////////////////// 
void Interface::NouvelUtil()
{
	util->Enregistrement();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 01/02/2014 
//! 
//! Simple appel à la fonction de Suppression déjà implémentée.
/////////////////////////////////////////////////////////////////////////// 

void Interface::SupprimerUtil()
{
	util->RemoveUtil();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 28/01/2014
//! 
//! On regarde d'abord si le widget est déjà en plein écran (booléen widgetIsFullscreen). Ensuite on "détache" le QTabWidget (setParent(0)) pour pouvoir ensuite le mette en plein écran s'il ne l'était pas déjà. S'il était déjà en plein écran alors on le rattache (ajout au layout). On change l'icone du bouton en fonction de l'état dans lequel nous sommes (plein écran ou non).
/////////////////////////////////////////////////////////////////////////// 
void Interface::FullScreen_Cahiers()
{
	if(!widgetIsFullscreen)
	{
		ui.Onglets->setParent(0);
		ui.Onglets->showFullScreen();
		ui.PleinEcranCours->setIcon(QIcon("Resources/SortieFullscreen.gif"));
		ui.PleinEcranEval->setIcon(QIcon("Resources/SortieFullscreen.gif"));
		ui.PleinEcranExo->setIcon(QIcon("Resources/SortieFullscreen.gif"));
		widgetIsFullscreen = true;
		return;
	}
	else
	{
		ui.LayoutCahiers->addWidget(ui.Onglets);
		ui.Onglets->showNormal();
		
		ui.PleinEcranCours->setIcon(QIcon("Resources/Fullscreen.gif"));
		ui.PleinEcranEval->setIcon(QIcon("Resources/Fullscreen.gif"));
		ui.PleinEcranExo->setIcon(QIcon("Resources/Fullscreen.gif"));
		widgetIsFullscreen = false;
		return;
	}
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 28/01/2014 
//! 
//! On regarde tout d'abord si le widget est déjà en plein écran (booléen widgetIsFullscreen). Si ce n'est pas le cas, on le détache et on fait appel ) showFullScreen(). S'il était déjà en mode plein écran alors on le rattache et on appelle la fonction showNormal(). On change l'icone du bouton en fonction de l'état dans lequel nous sommes (plein écran ou non).
/////////////////////////////////////////////////////////////////////////// 
void Interface::FullScreen_Geom()
{
	if(!widgetIsFullscreen)
	{
        projetGeom->setParent(0);
        projetGeom->showFullScreen();
		ui.pushButton->hide();
		ui.GeomPleinEcran->hide();

		geom->regle = NULL;
		geom->equerre = NULL;
		geom->crayon = NULL;

        projetGeom->ui.widget->show();
        projetGeom->ui.DockWidgetCompas->hide();
        projetGeom->ui.DockWidgetCrayon->hide();
        projetGeom->ui.DockWidgetEquerre->hide();
        projetGeom->ui.DockWidgetRegle->hide();
        projetGeom->ui.ScrollAreaOptionsOutils->hide();

		widgetIsFullscreen = true;
		return;
	}
	else
	{
        projetGeom->geometrie->compas = NULL;
		projetGeom->geometrie->regle = NULL;
		projetGeom->geometrie->equerre = NULL;
		projetGeom->geometrie->crayon = NULL;
		ui.LayoutGeom->addWidget(ui.Geom);

		projetGeom->ui.BoutonRegle->setChecked(false);
		projetGeom->ui.BoutonEquerre->setChecked(false);
		projetGeom->ui.BoutonCompas->setChecked(false);
		projetGeom->ui.BoutonCrayon->setChecked(false);

        ui.geomEcranScind->addWidget(projetGeom);
        projetGeom->showNormal();
		ui.pushButton->show();
        ui.GeomPleinEcran->show();
        projetGeom->ui.widget->hide();
		projetGeom->ui.ScrollAreaOptionsOutils->hide();

		widgetIsFullscreen = false;
	}
}
// Fermeture du programme
void Interface::closeEvent(QCloseEvent *event)
{
	event->accept();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 26/01/2014 
//! 
//! Ouverture d'une boite de dialogue qui va demander à l'utilisateur de saisir une valeur entière pour la taille de police. Cette valeur sera ensuite assignée au QTextEdit.
/////////////////////////////////////////////////////////////////////////// 
void Interface::TailleDeTexte()
{
	bool ok, txtSelectionne;
	QTextCursor selection;
	fontSize = QInputDialog::getInt(this, "Taille de police", "Saisir la taille d‚sir‚e :", fontSize,2,72,1,&ok,0);
	if(ui.Onglets->currentIndex() == 0)
	{
		selection = txtCours->textCursor();
		if(selection.hasSelection())
			txtSelectionne = true;
		if(!txtSelectionne)
			txtCours->setFont(QFont("Times New Roman", fontSize));
	}
	
	if(ui.Onglets->currentIndex() == 1)
	{
		selection = txtEval->textCursor();
		if(selection.hasSelection())
			txtSelectionne = true;
		if(!txtSelectionne)
			txtEval->setFont(QFont("Times New Roman", fontSize));
	}
	
	if(ui.Onglets->currentIndex() == 2)
	{
		selection = txtExo->textCursor();
		if(selection.hasSelection())
			txtSelectionne = true;
		if(!txtSelectionne)
			txtExo->setFont(QFont("Times New Roman", fontSize));
	}
	
	if(txtSelectionne)
	{
		QTextCharFormat format;
		format.setFont(QFont("Times New Roman", fontSize));
		selection.setCharFormat(format);
	}
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 26/01/2014 
//! 
//! Ouverture d'une QColorDialog qui permet à l'utilisateur de choisir la couleur qu'il souhaite qui correspondra à la couleur de police du QTextEdit.
/////////////////////////////////////////////////////////////////////////// 
void Interface::CouleurDeTexte()
{
	fontColor = QColorDialog::getColor(Qt::white, this);
	if(ui.Onglets->currentIndex() == 0)
		txtCours->setTextColor(fontColor);
	
	if(ui.Onglets->currentIndex() == 1)
		txtEval->setTextColor(fontColor);
	
	if(ui.Onglets->currentIndex() == 2)
		txtExo->setTextColor(fontColor);
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 15/01/2014 
//! 
//! Simple QMessageBox mise en page à l'aide de balises html basiques. Regroupe les raccourcis clavier et leurs effets.
/////////////////////////////////////////////////////////////////////////// 
void Interface::AffichageRaccourcis()
{
	QString msg = QString::fromUtf8("<p><em>Gestion des utilisateurs : </em></p><p></p><p> <strong> - Ctrl + N </strong>: Ajout d'un utilisateur.</p> <p><strong> - Ctrl + D </strong>: Suppression d'un utilisateur.</p><p> <strong> - Ctrl + E </strong>: Changer d'utilisateur. </p><p></p><p> <em> Édition : </em> </p><p> <strong> - Ctrl + C </strong>: Copier. </p><p> <strong> - Ctrl + V </strong>: Coller.</p><p> <strong> - Ctrl + X </strong>: Couper. </p><p> <strong> - Ctrl + Z </strong>: Annuler. </p><p> <strong> - Ctrl + Y </strong>: Refaire. </p><p></p><p> <em> Autres : </p><p></p><p> <strong> - Ctrl + S </strong>: Sauvegarder. </p><p> <strong> - F12 </strong>: Sauvegarder Sous. </p><p> <strong> - Ctrl + P </strong>: Imprimer. </p><p> <strong> - Alt + P </strong>: Aperçu avant impression. </p><p> <strong> - F1 </strong>: Affichage de l'aide. </p><p> <strong> - Ctrl + H </strong>: Affichage de cette boite de dialogue. </p><p> <strong> - Alt + F4 </strong>: Quitter le programme.");
	QMessageBox* shortcuts = new QMessageBox(QMessageBox::NoIcon, "Raccourcis clavier ", msg);
	shortcuts->setIconPixmap(QPixmap("Resources/raccourcisClavier.png"));
	shortcuts->show();
}


/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 20/01/2014 
//! 
//! Instanciation de la classe QPrintPreviewDialog qui va permettre d'effectuer l'aperçu avant impression. 
/////////////////////////////////////////////////////////////////////////// 
void Interface::ApercuAvtImpr()
{
	QPrintPreviewDialog *printDialog = new QPrintPreviewDialog(printer);
    connect(printDialog, SIGNAL(paintRequested(QPrinter *)), this, SLOT(doSomething(QPrinter *)));
	printDialog->setWindowTitle("Aperçu avant impression");
    printDialog->exec();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 20/01/2014 
//! 
//! Ouverture d'un QPrintDialog qui va permettre de choisir l'imprimante souhaitée, le nombre de pages etc... Puis impression au moyen d'un QPainter qui va "dessiner" le contenu de la page.
/////////////////////////////////////////////////////////////////////////// 
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
    painter.translate(printer->paperRect().x() + printer->pageRect().width()/2, printer->paperRect().y() + printer->pageRect().height()/2);
    painter.scale(scale, scale);
    painter.translate(-width()/2, -height()/2);

    ui.Onglets->render(&painter);
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 01/02/2014
//!
//! Fonction permettant l'ouverture de la documentation (fichiers html/css) jointe.
/////////////////////////////////////////////////////////////////////////// 
void Interface::Aide()
{
	QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath()+"/Resources/Aide/index.html"));
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 01/02/2014
//!
//! Fonction permettant l'insertion des figures géométriques, créées dans le module de géométrie, dans les cahiers.
/////////////////////////////////////////////////////////////////////////// 
void Interface::insererGeom()
{
	/*ui.imgLabel->setPixmap(pix);
	QUrl Uri ( QString ( "Resources/img_Clone.jpg"));
	QTextDocument * textDocument = txtCours->document();
    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( *img ) );
    QTextCursor cursor = txtCours->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth( img->width() );
    imageFormat.setHeight( img->height() );
    imageFormat.setName( Uri.toString() );
    cursor.insertImage(imageFormat);*/
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 02/02/2014
//!
//! Fonction permettant la création d'une règle en écran scindé.
/////////////////////////////////////////////////////////////////////////// 
void Interface::creerRegle()
{
	if(projetGeom->geometrie->regle == NULL)
		geom->gererRegle();

	else
		projetGeom->geometrie->regle = NULL;
	
	ui.Geom->update();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 02/02/2014
//!
//! Fonction permettant la création d'une équerre en écran scindé.
/////////////////////////////////////////////////////////////////////////// 
void Interface::creerEquerre()
{
	if(projetGeom->geometrie->equerre == NULL)
		geom->gererEquerre();

	else
		projetGeom->geometrie->equerre = NULL;

	ui.Geom->update();	
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 02/02/2014
//!
//! Fonction permettant la création d'un crayon en écran scindé.
/////////////////////////////////////////////////////////////////////////// 
void Interface::creerCrayon()
{
	if(projetGeom->geometrie->crayon == NULL)
		geom->gererCrayon();

	else
		projetGeom->geometrie->crayon = NULL;

	
	ui.Geom->update();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 01/02/2014
//!
//! Fonction gerant l'affichage des paramètres de la règle.
/////////////////////////////////////////////////////////////////////////// 
void Interface::showParamRegle()
{
	if(projetGeom->ui.ScrollAreaOptionsOutils->isHidden())
		projetGeom->ui.ScrollAreaOptionsOutils->show();

	if(projetGeom->ui.DockWidgetRegle->isHidden())
		projetGeom->ui.DockWidgetRegle->show();
	else
		projetGeom->ui.DockWidgetRegle->hide();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 01/02/2014
//!
//! Fonction gerant l'affichage des paramètres de l'équerre.
/////////////////////////////////////////////////////////////////////////// 
void Interface::showParamEquerre()
{
	if(projetGeom->ui.ScrollAreaOptionsOutils->isHidden())
		projetGeom->ui.ScrollAreaOptionsOutils->show();

	if(projetGeom->ui.DockWidgetEquerre->isHidden())
		projetGeom->ui.DockWidgetEquerre->show();
	else
		projetGeom->ui.DockWidgetEquerre->hide();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 01/02/2014
//!
//! Fonction gerant l'affichage des paramètres du compas.
/////////////////////////////////////////////////////////////////////////// 
void Interface::showParamCompas()
{
	if(projetGeom->ui.ScrollAreaOptionsOutils->isHidden())
		projetGeom->ui.ScrollAreaOptionsOutils->show();

	if(projetGeom->ui.DockWidgetCompas->isHidden())
		projetGeom->ui.DockWidgetCompas->show();
	else
		projetGeom->ui.DockWidgetCompas->hide();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 01/02/2014
//!
//! Fonction gerant l'affichage des paramètres du crayon.
/////////////////////////////////////////////////////////////////////////// 
void Interface::showParamCrayon()
{
	if(projetGeom->ui.ScrollAreaOptionsOutils->isHidden())
		projetGeom->ui.ScrollAreaOptionsOutils->show();
	
	if(projetGeom->ui.DockWidgetCrayon->isHidden())
		projetGeom->ui.DockWidgetCrayon->show();
	else
		projetGeom->ui.DockWidgetCrayon->hide();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author JACQUIN Dylan
//! \date 10/02/2014
//!
//! Fonction gerant l'affichage de la grille depuis l'écran scindé.
/////////////////////////////////////////////////////////////////////////// 
void Interface::afficherGrille()
{
	projetGeom->ui.CheckBoxGrille->setChecked(ui.actionGrille->isChecked()); //Mise à jour de la checkbox Grille dans ProjetGeometrie
	projetGeom->geometrie->grille = ui.actionGrille->isChecked(); //Activation de la grille
	ui.Geom->update();
}
