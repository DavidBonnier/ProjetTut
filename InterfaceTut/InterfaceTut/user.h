#ifndef USER_H
#define USER_H

#include <QDialog>
#include <qtextstream.h>
#include <qinputdialog.h>
#include <qfileinfo.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qvector.h>

class User : public QDialog
{
	Q_OBJECT

public:
	User(QDialog *parent = 0);
	~User();

	QString id_user_actuel;
	QString mdp_user_actuel;
	bool user_actuel_IsAdmin;
	QString fichier_user_actuel;

	QVector<QString> identifiant;
	QVector<QString> mot_de_passe;
	QVector<QString> administrateur;
	QVector<QString> emplacement_fichier;

	void Connexion();
	void Enregistrement();
	void StockageVector();
	void RemoveUtil();

};

#endif // USER_H
