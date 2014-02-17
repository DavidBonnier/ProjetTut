#ifndef SVG_H
#define SVG_H

#include <QWidget>
#include <QPainter>
#include <QtSvg/QSvgGenerator>
#include <QtSvg/QSvgRenderer>
#include <QFile>
#include "arc.h"
#include "ligne.h"


namespace Ui {
class svg;
}

class svg : public QWidget
{
    Q_OBJECT

public:
    svg(QWidget *parent = 0);
    ~svg();

private:
    Ui::svg *ui;
    QWidget * tabFigure [2];
    QFile * fichier;
    QPainter * peintre;
    QSvgGenerator * generator;
    QSvgRenderer * renderer;
    QString * nomFichier;
    QString * nomFichierTemp;

public slots :
    void DebutTracer();
    void DebutGeneration();
    void ContinuerTracer();
    void FinGeneration();
};

#endif // SVG_H
