/////////////////////////////////////////////////////////////////////////// 
//! \file interface.cpp
//! 
//! \brief Mise en place de toutes les fonctionnalités relatives à l'Interface. Connect/signals et slots. 
//! 
//! On a crée dans le .h une variable de type User qui va nous permettre d'accéder aux fonctions de cette classe.
//! On crée donc les slots qui correspondent.
//! Pour les autres fonctionnalités, l'impression et l'aperçu avant impression par exemple,
//! on met simplement en place les fonctions dans ce fichier.
//! \date 01/02/2014
//! \version 2.3
/////////////////////////////////////////////////////////////////////////// 

#include "interface.h"

Interface::Interface(QMainWindow *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_nomLogiciel = QString("Logiciel de Mathématiques");
	setWindowTitle(m_nomLogiciel);
	setContextMenuPolicy(Qt::NoContextMenu);

	file = new QFile();

	util = new User();
	projetGeom = new ProjetGeometrie();
	ui.geomEcranScind->addWidget(projetGeom);

	projetGeom->ui.widget->hide();
	projetGeom->ui.ScrollAreaOptionsOutils->hide();

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
	impressionLanceViaApercu = false;
	txtModifie = false;
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

	ui.boutonInsertionGeom->setToolTip("Insérer la géométrie dans le cahier ouvert");
	ui.GeomPleinEcran->setToolTip("Travailler la géométrie en Plein Écran");
	ui.PleinEcranCours->setToolTip("Écrire sur vos cahiers en Plein Écran");
	ui.PleinEcranExo->setToolTip("Écrire sur vos cahiers en Plein Écran");
	ui.PleinEcranEval->setToolTip("Écrire sur vos cahiers en Plein Écran");

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
	connect(ui.actionNouveau, SIGNAL(triggered(bool)), this, SLOT(nouveauFichier()));
	connect(ui.actionSauvegarder, SIGNAL(triggered(bool)), this, SLOT(sauver()));
	connect(ui.actionSauvegarder_Sous, SIGNAL(triggered(bool)), this, SLOT(sauverSous()));
	connect(ui.actionOuvrir, SIGNAL(triggered(bool)), this, SLOT(ouvrir()));
	connect(ui.actionFermer, SIGNAL(triggered(bool)), this, SLOT(fermerFichier()));

	connect(txtCours, SIGNAL(textChanged()), this, SLOT(ModificationTexte()));

	connect(ui.actionConnexion, SIGNAL(triggered(bool)),this,SLOT(Connexion()));
	connect(ui.actionNouvel_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(NouvelUtil()));
	connect(ui.actionChanger_d_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(Connexion()));
	connect(ui.actionSupprimer_un_Utilisateur, SIGNAL(triggered(bool)),this,SLOT(SupprimerUtil()));

	connect(actionTailleTexte, SIGNAL(triggered(bool)),this,SLOT(TailleDeTexte()));
	connect(actionCouleurTexte, SIGNAL(triggered(bool)),this,SLOT(CouleurDeTexte()));

	connect(ui.actionImprimer, SIGNAL(triggered(bool)),this,SLOT(ApercuAvtImpr()));

	connect(ui.PleinEcranCours, SIGNAL(clicked(bool)), this,SLOT(FullScreen_Cahiers()));
	connect(ui.PleinEcranEval, SIGNAL(clicked(bool)), this,SLOT(FullScreen_Cahiers()));
	connect(ui.PleinEcranExo, SIGNAL(clicked(bool)), this,SLOT(FullScreen_Cahiers()));

	connect(projetGeom, SIGNAL(clickSortieFullScreen()), this, SLOT(FullScreen_Geom()));
	connect(ui.GeomPleinEcran, SIGNAL(clicked(bool)), this,SLOT(FullScreen_Geom()));
	connect(ui.boutonInsertionGeom, SIGNAL(clicked(bool)), this,SLOT(insererGeom()));

	connect(ui.actionDocumentation_Utilisateur, SIGNAL(triggered(bool)), this,SLOT(Aide()));
	connect(ui.A_propos, SIGNAL(triggered(bool)), this, SLOT(APropos()));
	connect(ui.actionRaccourcis_Clavier, SIGNAL(triggered(bool)),this,SLOT(AffichageRaccourcis()));

	connect(actionRegle, SIGNAL(triggered(bool)),this,SLOT(creerRegle()));
	connect(actionEquerre, SIGNAL(triggered(bool)),this,SLOT(creerEquerre()));
	connect(actionCrayon, SIGNAL(triggered(bool)),this,SLOT(creerCrayon()));

	connect(projetGeom, SIGNAL(clickRegle()), this, SLOT(showParamRegle()));
	connect(projetGeom, SIGNAL(clickCompas()), this, SLOT(showParamCompas()));
	connect(projetGeom, SIGNAL(clickEquerre()), this, SLOT(showParamEquerre()));
	connect(projetGeom, SIGNAL(clickCrayon()), this, SLOT(showParamCrayon()));

	connect(ui.actionGrille, SIGNAL(triggered(bool)), this, SLOT(afficherGrille()));

	connect(ui.actionCopier, SIGNAL(triggered(bool)),this,SLOT(copier()));
	connect(ui.actionColler, SIGNAL(triggered(bool)),this,SLOT(coller()));
	connect(ui.actionCouper, SIGNAL(triggered(bool)),this,SLOT(couper()));

	connect(ui.actionQuitter, SIGNAL(triggered(bool)),this,SLOT(close()));
}

