#ifndef QTSVG_H
#define QTSVG_H

#include <QtWidgets/QWidget>
#include "ui_qtsvg.h"

class QtSVG : public QWidget
{
	Q_OBJECT

public:
	QtSVG(QWidget *parent = 0);
	~QtSVG();

private:
	Ui::QtSVGClass ui;
};

#endif // QTSVG_H
