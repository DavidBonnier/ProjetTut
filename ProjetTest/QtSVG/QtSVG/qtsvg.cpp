#include "qtsvg.h"

QtSVG::QtSVG(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	generator.setFileName("./test");
  generator.setSize(QSize(200, 200));
  generator.setViewBox(QRect(0, 0, 200, 200));
  generator.setTitle(tr("SVG Generator Example Drawing"));
  generator.setDescription(tr("An SVG drawing created by the SVG Generator "
                              "Example provided with Qt."));
}

QtSVG::~QtSVG()
{

}