Interface::~Interface()
{
	delete util;
	delete file;
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 01/02/2014
//! 
//! 
//! Simple appel à la fonction de Connexion via l'instance de User.
//! Ce slot est connecté à deux éléments: la connexion et le changement d'Utilisateur
//! (qui n'est en fait que la connexion sous un autres identifiant).
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
//! On regarde d'abord si le widget est déjà en plein écran (booléen widgetIsFullscreen).
//! Ensuite on "détache" le QTabWidget (setParent(0)) pour pouvoir ensuite le mette en plein écran s'il ne l'était pas déjà.
//! S'il était déjà en plein écran alors on le rattache (ajout au layout).
//! On change l'icone du bouton en fonction de l'état dans lequel nous sommes (plein écran ou non).
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
//! On regarde tout d'abord si le widget est déjà en plein écran (booléen widgetIsFullscreen).
//! Si ce n'est pas le cas, on le détache et on fait appel ) showFullScreen().
//! S'il était déjà en mode plein écran alors on le rattache et on appelle la fonction showNormal().
//! On change l'icone du bouton en fonction de l'état dans lequel nous sommes (plein écran ou non).
/////////////////////////////////////////////////////////////////////////// 
void Interface::FullScreen_Geom()
{
	if(!widgetIsFullscreen)
	{
		projetGeom->setParent(0);
		projetGeom->showFullScreen();
		projetGeom->m_geometrie->update();

		ui.boutonInsertionGeom->hide();
		ui.GeomPleinEcran->hide();

		projetGeom->m_geometrie->regle = NULL;
		projetGeom->m_geometrie->equerre = NULL;
		projetGeom->m_geometrie->crayon = NULL;

		ui.Geom->update();
		projetGeom->ui.widget->show();
		projetGeom->ui.DockWidgetCompas->hide();
		projetGeom->ui.DockWidgetCrayon->hide();
		projetGeom->ui.DockWidgetEquerre->hide();
		projetGeom->ui.DockWidgetRegle->hide();
		projetGeom->ui.ScrollAreaOptionsOutils->show();

		widgetIsFullscreen = true;
	}
	else
	{
		projetGeom->m_geometrie->compas = NULL;
		projetGeom->m_geometrie->regle = NULL;
		projetGeom->m_geometrie->equerre = NULL;
		projetGeom->m_geometrie->crayon = NULL;

		ui.LayoutGeom->addWidget(ui.Geom);

		projetGeom->ui.BoutonRegle->setChecked(false);
		projetGeom->ui.BoutonEquerre->setChecked(false);
		projetGeom->ui.BoutonCompas->setChecked(false);
		projetGeom->ui.BoutonCrayon->setChecked(false);

		ui.geomEcranScind->addWidget(projetGeom);
		projetGeom->showNormal();
		ui.boutonInsertionGeom->show();
		ui.GeomPleinEcran->show();
		projetGeom->ui.widget->hide();
		projetGeom->ui.ScrollAreaOptionsOutils->hide();

		widgetIsFullscreen = false;
	}
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 26/01/2014 
//! 
//! Ouverture d'une boite de dialogue qui va demander à l'utilisateur de saisir une valeur entière pour la taille de police.
//! Cette valeur sera ensuite assignée au QTextEdit.
/////////////////////////////////////////////////////////////////////////// 
void Interface::TailleDeTexte()
{
	bool ok, txtSelectionne;
	QTextCursor selection;
	fontSize = QInputDialog::getInt(this, "Taille de police", "Saisir la taille désirée :", fontSize,2,72,1,&ok,0);
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
//! Ouverture d'une QColorDialog qui permet à l'utilisateur de choisir la couleur
//! qu'il souhaite qui correspondra à la couleur de police du QTextEdit.
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
	QString msg = QString::fromUtf8("<p><em>Gestion des utilisateurs : </em></p><p></p><p> <strong> - Ctrl + N </strong>: Ajout d'un utilisateur.</p>"
		"<p><strong> - Ctrl + D </strong>: Suppression d'un utilisateur.</p>"
		"<p> <strong> - Ctrl + E </strong>: Changer d'utilisateur. </p><p></p>"
		"<p> <em> Édition : </em> </p><p> <strong> - Ctrl + C </strong>: Copier. </p>"
		"<p> <strong> - Ctrl + V </strong>: Coller.</p><p> <strong> - Ctrl + X </strong>: Couper. </p>"
		"<p> <strong> - Ctrl + Z </strong>: Annuler. </p><p> <strong> - Ctrl + Y </strong>: Refaire. </p><p></p>"
		"<p> <em> Autres : </p><p></p><p> <strong> - Ctrl + S </strong>: Sauvegarder. </p>"
		"<p> <strong> - F12 </strong>: Sauvegarder Sous. </p>"
		"<p> <strong> - Ctrl + P </strong>: Imprimer. </p>"
		"<p> <strong> - Alt + P </strong>: Aperçu avant impression. </p>"
		"<p> <strong> - F1 </strong>: Affichage de l'aide. </p>"
		"<p> <strong> - Ctrl + H </strong>: Affichage de cette boite de dialogue. </p>"
		"<p> <strong> - Alt + F4 </strong>: Quitter le programme.");
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
	QDesktopWidget screen;
	QRect mainScreenSize = screen.availableGeometry(screen.primaryScreen());

	QPrinter print(QPrinter::HighResolution);
	QPrintPreviewDialog preview(&print, this);
	preview.setWindowFlags ( Qt::Window );
	preview.setFixedSize(mainScreenSize.width() - 10, mainScreenSize.height() - 10);

	preview.setWindowTitle("Aperçu avant impression");
	connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(Impression(QPrinter *)));
	preview.exec();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 20/01/2014 
//! 
//! Ouverture d'un QPrintDialog qui va permettre de choisir l'imprimante souhaitée, le nombre de pages etc...
//! Puis impression au moyen d'un QPainter qui va dessiner le contenu de la page.
/////////////////////////////////////////////////////////////////////////// 
void Interface::Impression(QPrinter* p)
{
	txtCours->print(p);
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
	QString texteFinal;
	QString cheminImage(projetGeom->m_geometrie->generationSVG());
	if(ui.Onglets->currentIndex() == 0)
	{
		texteFinal = txtCours->toHtml() + "<img src = \""+ cheminImage +"\" alt = \"\"/>";
		txtCours->setHtml(texteFinal);
	}

	else if(ui.Onglets->currentIndex() == 1)
	{
		texteFinal = txtEval->toHtml() + "<img src = \""+ cheminImage +"\" alt = \"\"/>";
		txtEval->setHtml(texteFinal);
	}

	else if(ui.Onglets->currentIndex() == 2)
	{
		texteFinal = txtExo->toHtml() + "<img src = \""+ cheminImage +"\" alt = \"\"/>";
		txtExo->setHtml(texteFinal);
	}
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo 
//! \date 02/02/2014
//!
//! Fonction permettant la création d'une règle en écran scindé.
/////////////////////////////////////////////////////////////////////////// 
void Interface::creerRegle()
{
	if(projetGeom->m_geometrie->regle == NULL)
		projetGeom->m_geometrie->gererRegle();

	else
		projetGeom->m_geometrie->regle = NULL;

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
	if(projetGeom->m_geometrie->equerre == NULL)
		projetGeom->m_geometrie->gererEquerre();

	else
		projetGeom->m_geometrie->equerre = NULL;

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
	if(projetGeom->m_geometrie->crayon == NULL)
		projetGeom->m_geometrie->gererCrayon();

	else
		projetGeom->m_geometrie->crayon = NULL;


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
//! Fonction gerant l'affichage des paramètres du Compas.
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
	projetGeom->m_geometrie->grille = ui.actionGrille->isChecked(); //Activation de la grille
	ui.Geom->update();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author JACQUIN Dylan
//! \date 23/02/2014
//!
//! Fonction gérant affichant le 'A Propos'.
/////////////////////////////////////////////////////////////////////////// 
void Interface::APropos()
{
	QMessageBox info;
	info.setText("A Propos de ce logiciel");
	info.setInformativeText("<p>Ce logiciel a été réalisé par des étudiants de l'<strong>IUT du Puy-en-Velay</strong>"
		"dans le cadre d'un projet tuteuré visant à aider"
		"les personnes en situation de handicap dans les mathématiques.</p>"
		"<br/><br/>" 
		"Enseignant référant :<strong> MONCORGÉ Dominque</strong>"
		"<br/>""<br/>"
		"Étudiants ayant pris part au projet :"
		"<br/><br/>"
		"2013/2014 : Création du logiciel et intégration du module de géométrie"
		"<br/>""<br/>"
		"-<em>ADAMONY Ravel</em>"
		"<br/>"
		"-<em>BIOLLEY Pierre</em>"
		"<br/>"
		"-<em>BONNIER David</em>"
		"<br/>"
		"-<em>JACQUIN Dylan</em>"
		"<br/>"
		"-<em>ROCHE Hugo</em>");
	//To be continued...
	info.setIcon(QMessageBox::Information);
	info.setStandardButtons(QMessageBox::Ok);

	info.exec();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author JACQUIN Dylan
//! \date 28/02/2014
//!
//! Fonction permettant d'afficher une boîte de dialogue demandant de chemin où le fichier doit être sauvegarder.
//! Elle renvoie sur la fonction de sauvegarde.
/////////////////////////////////////////////////////////////////////////// 
void Interface::sauverSous()
{
	//Demande du nom du chemin avant de sauvegarder
	repSauvegarde = QFileDialog::getSaveFileName(this, tr("Enregistrer un fichier"), repSauvegarde, tr("Fichier texte (*.html)"));
	sauvegarder(); //Sauvegarde en ayant modifié le chemin
}

/////////////////////////////////////////////////////////////////////////// 
//! \author JACQUIN Dylan
//! \date 28/02/2014
//!
//! Fonction qui vérifie si l'on a défini un chemin lors d'une demande de sauvegarde simple. 
/////////////////////////////////////////////////////////////////////////// 
void Interface::sauver()
{
	if (repSauvegarde.isNull()) //Si c'est la première fois qu'on sauvegarde
		//On lance sauvegarder sous
		sauverSous();
	else
		sauvegarder();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author JACQUIN Dylan
//! \date 28/02/2014
//!
//! Fonction permettant de sauvegarder le contenu des cahiers.
/////////////////////////////////////////////////////////////////////////// 
void Interface::sauvegarder()
{
	file = new QFile(repSauvegarde); //Fichier de sauvegarde

	txtModifie = false;

	if(repSauvegarde == " ")
		setWindowTitle(m_nomLogiciel);
	else
	{
		QStringList filePath = (QString(repSauvegarde).split("/"));
		setWindowTitle(m_nomLogiciel + " - " + filePath[filePath.size() - 1]);
	}

	QTextStream FluxOut(file); //Flux pour le fichier de sauvegarde
	FluxOut.setCodec("UTF-8"); //Passage en UTF-8
	//Ouverture du fichier, et vérification
	if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QString *texte = new QString;
	*texte = txtCours->toHtml(); //Récupération et transcription du contenu du cahier en HTML.
	FluxOut << *texte << endl; //Ecriture dans le fichier
}

/////////////////////////////////////////////////////////////////////////// 
//! \author JACQUIN Dylan
//! \date 28/02/2014
//!
//! Fonction permettant l'ouverture d'un fichier.
/////////////////////////////////////////////////////////////////////////// 
void Interface::ouvrir()
{
	if(peutEtreSauver())
	{
		//Demande et récupération du ficher à ouvrir
		repSauvegarde = QFileDialog::getOpenFileName(this, tr("Ouverture d'un fichier texte"),
			repSauvegarde, tr("Fichier texte (*.html)"));

		if (!repSauvegarde.isEmpty())
		{
			QStringList filePath = (QString(repSauvegarde).split("/"));
			setWindowTitle(m_nomLogiciel + " - " + filePath[filePath.size() - 1]);

			QFile fichier(repSauvegarde);
			fichier.open(QIODevice::ReadOnly | QIODevice::Text); //Ouverture du fichier
			QTextStream flux(&fichier);

			QString texte = flux.readAll(); //Lecture entière du fichier

			if(ui.Onglets->currentIndex() == 0)
				txtCours->setHtml(texte);
			if(ui.Onglets->currentIndex() == 1)
				txtEval->setHtml(texte);
			if(ui.Onglets->currentIndex() == 2)
				txtExo->setHtml(texte);
		}
	}
}

///////////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//! \date 02/03/2014
//!
//! Fonction qui renvois true pour continuer l'action (Fichier sauvegarder ou non).
//! Renvois false qui stop l'action qui l'appelle (Message annuler).
///////////////////////////////////////////////////////////////////////////
bool Interface::peutEtreSauver()
{
	if(txtModifie)
	{
		QMessageBox* ret = new QMessageBox(QMessageBox::Information, m_nomLogiciel,tr("Ce document a été modifié.\n Voulez vous sauvegarder les changements ?"));
		ret->addButton(QMessageBox::Save)->setText("Sauvegarder");
		ret->addButton(QMessageBox::Discard)->setText("Ne pas sauvegarder");
		ret->addButton(QMessageBox::Cancel)->setText("Annuler");
		int rep = ret->exec();
		if(rep == QMessageBox::Save)
		{
			sauver();
			return true;
		}
		else if (rep == QMessageBox::Cancel)
			return false;
	}
	return true;

}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 01/03/2014
//!
//! Slot permettant la fermeture d'un fichier.
/////////////////////////////////////////////////////////////////////////// 
void Interface::fermerFichier()
{
	if(peutEtreSauver())
	{
		if(file->isOpen())
			file->close();

		if(ui.Onglets->currentIndex() == 0)
			txtCours->clear();
		if(ui.Onglets->currentIndex() == 1)
			txtEval->clear();
		if(ui.Onglets->currentIndex() == 2)
			txtExo->clear();

		repSauvegarde= " ";
		txtModifie = false;

		setWindowTitle(m_nomLogiciel);
	}
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 01/03/2014
//!
//! Slot permettant la création d'un nouveau fichier.
/////////////////////////////////////////////////////////////////////////// 
void Interface::nouveauFichier()
{
	if(peutEtreSauver())
	{
		if(file->isOpen())
			file->close();

		txtCours->clear();
		txtEval->clear();
		txtExo->clear();

		setWindowTitle(m_nomLogiciel);
		txtModifie = true;
	}
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 01/03/2014
//!
//! Slot appelé à chaque modification du texte. Met le booléen txtModifie à true.
//! Rajoute une asterisque au titre de la fenêtre pour signifier que le fichier est modifié et non sauvegardé.
/////////////////////////////////////////////////////////////////////////// 
void Interface::ModificationTexte()
{
	txtModifie = true;
	if(repSauvegarde != " ")
	{
		QStringList filePath = (QString(repSauvegarde).split("/"));
		setWindowTitle(m_nomLogiciel + " - " + filePath[filePath.size() - 1] + "*");
	}
	else
		setWindowTitle(m_nomLogiciel + " - Sans titre*");
}

void Interface::closeEvent(QCloseEvent *event)
{
	if(peutEtreSauver())
		event->accept();
	else
		event->ignore();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 02/03/2014
//!
//! Slot permettant de copier tout le contenu du cahier en cours ou simplement la selection.
/////////////////////////////////////////////////////////////////////////// 
void Interface::copier()
{
	if(ui.Onglets->currentIndex() == 0)
		txtCours->copy();
	if(ui.Onglets->currentIndex() == 1)
		txtEval->copy();
	if(ui.Onglets->currentIndex() == 2)
		txtExo->copy();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 02/03/2014
//!
//! Slot permettant de coller le contenu préalablement copié ou coupé..
/////////////////////////////////////////////////////////////////////////// 
void Interface::coller()
{
	if(ui.Onglets->currentIndex() == 0)
		txtCours->copy();
	if(ui.Onglets->currentIndex() == 1)
		txtEval->paste();
	if(ui.Onglets->currentIndex() == 2)
		txtExo->paste();
}

/////////////////////////////////////////////////////////////////////////// 
//! \author ROCHE Hugo
//! \date 02/03/2014
//!
//! Slot permettant de couper tout le contenu du cahier en cours ou simplement la selection.
/////////////////////////////////////////////////////////////////////////// 
void Interface::couper()
{
	if(ui.Onglets->currentIndex() == 0)
		txtCours->cut();
	if(ui.Onglets->currentIndex() == 1)
		txtEval->cut();
	if(ui.Onglets->currentIndex() == 2)
		txtExo->cut();
}
