#include "svg.h"
#include "ui_svg.h"

svg::svg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::svg)
{
    ui->setupUi(this);
    connect(ui->pushDebutTracer, SIGNAL(pressed()), this, SLOT(DebutTracer()));
    connect(ui->pushDebGene, SIGNAL(pressed()), this, SLOT(DebutGeneration()));
    connect(ui->pushContinueTracer, SIGNAL(pressed()), this, SLOT(ContinuerTracer()));
    connect(ui->pushFinGene, SIGNAL(pressed()), this, SLOT(FinGeneration()));

    peintre = new QPainter(this);

    nomFichier = new QString("./enregistrement.svg");
    nomFichierTemp = new QString("./temps.svg");

    tabFigure[0] = new Arc();
    tabFigure[1] = new Ligne();
}

svg::~svg()
{
    delete ui;
}

void svg::DebutTracer()
{
    generator = new QSvgGenerator;
    generator->setFileName(*nomFichierTemp);

    peintre->begin(generator);
    //peintre->drawLine(0,0,10,10);
}

void svg::DebutGeneration()
{
    peintre->end();
    delete generator;
}

void svg::ContinuerTracer()
{
    generator = new QSvgGenerator;
    generator->setFileName(*nomFichier);
    generator->setSize(QSize(50, 50));
    generator->setViewBox(QRect(0, 0, 50, 50));
    generator->setTitle(tr("SVG Generator Example Drawing"));
    generator->setDescription(tr("An SVG drawing created by the SVG Generator"));
    peintre->begin(generator);
    renderer = new QSvgRenderer(*nomFichierTemp);
    renderer->render(peintre);
    peintre->drawLine(10,0,20,10);
    peintre->drawLine(10,0,20,10);
    peintre->drawLine(10,0,20,10);
    peintre->drawLine(0,0,10,10);
}

void svg::FinGeneration()
{
    peintre->end();
    delete generator;
}
