/////////////////////////////////////////////////////////////////////////// 
//! \file interface.h
//! 
//! \brief Déclaration des variables nécessaires à la réalisation de l'Interface 
//! 
//! Déclaration de tous les slots nécessaires à la réalisation de l'interface.
//! 
//! \date 01/02/2014
//! \version 2.3
/////////////////////////////////////////////////////////////////////////// 

#ifndef INTERFACE_H
#define INTERFACE_H

#include <qmainwindow.h>
#include <qevent.h>
#include "user.h"
#include "qpainter.h"
#include "qtextedit.h"
#include "qcolordialog.h"
#include "ui_interface.h"
#include "ui_projetgeometrie.h"
#include "qscrollarea.h"
#include "qdesktopservices.h"
#include "qurl.h"
#include "qtoolbar.h"
#include "QtPrintSupport\qprinter.h"
#include "QtPrintSupport\qprintdialog.h"
#include "QtPrintSupport\qprintpreviewdialog.h"
#include "qdesktopwidget.h"
#include "qimage.h"
#include "Compas.h"
#include "qtextcodec.h"
#include "projetgeometrie.h"
#include "Regle.h"
#include "Geometrie.h"
#include "Crayon.h"
#include "Equerre.h"
/////////////////////////////////////////////////////////////////////////// 
//! \class Interface
//! 
//! \brief Classe regroupant toutes les fonctionnalités relatives à la gestion de l'interface.
//! 
//! \author ROCHE Hugo
//! \date 06/01/2014
//! \version 2.1 
//! 
//! Signaux/slots, instanciation de la classe User pour accéder aux fonctions qui se rapportent à la gestion des Utilisateurs.
/////////////////////////////////////////////////////////////////////////// 

class Interface : public QMainWindow
{
	Q_OBJECT

public:
	Interface(QMainWindow *parent = 0);
	~Interface();
private:
    Ui::InterfaceClass ui;
	void closeEvent(QCloseEvent *event);

	int fontSize;

	QColor fontColor;
	bool widgetIsFullscreen, impressionLanceViaApercu, txtModifie, newFile;

    QVBoxLayout* layoutCours;
	QVBoxLayout* layoutExo;
	QVBoxLayout* layoutEval;
	QTextEdit* txtCours;
	QTextEdit* txtEval;
	QTextEdit* txtExo;

	QWidget* container;
	User* util;
	
	ProjetGeometrie* projetGeom;

	//Toolbar écran scindé
	QAction* actionTailleTexte;
	QAction* actionCouleurTexte;
	QAction* actionEquerre;
	QAction* actionRegle;
	QAction* actionCrayon;

	QImage* img;
	QPixmap pix;

	//Outils de sauvegarde et ouverture
	QString repSauvegarde;
	QString nomFichier;
	QFileDialog fichierOuvert;
	QFile* file;
	void sauvegarder();

public slots:
	void nouveauFichier();
	void sauver();
	void sauverSous();
	void ouvrir();
	void fermerFichier();
	void ModificationTexte();

    void Connexion();
    void NouvelUtil();
    void SupprimerUtil();

    void FullScreen_Cahiers();
    void FullScreen_Geom();

    void TailleDeTexte();
    void CouleurDeTexte();

    void AffichageRaccourcis();
    void ApercuAvtImpr();
    void Impression(QPrinter* p);

    void Aide();
	void APropos();

    void insererGeom();

    void creerRegle();
    void creerEquerre();
    void creerCrayon();

    void showParamRegle();
    void showParamEquerre();
    void showParamCompas();
    void showParamCrayon();

    void afficherGrille();
};

#endif // INTERFACE_H
