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
