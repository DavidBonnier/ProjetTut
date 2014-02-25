#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <QWidget>
#include <QFile>
#include "qmath.h"
#include <QPoint>
#include <QGraphicsItem>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

#include "arc.h"
#include "ligne.h"

class ProjetGeometrie;

class Instrument : public QGraphicsItem
{
public:
    Instrument(QGraphicsItem * parent);
    ~Instrument();

    virtual void setTransparence(bool transparence);
    virtual void translation(double positionX , double positionY);
    virtual void setAngle(double angle);
    QRectF boundingRect(void);

    inline int getLongueur(){return m_longueur;}
    inline int getLargeur(){return m_largeur;}

    bool m_moveSelected;

protected:
    //Instrument
    bool m_transparence;
    int m_longueur;
    int m_largeur;

    QString* m_nomFichierXML;
    QString* m_nomDocument;
    QString* m_nomElement;

    void Initialisation();
    double toGradian(double angle);

    ProjetGeometrie * m_projetGeometrie;
};

#endif // INSTRUMENT_H
