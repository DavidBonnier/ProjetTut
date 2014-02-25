///////////////////////////////////////////////////////////////////////////
//! \file Regle.cpp
//!
//! \brief Mise en place des fonctions servant à modifier le fichier XML suivant la transformation appelée.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include "Regle.h"
#include "projetgeometrie.h"

Regle::Regle()
{
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \brief Constructeur de la règle, initialise toutes les valeurs du fichier XML à 0.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
Regle::Regle(ProjetGeometrie * projetGeometrie)
{
    m_projetGeometrie = projetGeometrie;

    m_nomFichierXML = new QString(":/XML/Resources/XML/Regle.xml");
    m_nomDocument = new QString("Regle");
    m_nomElement = new QString("regle");

    InitialisationRegle();

    update();
}

void Regle::InitialisationRegle()
{
    Initialisation();

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
            if (element.tagName() == "graduation")
                m_graduation = element.text().toInt();
        }
        noeud = noeud.nextSibling(); //Ce code permet d'aller à l'élément suivant.
    }
    xml_doc.close();
}



Regle::~Regle()
{

}

//***************************************Fonctions de mise à jour des valeurs***************************************
///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param g Défini le nouveau type de graduation
//!
//! \brief Cette fonction met à jour le fichier XML de la règle avec le nouveau type de graduation (cm, 1/2cm, mm).
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Regle::setGraduation(int graduation)
{
    QFile *file = new QFile(*m_nomFichierXML);
    QString graduationString = QString::number(graduation); //Cast de bool en QString

    QByteArray xmlData(file->readAll());
    QDomDocument doc(*m_nomDocument);
    doc.setContent(xmlData);
    //Définition du noeud regle
    QDomElement root = doc.firstChildElement(*m_nomElement);
    //Recherche et remplacement du noeud
    root.firstChildElement("graduation").firstChild().setNodeValue(graduationString);
    file->resize(0);
    QTextStream stream(file);
    stream.setDevice(file);
    doc.save(stream, 4);
    file->close();
    m_graduation = graduation;
    update();
}

void Regle::setTransparence(bool transparence)
{
    Instrument::setTransparence(transparence);
    m_projetGeometrie->ui.CheckBoxRegleTransparence->setChecked(transparence);
}

void Regle::translation(double positionX , double positionY)
{
    Instrument::translation(positionX,positionY);
    m_projetGeometrie->ui.SpinBoxReglePositionX->setValue(positionX);
    m_projetGeometrie->ui.SpinBoxReglePositionY->setValue(positionY);
}

void Regle::setAngle(double angle)
{
    Instrument::setAngle(angle);
    m_projetGeometrie->ui.SpinBoxRegleOrientation->setValue(angle);
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param dessin Prend le dessin du QPainter en paramètre
//!
//! \brief Cette fonction dessine une règle grâce aux valeurs de son fichier XML.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
void Regle::paint(QPainter * dessin, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    dessin->save();

    if (m_transparence) //S'il y a de la transparence
        dessin->setPen(Qt::black);
    else //Pas de transparence
        dessin->setBrush(QColor(255,255,153)); //Couleur du petit rectangle

    //Rotation
    dessin->translate(x(),y());
    dessin->translate(-x(),-y());
    //Dessin des rectangles
    dessin->drawRect(x(), y(), m_longueur, m_largeur/4); //Rectangle plein ou vide (1/4 du rectangle principal)
    dessin->setBrush(QColor(255,255,51)); //Mise en couleur de la partie principale de la regle
    dessin->drawRect(x(), y()+m_largeur/4, m_longueur, m_largeur);
    //Dessin du bouton de rotation
    dessin->setBrush(QColor(127,255,255));
    dessin->drawEllipse(QPointF(x()+500,y()+50),15,15);

//Dessin des graduations
    int hauteurMaxGrad = m_largeur/6;
    dessin->setFont(QFont("Arial", 8)); //Police et taille des charactères
    int chiffre = 0; //Chiffre actuel sur la règle
    QString grad[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12"}; //Chiffres sur la règle
    for (int i=0 ; i<m_longueur ; i+=m_graduation*5) //5 pixels entre chaque graduations
    {
        if (i%50 == 0) //Graduation cm
        {
            dessin->drawLine(x()+i,y(), x()+i,y()+hauteurMaxGrad);
            dessin->drawText(x()+2+i, y()-3+m_largeur/2, grad[chiffre]); //Affichage des chiffres
            chiffre++;
        }
        else if (i%25 == 0) //Graduation 1/2 cm
            dessin->drawLine(x()+i,y(), x()+i,y()+2*hauteurMaxGrad/3);
        else //Graduation mm
            dessin->drawLine(x()+i,y(), x()+i,y()+hauteurMaxGrad/3);
    }
    dessin->restore();
}
