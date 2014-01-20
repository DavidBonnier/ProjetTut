#include "svg.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SVG w;
	w.show();
	return a.exec();
}
