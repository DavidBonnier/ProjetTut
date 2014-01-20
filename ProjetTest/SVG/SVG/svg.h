#ifndef SVG_H
#define SVG_H

#include <QtWidgets/QWidget>
#include "ui_svg.h"
#include <qpainter.h>
#include <qsvggenerator.h>

class SVG : public QWidget
{
	Q_OBJECT

public:
	SVG(QWidget *parent = 0);
	~SVG();

private:
	Ui::SVGClass ui;
	QPainter * peintre;
	QSvgGenerator * generator;

public slots:
	void DebutTracer();
	void DebutGeneration();
	void ContinuerTracer();
	void FinGeneration();
};

#endif // SVG_H
