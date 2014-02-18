///////////////////////////////////////////////////////////////////////////
//! \file Equerre.cpp
//!
//! \brief Mise en place des fonctions servant à modifier le fichier XML suivant la transformation appelée.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include "Equerre.h"
#include "Geometrie.h"

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \brief Constructeur de l'équerre, initialise toutes les valeurs du fichier XML à 0.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
Equerre::Equerre(Geometrie * geometrie)
{
    m_nomFichierXML = new QString("Equerre.xml");
    m_nomDocument = new QString("Equerre");
    m_nomElement = new QString("equerre");

    m_geometrie = geometrie;

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

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param dessin Prend le dessin du QPainter en paramètre
//!
//! \brief Cette fonction dessine une équerre grâce aux valeurs de son fichier XML.
//!
//! \date 17/01/2014
///////////////////////////////////////////////////////////////////////
void Equerre::dessinerEquerre(QPainter& dessin)
{
    dessin.save();

    int hauteurZoneTransp = m_largeur/7;

    if (m_transparence) //S'il y a de la transparence
        dessin.setPen(Qt::black);
    else //Pas de transparence
        dessin.setBrush(QColor(255,255,152)); //Couleur du petit rectangle

    //Rotation
    dessin.translate(m_positionX,m_positionY);
    dessin.rotate(m_angle);
    dessin.translate(-m_positionX,-m_positionY);
    //Dessin de la zone transparente
    QPointF pointHyp = Thales(m_longueur, m_largeur, hauteurZoneTransp, m_positionX, m_positionY);
    QPointF pointsZoneTranparent[4] = {QPointF(m_positionX, m_positionY), QPointF(m_positionX+m_longueur, m_positionY), pointHyp, QPointF(m_positionX, m_positionY+hauteurZoneTransp)}; //Points de la zone transparente
    dessin.drawConvexPolygon(pointsZoneTranparent, 4); //Dessin de la zone transparente
    //Dessin de la zone principale
    dessin.setBrush(QColor(255,255,50)); //Mise en couleur de la partie principale de l'equerre
    QPointF triangle[3] = {pointHyp, QPointF(m_positionX, m_positionY+hauteurZoneTransp), QPointF(m_positionX, m_positionY+m_largeur)}; //Points du triangle principal
    dessin.drawConvexPolygon(triangle, 3); //Triangle principal
    //Dessin du bouton rotation
    dessin.setBrush(QColor(126,255,255));
    dessin.drawEllipse(QPointF(m_positionX+250,m_positionY+50),15,15);
    //Dessin des graduations
    dessin.setFont(QFont("Arial", 8)); //Police et taille des charactères
    int chiffre = 0; //Chiffre actuel sur l'équerre
    QString grad[] = {"0","1","2","3","4","5","6","7"}; //Chiffres sur l'équerre
    int hauteurMaxGrad = hauteurZoneTransp/2;
    for (int i=0 ; i<m_longueur ; i+=m_graduation*5) //5 pixels entre chaque graduations
    {
        if (i%50 == 0) //Graduation cm
        {
            dessin.drawLine(m_positionX+i,m_positionY, m_positionX+i,m_positionY+hauteurMaxGrad);
            dessin.drawText(m_positionX+2+i, m_positionY-3+m_largeur/8, grad[chiffre]); //Affichage des chiffres
            chiffre++;
        }
        else if (i%25 == 0) //Graduation 1/2 cm
            dessin.drawLine(m_positionX+i,m_positionY, m_positionX+i,m_positionY+hauteurMaxGrad/2);
        else //Graduation mm
            dessin.drawLine(m_positionX+i,m_positionY, m_positionX+i,m_positionY+hauteurMaxGrad/4);
    }
    dessin.restore();
}
