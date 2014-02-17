#include "svg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    svg w;
    w.show();

    return a.exec();
}
