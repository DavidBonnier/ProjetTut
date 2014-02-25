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
	m_ecartSelected = false;
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

void Instrument::clic(QMouseEvent *clic, bool boutonRotation, bool boutonEcartement)
{
    if(m_moveSelected||m_rotateSelectedLeft||m_rotateSelectedRight||m_ecartSelected)
    {
        deselectionner();
        return;
    }

    if(!boutonEcartement&&!boutonRotation)
    {
        m_moveSelected = true;
        m_offset.setX(clic->x() - m_position.x());
        m_offset.setY(clic->y() - m_position.y());
    }

	if(boutonEcartement&&!boutonRotation)
	{
		m_ecartSelected = true;
		m_posClic.setX(clic->x());
		m_posClic.setY(clic->y());
		Compas* com = dynamic_cast<Compas*>(this);
		if (com)
			m_oldEcartValue = com->getEcart();
	}

	if(!boutonEcartement&&boutonRotation)
	{
		Equerre* equ = dynamic_cast<Equerre*>(this);
		Compas* com = dynamic_cast<Compas*>(this);
		Regle* reg = dynamic_cast<Regle*>(this);
		Crayon* cra = dynamic_cast<Crayon*>(this);
		int thUp, thDown;
		if(equ || reg)
		{
			thDown = 90;
			thUp = 270;
		}
		else
		{
			thDown = 0;
			thUp = 180;
		}
		if (m_angle > thDown && m_angle < thUp)
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
			m_position.setX(0);
        }

        if (m_position.y() < 0)
        {
			m_position.setY(0);
        }
		Equerre* equ = dynamic_cast<Equerre*>(this);
		if (equ)
		{
			equ->MagnetiserEquerre(m_geometrie->tableauFigure);
			equ->translation (equ->getPositionX(),equ->getPositionY());
			equ->setAngle (equ->getAngle());
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
        double cd =yA/xA;
        double h = m_position.y()-cd*m_position.x();
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

	if(m_ecartSelected)
	{
		Compas* com = dynamic_cast<Compas*>(this);
		if (com) com->sourisEcart(move);
	}
    update();
}

void Instrument::deselectionner()
{
    m_moveSelected = false;
    m_rotateSelectedRight = false;
    m_rotateSelectedLeft = false;
	m_ecartSelected = false;
}

double Instrument::toGradian(double angle)
{
    return PI*(angle/180);
}
