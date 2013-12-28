#include "DessinSvg.h"


DessinSvg::DessinSvg(void)
{
}


DessinSvg::~DessinSvg(void)
{
}

void DessinSvg::paintEvent (QPaintEvent *)
{
	QPainter painter(this);
	painter.drawLine(0,0,100,100);
}