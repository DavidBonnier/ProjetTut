#include "interfacetut.h"
#include "user.h"
#include <QtGui/QApplication>
#include "qinputdialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Interface w;
	User t;
	bool ok = false;
	QMessageBox* choix = new QMessageBox(QMessageBox::Question, "Gestion des utilisateurs ", "Souhaitez-vous vous enregistrer?");
	choix->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	choix->setButtonText(QMessageBox::Yes, "Oui");
	choix->setButtonText(QMessageBox::No, "Non");
	choix->show();
	int ret = choix->exec();
	switch (ret)
	{
		case QMessageBox::Yes:
			t.Enregistrement();
			t.StockageVector();
			break;

		case QMessageBox::No:
			t.Connexion();
			break;

		default: 
			w.close();
	}
	w.show();
	return a.exec();
}
