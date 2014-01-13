#ifndef MAQUETTE_PT_H
#define MAQUETTE_PT_H

#include <QtGui/QMainWindow>
#include <qevent.h>
#include "user.h"
#include "qpainter.h"
#include "qtextedit.h"
#include "ui_interfacetut.h"
#include "qprinter.h"
#include "qprintdialog.h"
#include "qprintpreviewdialog.h"

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
	QPrinter* printer;

	public slots:
		void Aide();

		void ChangerUtil();
		void NouvelUtil();
		void SupprimerUtil();

		void FullScreen_Cahiers();
		void FullScreen_Geom();

		void ZoneDeTexte();
		void AffichageRaccourcis();
		void ApercuAvtImpr();
		void Impression();
};

#endif // MAQUETTE_PT_H
