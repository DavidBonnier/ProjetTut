///////////////////////////////////////////////////////////////////////
//! \mainpage
//! \section intro Introduction
//! Cette documentation a été créée pour le logiciel de mathématiques destiné aux handicapés. Ce logiciel a été développé dans le cadre d'un projet tuteuré de 2ème année en 2013-2014.
//! \section I Le Cheminement du projet
//! \subsection Ii  - Année où le projet a été proposé
//! Nous avons eu de nombreuses réunions (dont une avec le SSESD (<em>Service de Soins et d'Éducation Spécialisée à Domicile</em>) qui nous ont permis d'établir un cahier des charges que nous avons soumis aux clients. Une fois le cahier des charges accepté, nous nous sommes lancés dans la phase de programmation. Nous avons implémenté des instruments en XML, une gestion utilisateur aussi en XML, différentes fonctions de tracés, un magnétisme des instruments...
//! \section II Ce que nous avons apporté
//! \subsection IIi - Année où le projet a été proposé
//! La première année où ce projet a été proposé, nous avons été chargés du module de géométrie ainsi que de la gestion utilisateurs. Vous trouverez des informations relatives aux fonctions et classes du programme dans cette documentation. Si vous souhaitez comprendre comment marche une fonctionnalité, une documentation utilisateur est aussi à votre disposition.
//! 
//!
//!
//! 
///////////////////////////////////////////////////////////////////////


#include <QApplication>
#include <QInputDialog>
#include <QTranslator>

#include "interface.h"
#include "user.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    Interface w;
	User util;
	if(util.firstUse())
	{
		util.premUtil = true;
		util.Enregistrement();
	}
	w.show();
	return a.exec();
}
