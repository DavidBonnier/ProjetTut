#include "test.h"

Test::Test(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);
	ui.widget_6->hide();
	//setWindowState(Qt::WindowFullScreen);
	svgGenerator = new DessinSvg;
	svgGenerator->setSize(QSize(800,800));
	svgGenerator->setResolution(300);
	svgGenerator->setTitle("Test de svg des familles");
	svgGenerator->setViewBox(QRect(0,0,800,800));
	QPainter painter(svgGenerator);
	painter.drawLine(0,0,100,100);
	
}

Test::~Test()
{

}

void Test::paintEvent (QPaintEvent * event)
{
	svgGenerator->paintEvent(event);
}