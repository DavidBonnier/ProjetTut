#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QWidget>
#include <QFile>
#include <QtSvg/QSvgGenerator>
#include <QtSvg/QSvgRenderer>
#include "qmath.h"
#include <QPoint>

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
    void clic(QMouseEvent *clic, bool boutonRotation, bool boutonEcartement);
    void move(QMouseEvent *move);
    void deselectionner();

    virtual void setTransparence(bool transparence);
    virtual void translation(double positionX , double positionY);
    virtual void setAngle(double angle);

    inline int getPositionX(){return m_position.x();}
    inline int getPositionY(){return m_position.y();}
    inline double getAngle(){return m_angle;}
    inline int getLongueur(){return m_longueur;}
    inline int getLargeur(){return m_largeur;}

    bool m_moveSelected;
    bool m_rotateSelectedRight;
    bool m_rotateSelectedLeft;
	bool m_ecartSelected;

protected:
    //Instrument
    QPoint m_position;
    double m_angle;
    bool m_transparence;
    int m_longueur;
    int m_largeur;
    //Vecteur Instrument -> Souris
    QPoint m_offset;
    //Rotation
    QPoint m_posClic;
    int m_oldRotationValue;
	int m_oldEcartValue;

    QString* m_nomFichierXML;
    QString* m_nomDocument;
    QString* m_nomElement;

    void Initialisation();
    double toGradian(double angle);

    Geometrie * m_geometrie;
};

#endif // INSTRUMENT_H
