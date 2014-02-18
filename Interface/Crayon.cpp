///////////////////////////////////////////////////////////////////////////
//! \file Crayon.cpp
//!
//! \brief Mise en place des fonctions servant à modifier le fichier XML suivant la transformation appelée.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include "Crayon.h"
#include "Geometrie.h"
#include "projetgeometrie.h"

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \brief Constructeur du crayon, initialise toutes les valeurs du fichier XML à 0.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
Crayon::Crayon(Geometrie * geometrie)
{
    m_nomFichierXML = new QString("Crayon.xml");
    m_nomDocument = new QString("Crayon");
    m_nomElement = new QString("crayon");

    m_geometrie = geometrie;

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
            if (element.tagName() == "hauteurPointe")
                m_hauteurPointe = element.text().toInt();
            if (element.tagName() == "epaisseur")
                m_epaisseur = element.text().toInt();
        }
        noeud = noeud.nextSibling(); //Ce code permet d'aller à l'élément suivant.
    }
    xml_doc.close();

    update();
}

void Crayon::setTransparence(bool transparence)
{
    Instrument::setTransparence(transparence);
    m_geometrie->m_projetGeometrie->ui.CheckBoxCrayonTransparence->setChecked(transparence);
}

void Crayon::translation(double positionX , double positionY)
{
    Instrument::translation(positionX,positionY);
    m_geometrie->m_projetGeometrie->ui.SpinBoxCrayonPositionX->setValue(positionX);
    m_geometrie->m_projetGeometrie->ui.SpinBoxCrayonPositionY->setValue(positionY);
}

void Crayon::setAngle(double angle)
{
    Instrument::setAngle(angle);
    m_geometrie->m_projetGeometrie->ui.SpinBoxCrayonOrientation->setValue(angle);
}

//***************************************Fonctions de mise à jour des valeurs***************************************
///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param dessin Prend le dessin du QPainter en paramètre
//!
//! \brief Cette fonction dessine un crayon grâce aux valeurs de son fichier XML.
//!
//! \date 18/01/2014
///////////////////////////////////////////////////////////////////////
void Crayon::dessinerCrayon(QPainter& dessin)
{
    dessin.save();

    if (m_transparence) //S'il y a de la transparence
        dessin.setPen(Qt::black);
    else //Pas de transparence
        dessin.setBrush(Qt::black); //Couleur de la mine

    int epaisseurMine = m_epaisseur/2;
    int hauteurMine = m_hauteurPointe/3;
    //Rotation
    dessin.translate(m_positionX,m_positionY);
    dessin.rotate(m_angle);
    dessin.translate(-m_positionX,-m_positionY);
    //Dessin de la mine
    QPointF pointsMine[3] = {QPointF(m_positionX, m_positionY), QPointF(m_positionX-(epaisseurMine/2), m_positionY+hauteurMine), QPointF(m_positionX+epaisseurMine/2, m_positionY+hauteurMine)}; //Points de la zone transparente
    dessin.drawConvexPolygon(pointsMine, 3); //Dessin de la mine
    //Dessin du reste de la pointe
    dessin.setBrush(QColor(255,203,96)); //Mise en couleur de la pointe
    QPointF pointe[4] = {QPointF(m_positionX-(epaisseurMine/2), m_positionY+hauteurMine), QPointF(m_positionX+epaisseurMine/2, m_positionY+hauteurMine),
                         QPointF(m_positionX+m_epaisseur/2, m_positionY+m_hauteurPointe), QPointF(m_positionX-(m_epaisseur/2), m_positionY+m_hauteurPointe)}; //Points du triangle principal
    dessin.drawConvexPolygon(pointe, 4); //Pointe du crayon
    //Dessin du corps du crayon
    dessin.setBrush(QColor(255,255,49));
    dessin.drawRect(m_positionX-(m_epaisseur/2), m_positionY+m_hauteurPointe, m_epaisseur, m_longueur);
    //Dessin du bouton rotation
    dessin.setBrush(QColor(125,255,255));
    dessin.drawRect(m_positionX-epaisseurMine, m_positionY+250, 2*epaisseurMine, 8*epaisseurMine);
    //Dessin de 2 traits sur le corps
    dessin.drawLine(m_positionX-(m_epaisseur/5),m_positionY+m_hauteurPointe, m_positionX-(m_epaisseur/5),m_positionY+m_hauteurPointe+m_longueur-30);
    dessin.drawLine(m_positionX+m_epaisseur/5,m_positionY+m_hauteurPointe, m_positionX+m_epaisseur/5,m_positionY+m_hauteurPointe+m_longueur-30);
    dessin.restore();
}
