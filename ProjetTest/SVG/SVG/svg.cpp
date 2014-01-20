#include "svg.h"

SVG::SVG(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushDebTracer, SIGNAL(pressed()), this, SLOT(DebutTracer()));
	connect(ui.pushDebGeneration, SIGNAL(pressed()), this, SLOT(DebutGeneration()));
	connect(ui.pushContinuerTracer, SIGNAL(pressed()), this, SLOT(ContinuerTracer()));
	connect(ui.pushFinGeneration, SIGNAL(pressed()), this, SLOT(FinGeneration()));

	peintre = new QPainter;
	peintre->setViewport(0,0,50,50);

	generator = new QSvgGenerator;
	generator->setFileName("./temps.svg");
    generator->setSize(QSize(50, 50));
    generator->setViewBox(QRect(0, 0, 50, 50));
    generator->setTitle(tr("SVG Generator Example Drawing"));
    generator->setDescription(tr("An SVG drawing created by the SVG Generator"));
}

SVG::~SVG()
{

}

void SVG::DebutTracer()
{
	peintre->begin(generator);
	peintre->drawLine(0,0,10,10);
}

void SVG::DebutGeneration()
{
	peintre->end();
}

void SVG::ContinuerTracer()
{
	peintre->begin(generator);
	peintre->drawLine(10,0,20,10);
}

void SVG::FinGeneration()
{
	peintre->end();
}
