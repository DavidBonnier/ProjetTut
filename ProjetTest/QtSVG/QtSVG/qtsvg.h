#ifndef QTSVG_H
#define QTSVG_H

#include <QtWidgets/QWidget>
#include "ui_qtsvg.h"
#include <qpainter.h>
#include <qsvgrenderer.h>

class QtSVG : public QWidget
{
	Q_OBJECT

public:
	QtSVG(QWidget *parent = 0);
	~QtSVG();

	QSvgGenerator generator;

private:
	Ui::QtSVGClass ui;
};

#endif // QTSVG_H
