#include "interface.h"
#include "user.h"
#include <qapplication.h>
#include "qinputdialog.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    a.setApplicationName("Yolo");
    a.setOrganizationName("IUT du Puy");

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
