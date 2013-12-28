#pragma once
#include <qsvggenerator.h>
#include <qsvgrenderer.h>
#include <qsvgwidget.h>
#include <qpainter.h>

class DessinSvg : public QSvgGenerator
{
public:
	DessinSvg(void);
	~DessinSvg(void);

	void paintEvent (QPaintEvent * event);
};

