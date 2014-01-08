#include "projetgeometrie.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ProjetGeometrie w;
	w.show();
	return a.exec();
}
