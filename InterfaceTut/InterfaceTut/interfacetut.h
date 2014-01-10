#ifndef MAQUETTE_PT_H
#define MAQUETTE_PT_H

#include <QtGui/QMainWindow>
#include <qevent.h>
#include "user.h"
#include "ui_interfacetut.h"

class Interface : public QMainWindow
{
	Q_OBJECT

public:
	Interface(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Interface();

private:
	Ui::InterfaceClass ui;
	void closeEvent(QCloseEvent *event);
	User* util;

	public slots:
		void NouvelUtil();
		void SupprimerUtil();
		void FullScreen_Cahiers();
		void FullScreen_Geom();
};

#endif // MAQUETTE_PT_H
