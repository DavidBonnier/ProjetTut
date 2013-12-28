#ifndef TEST_H
#define TEST_H

#include <QtWidgets/QMainWindow>
#include "ui_test.h"

#include <qsvggenerator.h>
#include <qsvgrenderer.h>
#include <qsvgwidget.h>
#include <qpainter.h>

#include "DessinSvg.h"

class Test : public QMainWindow
{
	Q_OBJECT

public:
	Test(QWidget *parent = 0);
	~Test();
	DessinSvg *svgGenerator;

private:
	Ui::plopClass ui;
	void paintEvent (QPaintEvent * event);

};

#endif // TEST_H
