#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QWidget>
#include <QFile>
#include <QtSvg/QSvgGenerator>
#include <QtSvg/QSvgRenderer>
#include "math.h"

#define PI 3.14159265358979323846264279502884

#include "arc.h"
#include "ligne.h"

class Geometrie;

class Instrument : public QWidget
{
    Q_OBJECT
public:
    Instrument(QWidget *parent = 0);
    ~Instrument();

    //Fonctions de sélection avec la souris
    void clic(QMouseEvent *clic, bool boutonRotation);
    void move(QMouseEvent *move);
    void deselectionner();

    virtual void setTransparence(bool transparence);
    virtual void translation(double positionX , double positionY);
    virtual void setAngle(double angle);

    bool m_moveSelected;
    bool m_rotateSelectedRight;
    bool m_rotateSelectedLeft;

protected:
    //Instrument
    int m_positionX;
    int m_positionY;
    double m_angle;
    bool m_transparence;
    int m_longueur;
    int m_largeur;
    int m_epaisseur;
    //Vecteur Instrument -> Souris
    int m_offsetX;
    int m_offsetY;
    //Rotation
    int m_posClicX;
    int m_posClicY;
    int m_oldRotationValue;

    QString* m_nomFichierXML;
    QString* m_nomDocument;
    QString* m_nomElement;

    void Initialisation();
    double toGradian(double angle);

    Geometrie * m_geometrie;
};

#endif // INSTRUMENT_H
