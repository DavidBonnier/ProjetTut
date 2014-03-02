///////////////////////////////////////////////////////////////////////////
//! \file Regle.cpp
//!
//! \brief Mise en place des fonctions servant à modifier le fichier XML suivant la transformation appelée.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include "Regle.h"
#include "Geometrie.h"
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
Regle::Regle(Geometrie * geometrie)
{
    m_nomFichierXML = new QString("Resources/XML/Regle.xml");
    m_nomDocument = new QString("Regle");
    m_nomElement = new QString("regle");

    m_geometrie = geometrie;

    InitialisationRegle();

    update();
}

void Regle::InitialisationRegle()
{
    Initialisation();

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

///////////////////////////////////////////////////////////////////////
//! \author  BONNIER David
//!
//! \param grad1 Graduation de départ du trait
//! \param grad2 Graduation de fin du trait
//!
//! \brief Cette fonction permet de tracer un trait entre grad1 et grad2.
//!
//! \date 17/02/2014
///////////////////////////////////////////////////////////////////////
void Regle :: tracer (double graduation1 , double graduation2 )
{
    double temps;
    if(graduation1 > graduation2)
    {
        temps = graduation1;
        graduation1 = graduation2;
        graduation2 = temps;
    }

    graduation1 *= 50;
    graduation2 *= 50;

    Ligne * ligne = new Ligne(m_position.x() + graduation1, m_position.y(),
                              m_position.x() + graduation2, m_position.y());
    ligne->setAngle(-m_angle);

    if(m_geometrie->tableauFigure.isEmpty())
        m_geometrie->tableauFigure.push_back(ligne);
    else
    {
        Ligne* maLigne = dynamic_cast<Ligne*> (m_geometrie->tableauFigure[m_geometrie->tableauFigure.size()-1]);
        if(maLigne && !maLigne->getFin())
        {
            maLigne->setQLine(ligne->getQLine());
            maLigne->setAngle(-m_angle);
        }
        else
            m_geometrie->tableauFigure.push_back(ligne);
    }
}

void Regle :: finTracer()
{
    if(!m_geometrie->tableauFigure.isEmpty())
    {
        Ligne* maLigne = dynamic_cast<Ligne*> (m_geometrie->tableauFigure[m_geometrie->tableauFigure.size()-1]);
        if(maLigne && !maLigne->getFin())
        {
            maLigne->setFin(true);
        }
    }
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

    if (!file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(this,"Erreur","Impossible d'ouvrir le ficher XML");
        file->close();
        return;
    }

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
    m_geometrie->m_projetGeometrie->ui.CheckBoxRegleTransparence->setChecked(transparence);
    Instrument::setTransparence(transparence);
}

void Regle::translation(double positionX , double positionY)
{
    m_geometrie->m_projetGeometrie->ui.SpinBoxReglePositionX->setValue(positionX);
    m_geometrie->m_projetGeometrie->ui.SpinBoxReglePositionY->setValue(positionY);
    Instrument::translation(positionX,positionY);
}

void Regle::setAngle(double angle)
{
    m_geometrie->m_projetGeometrie->ui.SpinBoxRegleOrientation->setValue(angle);

    if(!m_geometrie->tableauFigure.isEmpty())
    {
        Ligne* maLigne = dynamic_cast<Ligne*> (m_geometrie->tableauFigure[m_geometrie->tableauFigure.size()-1]);
        if(maLigne && !maLigne->getFin())
            maLigne->setAngle(-m_angle);
    }
    Instrument::setAngle(angle);
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
void Regle::dessinerRegle(QPainter& dessin)
{
    dessin.save();

    if (m_transparence) //S'il y a de la transparence
        dessin.setPen(Qt::black);
    else //Pas de transparence
        dessin.setBrush(QColor(255,255,153)); //Couleur du petit rectangle

    //Rotation
    dessin.translate(m_position.x(),m_position.y());
    dessin.rotate(m_angle);
    dessin.translate(-m_position.x(),-m_position.y());
    //Dessin des rectangles
    dessin.drawRect(m_position.x(), m_position.y(), m_longueur, m_largeur/4); //Rectangle plein ou vide (1/4 du rectangle principal)
    dessin.setBrush(QColor(255,255,51)); //Mise en couleur de la partie principale de la regle
    dessin.drawRect(m_position.x(), m_position.y()+m_largeur/4, m_longueur, m_largeur);
    //Dessin du bouton de rotation
    dessin.setBrush(QColor(127,255,255));
    dessin.drawEllipse(QPointF(m_position.x()+500,m_position.y()+50),15,15);

//Dessin des graduations
    int hauteurMaxGrad = m_largeur/6;
    dessin.setFont(QFont("Arial", 8)); //Police et taille des charactères
    int chiffre = 0; //Chiffre actuel sur la règle
    QString grad[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12"}; //Chiffres sur la règle
    for (int i=0 ; i<m_longueur ; i+=m_graduation*5) //5 pixels entre chaque graduations
    {
        if (i%50 == 0) //Graduation cm
        {
            dessin.drawLine(m_position.x()+i,m_position.y(), m_position.x()+i,m_position.y()+hauteurMaxGrad);
            dessin.drawText(m_position.x()+2+i, m_position.y()-3+m_largeur/2, grad[chiffre]); //Affichage des chiffres
            chiffre++;
        }
        else if (i%25 == 0) //Graduation 1/2 cm
            dessin.drawLine(m_position.x()+i,m_position.y(), m_position.x()+i,m_position.y()+2*hauteurMaxGrad/3);
        else //Graduation mm
            dessin.drawLine(m_position.x()+i,m_position.y(), m_position.x()+i,m_position.y()+hauteurMaxGrad/3);
    }
    dessin.restore();
}
