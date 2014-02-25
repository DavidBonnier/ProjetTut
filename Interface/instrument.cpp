#include "instrument.h"
#include "Geometrie.h"

Instrument::Instrument(QWidget *parent) :
    QWidget(parent)
{
}

Instrument::~Instrument()
{
    delete m_nomFichierXML;
    delete m_nomDocument;
    delete m_nomElement;
}

void Instrument::Initialisation()
{
    Q_ASSERT_X(QFile::exists(*m_nomFichierXML), "Open XML", "Not find : " + *m_nomFichierXML->toStdString().c_str());
    QFile xml_doc(*m_nomFichierXML);// On choisit le fichier contenant les informations XML.
    QDomDocument dom(*m_nomDocument); // Création de l'objet DOM
    QDomElement dom_element = dom.documentElement();
    QDomNode noeud = dom_element.firstChild();
    while(!noeud.isNull()) //Parours du fichier
    {
        QDomElement element = noeud.toElement(); // On utilise cette propriété afin de transformer le nœud en éléments.
                                                 //Cela nous permet aussi de récupérer l'élément ou nœud courant.
        if(!element.isNull()) //S'il y a un élément dans le noeud
        {
            //Boolean
            if (element.tagName() == "transparence")
                m_transparence = element.text().toInt();
            if (element.tagName() == "moveSelected")
                m_moveSelected = element.text().toInt();
            if (element.tagName() == "rotateSelectedRight")
                m_rotateSelectedRight = element.text().toInt();
            if (element.tagName() == "rotateSelectedLeft")
                m_rotateSelectedLeft = element.text().toInt();

            //Variable
            if (element.tagName() == "positionX")
                m_position.setX(element.text().toInt());
            if (element.tagName() == "positionY")
                m_position.setY(element.text().toInt());
            if (element.tagName() == "angle")
                m_angle = element.text().toDouble();
            if (element.tagName() == "offsetX")
                m_offset.setX(element.text().toInt());
            if (element.tagName() == "offsetY")
                m_offset.setY(element.text().toInt());
            if (element.tagName() == "posClicX")
                m_posClic.setX(element.text().toInt());
            if (element.tagName() == "posClicY")
                m_posClic.setY(element.text().toInt());

            //Constantes
            if (element.tagName() == "longueur")
                m_longueur = element.text().toInt();
            if (element.tagName() == "largeur")
                m_largeur = element.text().toInt();
            if (element.tagName() == "epaisseur")
                m_epaisseur = element.text().toInt();
        }
        noeud = noeud.nextSibling(); //Ce code permet d'aller à l'élément suivant.
    }
    xml_doc.close();
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param positionX Nouvelle position en x
//! \param positionY Nouvelle position en y
//!
//! \brief Cette fonction met à jour les nouvelles position en x et y et met a jour ui.
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Instrument::translation(double positionX , double positionY)
{
    m_position.setX(positionX);
    m_position.setY(positionY);
    update();
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param transparence Change le paramètre de la transparence
//!
//! \brief Cette fonction choisit si on affiche les instrments en transparence ou pas.
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Instrument::setTransparence(bool transparence)
{
    m_transparence = transparence;
    update();
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param newangle Nouvelle orientation
//!
//! \brief Cette fonction met à jour le fichier XML de la règle avec sa nouvelle orientation
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Instrument::setAngle(double angle)
{
    m_angle = angle;
    update();
}

void Instrument::clic(QMouseEvent *clic, bool boutonRotation)
{
    if(m_moveSelected||m_rotateSelectedLeft||m_rotateSelectedRight)
    {
        deselectionner();
        return;
    }

    if(!boutonRotation)
    {
        m_moveSelected = true;
        m_offset.setX(clic->x() - m_position.x());
        m_offset.setY(clic->y() - m_position.y());
    }

    else
    {
        if (m_angle > 90 && m_angle < 270)
            m_rotateSelectedLeft = true;
        else
            m_rotateSelectedRight = true;
        m_oldRotationValue = m_angle;
        m_posClic.setX(clic->x());
        m_posClic.setY(clic->y());
    }
    update();
}

void Instrument::move(QMouseEvent *move)
{
    if(m_moveSelected)
    {
        translation(move->x() - m_offset.x(), move->y() - m_offset.y());
        //Pom_position.x()es positions négatives
        if (m_position.x() < 0)
        {
            m_offset.setX(move->x());
            translation(0,m_position.y());
        }

        if (m_position.y() < 0)
        {
            m_offset.setX(m_position.x());
            translation(m_position.x(),0);
        }
    }

    if (m_rotateSelectedRight || m_rotateSelectedLeft)
    {
        double xA = m_posClic.x() -m_position.x();
        double yA = m_posClic.y() -m_position.y();
        double xB = move->x() - m_position.x();
        double yB = move->y() - m_position.y();
        double cosTheta = (xA*xB + yA*yB)/(sqrt(pow(xA,2)+pow(yA,2)) * sqrt(pow(xB,2)+pow(yB,2)));
        double thetaRadians = acos(cosTheta);
        double theta = (180*thetaRadians)/3.14159265359;
        //On regarde si la souris est au dessus de la droite (posClic, pos)
        double cd =m_position.x();
        double h = m_position.x()-cd*m_position.y();
        if (move->y() < cd * move->x() + h)
            theta = -theta;
        double newAngle;
        if (m_rotateSelectedRight)
            newAngle = m_oldRotationValue + theta;
        else
            newAngle = m_oldRotationValue - theta;
        if (newAngle < 0)
            newAngle +=360;
        if (newAngle > 360)
            newAngle -= 360;
        setAngle(newAngle);
    }
    update();
}

void Instrument::deselectionner()
{
    m_moveSelected = false;
    m_rotateSelectedRight = false;
    m_rotateSelectedLeft = false;
}

double Instrument::toGradian(double angle)
{
    return PI*(angle/180);
}
