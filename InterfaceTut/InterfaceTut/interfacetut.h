#ifndef MAQUETTE_PT_H
#define MAQUETTE_PT_H

#include <QtGui/QMainWindow>
#include <qevent.h>
#include "user.h"
#include "qtextedit.h"
#include "ui_interfacetut.h"

class Interface : public QMainWindow
{
	Q_OBJECT

public:
	Interface(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Interface();

	bool txtZoneIsClicked;

protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	Ui::InterfaceClass ui;
	void closeEvent(QCloseEvent *event);
	void mousePressEvent(QMouseEvent* mouse);
	
	QTextEdit* txt;
	User* util;
	QAction* actionZoneTexte;


	public slots:
		void Aide();
		void ChangerUtil();
		void NouvelUtil();
		void SupprimerUtil();
		void FullScreen_Cahiers();
		void FullScreen_Geom();
		void ZoneDeTexte();
		void AffichageRaccourcis();
};

#endif // MAQUETTE_PT_H
