///////////////////////////////////////////////////////////////////////////
//! \file user.h
//!
//! \brief Déclaration des variables, fonctions pour la gestion des utilisateurs.
//!
//! Toutes les fonctions relatives à la gestion d'utilisateur (chargement des paramètres, enregistrement de l'utilisateur, suppression de l'utilisateur, détection de la première utilisation du logiciel, connexion...)sont présentées ici.
//!
//! \date 01/02/2014
//! \version 4.2
///////////////////////////////////////////////////////////////////////////

#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <qtextstream.h>
#include <qinputdialog.h>
#include <qfileinfo.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qvector.h>
#include <qdom.h>
#include <qxmlstream.h>

///////////////////////////////////////////////////////////////////////////
//! \class User
//!
//! \brief Classe héritant de QDialog qui va regrouper toute la gestion d'utilisateur.
//!
//! \author ROCHE Hugo
//! \date 6/01/2014
//! \version 2.1
//!
//! Cette classe va s'occuper de la gestion du .xml. Chargement des données de l'utilisateur, connexion, enregistrement et suppression. Pour cela on utilise le parser DOM proposé par QT.
///////////////////////////////////////////////////////////////////////////


class User : public QDialog
{
    Q_OBJECT

public:
    User(QDialog *parent = 0);
    ~User();

    QString id_user_actuel;
    QString mdp_user_actuel;
    bool user_actuel_IsAdmin;
	bool premUtil;
    QString fichier_user_actuel;

    void Connexion();
    void Enregistrement();
    void StockageVector();
    void RemoveUtil();
    bool firstUse();
};

#endif
