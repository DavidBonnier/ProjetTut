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
    QFile xml_doc(*m_nomFichierXML);// On choisit le fichier contenant les informations XML.
    if(!xml_doc.open(QIODevice::ReadOnly))// Si l'on n'arrive pas à ouvrir le fichier XML.
    {
         QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre ouvert. Verifiez que le nom est le bon et que le document est bien place");
         return;
    }
    QDomDocument dom(*m_nomDocument); // Création de l'objet DOM
    if (!dom.setContent(&xml_doc)) // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.
    {
         xml_doc.close();
         QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre attribue a l'objet QDomDocument.");
         return;
    }
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
                m_positionX = element.text().toInt();
            if (element.tagName() == "positionY")
                m_positionY = element.text().toInt();
            if (element.tagName() == "angle")
                m_angle = element.text().toDouble();
            if (element.tagName() == "offsetX")
                m_offsetX = element.text().toInt();
            if (element.tagName() == "offsetY")
                m_offsetY = element.text().toInt();
            if (element.tagName() == "posClicX")
                m_posClicX = element.text().toInt();
            if (element.tagName() == "posClicY")
                m_posClicY = element.text().toInt();

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
//! \param newx Nouvelle position en x
//! \param newy Nouvelle position en y
//!
//! \brief Cette fonction met à jour le fichier XML du compas avec les nouvelles position en x et y.
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Instrument::translation(double positionX , double positionY)
{
    m_positionX = positionX;
    m_positionY = positionY;
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
        m_offsetX = clic->x() - m_positionX;
        m_offsetY = clic->y() - m_positionY;
    }

    else
    {
        if (m_angle > 90 && m_angle < 270)
            m_rotateSelectedLeft = true;
        else
            m_rotateSelectedRight = true;
        m_oldRotationValue = m_angle;
        m_posClicX = clic->x();
        m_posClicY = clic->y();
    }
    update();
}

void Instrument::move(QMouseEvent *move)
{
    if(m_moveSelected)
    {
        translation(move->x() - m_offsetX, move->y() - m_offsetY);
        //Pour éviter les positions négatives
        if (m_positionX < 0)
        {
            m_offsetX = move->x();
            translation(0,m_positionY);
        }

        if (m_positionY < 0)
        {
            m_offsetY = move->y();
            translation(m_positionX,0);
        }
    }

    if (m_rotateSelectedRight || m_rotateSelectedLeft)
    {
        double xA = m_posClicX - m_positionX;
        double yA = m_posClicY - m_positionY;
        double xB = move->x() - m_positionX;
        double yB = move->y() - m_positionY;
        double cosTheta = (xA*xB + yA*yB)/(sqrt(pow(xA,2)+pow(yA,2)) * sqrt(pow(xB,2)+pow(yB,2)));
        double thetaRadians = acos(cosTheta);
        double theta = (180*thetaRadians)/3.14159265359;
        //On regarde si la souris est au dessus de la droite (posClic, pos)
        double cd = yA/xA;
        double h = m_positionX-cd*m_positionY;
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
