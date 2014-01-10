#include "qtsvg.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtSVG w;
	w.show();
	return a.exec();
}
