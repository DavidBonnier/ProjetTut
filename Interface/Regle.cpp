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
    m_nomFichierXML = new QString("Regle.xml");
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
    graduation1 *= 50;
    graduation2 *= 50;

    QPointF * debTrait = NULL;
    QPointF * finTrait = NULL;

    const int angleDroit = 90;
    const int decalageRegle = 1;

    if(m_angle == 0 || m_angle == 360)
    {
        debTrait = new QPointF(m_positionX + graduation1, m_positionY - decalageRegle);
        finTrait = new QPointF(m_positionX + graduation2, m_positionY - decalageRegle);
    }
    else if(m_angle < 90)
    {
        const double x1 = cos(toGradian(m_angle)) * graduation1;
        const double y1 = sin(toGradian(m_angle)) * graduation1;
        const double x2 = cos(toGradian(m_angle)) * graduation2;
        const double y2 = sin(toGradian(m_angle)) * graduation2;
        debTrait = new QPointF(m_positionX + x1 + decalageRegle, m_positionY + y1);
        finTrait = new QPointF(m_positionX + x2 + decalageRegle, m_positionY + y2);
    }
    else if(m_angle == 90)
    {
        debTrait = new QPointF(m_positionX + decalageRegle, m_positionY + graduation1);
        finTrait = new QPointF(m_positionX + decalageRegle, m_positionY + graduation2);
    }
    else if(m_angle < 180)
    {
        const double angleEcartement = m_angle - angleDroit;
        const double x1 = sin(toGradian(angleEcartement)) * graduation1;
        const double y1 = cos(toGradian(angleEcartement)) * graduation1;
        const double x2 = sin(toGradian(angleEcartement)) * graduation2;
        const double y2 = cos(toGradian(angleEcartement)) * graduation2;
        debTrait = new QPointF(m_positionX - x1, m_positionY + y1 + decalageRegle);
        finTrait = new QPointF(m_positionX - x2, m_positionY + y2 + decalageRegle);
    }
    else if(m_angle == 180)
    {
        debTrait = new QPointF(m_positionX - graduation1, m_positionY + decalageRegle);
        finTrait = new QPointF(m_positionX - graduation2, m_positionY + decalageRegle);
    }
    else if(m_angle < 270)
    {
        const double angleEcartement = m_angle - 2*angleDroit;
        const double x1 = cos(toGradian(angleEcartement)) * graduation1;
        const double y1 = sin(toGradian(angleEcartement)) * graduation1;
        const double x2 = cos(toGradian(angleEcartement)) * graduation2;
        const double y2 = sin(toGradian(angleEcartement)) * graduation2;
        debTrait = new QPointF(m_positionX - x1 - decalageRegle, m_positionY - y1);
        finTrait = new QPointF(m_positionX - x2 - decalageRegle, m_positionY - y2);
    }
    else if(m_angle == 270)
    {
        debTrait = new QPointF(m_positionX - decalageRegle, m_positionY - graduation1);
        finTrait = new QPointF(m_positionX - decalageRegle, m_positionY - graduation2);
    }
    else if(m_angle < 360)
    {
        const double angleEcartement = m_angle - 3*angleDroit;
        const double x1 = sin(toGradian(angleEcartement)) * graduation1;
        const double y1 = cos(toGradian(angleEcartement)) * graduation1;
        const double x2 = sin(toGradian(angleEcartement)) * graduation2;
        const double y2 = cos(toGradian(angleEcartement)) * graduation2;
        debTrait = new QPointF(m_positionX + x1, m_positionY - y1 - decalageRegle);
        finTrait = new QPointF(m_positionX + x2, m_positionY - y2 - decalageRegle);
    }

    if (debTrait && finTrait)
        m_geometrie->tableauFigure.push_back(new Ligne(QLineF(*debTrait, *finTrait)));
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
    Instrument::setTransparence(transparence);
    m_geometrie->m_projetGeometrie->ui.CheckBoxRegleTransparence->setChecked(transparence);
}

void Regle::translation(double positionX , double positionY)
{
    Instrument::translation(positionX,positionY);
    m_geometrie->m_projetGeometrie->ui.SpinBoxReglePositionX->setValue(positionX);
    m_geometrie->m_projetGeometrie->ui.SpinBoxReglePositionY->setValue(positionY);
}

void Regle::setAngle(double angle)
{
    Instrument::setAngle(angle);
    m_geometrie->m_projetGeometrie->ui.SpinBoxRegleOrientation->setValue(angle);
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
    dessin.translate(m_positionX,m_positionY);
    dessin.rotate(m_angle);
    dessin.translate(-m_positionX,-m_positionY);
    //Dessin des rectangles
    dessin.drawRect(m_positionX, m_positionY, m_longueur, m_largeur/4); //Rectangle plein ou vide (1/4 du rectangle principal)
    dessin.setBrush(QColor(255,255,51)); //Mise en couleur de la partie principale de la regle
    dessin.drawRect(m_positionX, m_positionY+m_largeur/4, m_longueur, m_largeur);
    //Dessin du bouton de rotation
    dessin.setBrush(QColor(127,255,255));
    dessin.drawEllipse(QPointF(m_positionX+500,m_positionY+50),15,15);

//Dessin des graduations
    int hauteurMaxGrad = m_largeur/6;
    dessin.setFont(QFont("Arial", 8)); //Police et taille des charactères
    int chiffre = 0; //Chiffre actuel sur la règle
    QString grad[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12"}; //Chiffres sur la règle
    for (int i=0 ; i<m_longueur ; i+=m_graduation*5) //5 pixels entre chaque graduations
    {
        if (i%50 == 0) //Graduation cm
        {
            dessin.drawLine(m_positionX+i,m_positionY, m_positionX+i,m_positionY+hauteurMaxGrad);
            dessin.drawText(m_positionX+2+i, m_positionY-3+m_largeur/2, grad[chiffre]); //Affichage des chiffres
            chiffre++;
        }
        else if (i%25 == 0) //Graduation 1/2 cm
            dessin.drawLine(m_positionX+i,m_positionY, m_positionX+i,m_positionY+2*hauteurMaxGrad/3);
        else //Graduation mm
            dessin.drawLine(m_positionX+i,m_positionY, m_positionX+i,m_positionY+hauteurMaxGrad/3);
    }
    dessin.restore();
}
