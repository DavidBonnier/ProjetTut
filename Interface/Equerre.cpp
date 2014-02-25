///////////////////////////////////////////////////////////////////////////
//! \file Equerre.cpp
//!
//! \brief Mise en place des fonctions servant à modifier le fichier XML suivant la transformation appelée.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include "Equerre.h"
#include "Geometrie.h"
#include "projetgeometrie.h"
#include "qmath.h"

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \brief Constructeur de l'équerre, initialise toutes les valeurs du fichier XML à 0.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
Equerre::Equerre(ProjetGeometrie * projetGeometrie)
{
    m_projetGeometrie = projetGeometrie;

    m_nomFichierXML = new QString(":/XML/Resources/XML/Equerre.xml");
    m_nomDocument = new QString("Equerre");
    m_nomElement = new QString("equerre");

    InitialisationRegle();

    update();
}


Equerre::~Equerre()
{

}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param longueur Longueur de l'équerre
//! \param largeur Largeur de l'équerre
//! \param transp Hauteur de la zone transparente
//! \param x Position en x de l'équerre
//! \param y Position en y de l'équerre
//!
//! \return Retourne le point situé sur l'hypotenuse et la zone délimitant la transparence.
//!
//! \brief Calcul le point situé sur l'hypotenuse et la zone délimitant la transparence à l'aide de Thalès.
//!
//! \date 17/01/2014
///////////////////////////////////////////////////////////////////////
QPointF Equerre::Thales(double longueur, double largeur, double transp, int x, int y)
{
    double longueurTransp =  longueur*( (largeur-transp)/largeur); //Calcul de la longueur du segment délimitant la transparence
    return QPointF(x+longueurTransp, y+transp); //Retourne les coordonnée du point de l'intersection de ce segment avec l'hypoténuse
}

void Equerre::setTransparence(bool transparence)
{
    Instrument::setTransparence(transparence);
    m_projetGeometrie->ui.CheckBoxEquerreTransparence->setChecked(transparence);
}

void Equerre::translation(double positionX , double positionY)
{
    Instrument::translation(positionX,positionY);
    m_projetGeometrie->ui.SpinBoxEquerrePositionX->setValue(positionX);
    m_projetGeometrie->ui.SpinBoxEquerrePositionY->setValue(positionY);
}

void Equerre::setAngle(double angle)
{
    Instrument::setAngle(angle);
    m_projetGeometrie->ui.SpinBoxEquerreOrientation->setValue(angle);
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param dessin Prend le dessin du QPainter en paramètre
//!
//! \brief Cette fonction dessine une équerre grâce aux valeurs de son fichier XML.
//!
//! \date 17/01/2014
///////////////////////////////////////////////////////////////////////
void Equerre::paint(QPainter * dessin, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    dessin->save();

    int hauteurZoneTransp = m_largeur/7;

    if (m_transparence) //S'il y a de la transparence
        dessin->setPen(Qt::black);
    else //Pas de transparence
        dessin->setBrush(QColor(255,255,152)); //Couleur du petit rectangle

    //Rotation
    dessin->translate(m_position.x(),m_position.y());
    dessin->rotate(m_angle);
    dessin->translate(-m_position.x(),-m_position.y());
    //Dessin de la zone transparente
    QPointF pointHyp = Thales(m_longueur, m_largeur, hauteurZoneTransp, m_position.x(), m_position.y());
    QPointF pointsZoneTranparent[4] = {QPointF(m_position.x(), m_position.y()), QPointF(m_position.x()+m_longueur, m_position.y()), pointHyp, QPointF(m_position.x(), m_position.y()+hauteurZoneTransp)}; //Points de la zone transparente
    dessin->drawConvexPolygon(pointsZoneTranparent, 4); //Dessin de la zone transparente
    //Dessin de la zone principale
    dessin->setBrush(QColor(255,255,50)); //Mise en couleur de la partie principale de l'equerre
    QPointF triangle[3] = {pointHyp, QPointF(m_position.x(), m_position.y()+hauteurZoneTransp), QPointF(m_position.x(), m_position.y()+m_largeur)}; //Points du triangle principal
    dessin->drawConvexPolygon(triangle, 3); //Triangle principal
    //Dessin du bouton rotation
    dessin->setBrush(QColor(126,255,255));
    dessin->drawEllipse(QPointF(m_position.x()+250,m_position.y()+50),15,15);
    //Dessin des graduations
    dessin->setFont(QFont("Arial", 8)); //Police et taille des charactères
    int chiffre = 0; //Chiffre actuel sur l'équerre
    QString grad[] = {"0","1","2","3","4","5","6","7"}; //Chiffres sur l'équerre
    int hauteurMaxGrad = hauteurZoneTransp/2;
    for (int i=0 ; i<m_longueur ; i+=m_graduation*5) //5 pixels entre chaque graduations
    {
        if (i%50 == 0) //Graduation cm
        {
            dessin->drawLine(m_position.x()+i,m_position.y(), m_position.x()+i,m_position.y()+hauteurMaxGrad);
            dessin->drawText(m_position.x()+2+i, m_position.y()-3+m_largeur/8, grad[chiffre]); //Affichage des chiffres
            chiffre++;
        }
        else if (i%25 == 0) //Graduation 1/2 cm
            dessin->drawLine(m_position.x()+i,m_position.y(), m_position.x()+i,m_position.y()+hauteurMaxGrad/2);
        else //Graduation mm
            dessin->drawLine(m_position.x()+i,m_position.y(), m_position.x()+i,m_position.y()+hauteurMaxGrad/4);
    }
    dessin->restore();
}

