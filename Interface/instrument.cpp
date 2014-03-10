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
            if (element.tagName() == "rotateSelected")
                m_rotateSelected = element.text().toInt();

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
        }
        noeud = noeud.nextSibling(); //Ce code permet d'aller à l'élément suivant.
    }
    xml_doc.close();
	m_ecartSelected = false;
	m_traceSelected = false;
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

void Instrument::clic(QMouseEvent *clic, bool boutonRotation, bool boutonEcartement , bool boutonTrace)
{
	if(m_moveSelected||m_rotateSelected||m_ecartSelected||m_traceSelected)
    {
        deselectionner();
        return;
    }

	if(!boutonEcartement&&!boutonRotation&&!boutonTrace)
    {
        m_moveSelected = true;
        m_offset.setX(clic->x() - m_position.x());
        m_offset.setY(clic->y() - m_position.y());
    }

	if(!boutonEcartement&&!boutonRotation&&boutonTrace)
    {
        m_moveSelected = true;
		m_traceSelected = true;
        m_offset.setX(clic->x() - m_position.x());
        m_offset.setY(clic->y() - m_position.y());
    }

	if(boutonEcartement&&!boutonRotation&&!boutonTrace)
	{
		m_ecartSelected = true;
		m_posClic.setX(clic->x());
		m_posClic.setY(clic->y());
		Compas* com = dynamic_cast<Compas*>(this);
		if (com)
			m_oldEcartValue = com->getEcart();
	}

	if(!boutonEcartement&&boutonRotation&&!boutonTrace)
	{
		m_rotateSelected = true;
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
		Equerre* equ = dynamic_cast<Equerre*>(this);
		if (equ)
		{
			equ->MagnetiserEquerre(m_geometrie->tableauFigure);
			equ->translation (equ->getPositionX(),equ->getPositionY());
			equ->setAngle (equ->getAngle());
		}
		Regle* reg = dynamic_cast<Regle*>(this);
		if (reg)
		{
			reg->MagnetiserRegle(m_geometrie->tableauFigure);
			reg->translation (reg->getPositionX(),reg->getPositionY());
			reg->setAngle (reg->getAngle());
		}
		Crayon* cra = dynamic_cast<Crayon*>(this);
		if (cra)
		{
			cra->MagnetiserCrayon(m_geometrie->tableauFigure);
			cra->translation (cra->getPositionX(),cra->getPositionY());
			cra->setAngle (cra->getAngle());
			if(cra->m_traceSelected)
			{
				cra->traceCrayon();
			}
		}
		Compas* comp = dynamic_cast<Compas*>(this);
		if (comp)
		{
			comp->MagnetiserCompas(m_geometrie->tableauFigure);
			comp->translation (comp->getPositionX(),comp->getPositionY());
			comp->setAngle (comp->getAngle());
		}
    }

    if (m_rotateSelected)
    {
		QPoint tailleFenetre (m_geometrie->largeurViewport * 0.75, m_geometrie->hauteurViewport * 0.875);
       QVector2D VecteurRegleSouris (move->x() - tailleFenetre.x() - m_position.x(), move->y() - tailleFenetre.y() - m_position.y());
		double newAngle = (180/M_PI)*acos (VecteurRegleSouris.x()/sqrt (pow (VecteurRegleSouris.x(),2) + pow (VecteurRegleSouris.y(),2)));
        if (newAngle < 0)
            newAngle +=360;
        if (newAngle > 360)
            newAngle -= 360;
		if (move->y() - m_geometrie->hauteurViewport * 0.875 >= m_position.y())
		{
			setAngle(newAngle);
		}
		else
		{
			setAngle(newAngle + 2*(180-newAngle));
		}
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
	m_rotateSelected = false;
	m_ecartSelected = false;
	m_traceSelected = false;
}

double Instrument::toGradian(double angle)
{
    return M_PI*(angle/180);
}
