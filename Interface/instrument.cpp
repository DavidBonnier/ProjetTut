#include "instrument.h"
#include "Geometrie.h"

Instrument::Instrument()
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

            //Variable
            if (element.tagName() == "positionX")
                setX(element.text().toInt());
            if (element.tagName() == "positionY")
                setY(element.text().toInt());
            if (element.tagName() == "angle")
                setRotation(element.text().toDouble());
            /*if (element.tagName() == "offsetX")
                m_offset.setX(element.text().toInt());
            if (element.tagName() == "offsetY")
                m_offset.setY(element.text().toInt());
            if (element.tagName() == "posClicX")
                m_posClic.setX(element.text().toInt());
            if (element.tagName() == "posClicY")
                m_posClic.setY(element.text().toInt());*/

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

double Instrument::toGradian(double angle)
{
    return M_PI*(angle/180);
}

void Instrument::setAngle(double angle)
{
    setRotation(angle);
    update();
}

void Instrument::translation(double positionX , double positionY)
{
   setPos(positionX, positionY);
   update();
}
