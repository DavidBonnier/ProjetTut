///////////////////////////////////////////////////////////////////////////
//! \file Compas.cpp
//!
//! \brief Mise en place des fonctions servant à modifier le fichier XML suivant la transformation appelée.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include "Compas.h"
#include "Geometrie.h"
#include "projetgeometrie.h"

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \brief Constructeur du compas, initialise toutes les valeurs du fichier XML à 0.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
Compas::Compas(ProjetGeometrie * projetGeometrie)
{
    m_projetGeometrie = projetGeometrie;

    m_nomFichierXML = new QString(":/XML/Resources/XML/Compas.xml");
    m_nomDocument = new QString("Compas");
    m_nomElement = new QString("compas");

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
            //Variable
            if (element.tagName() == "ecartement")
                m_ecartement = element.text().toInt();
            //Constantes
            if (element.tagName() == "hauteurPointe")
                m_hauteurPointe = element.text().toInt();
            if (element.tagName() == "hauteurBase")
                m_hauteurBase = element.text().toInt();
        }
        noeud = noeud.nextSibling(); //Ce code permet d'aller à l'élément suivant.
    }
    xml_doc.close();

    update();
}

Compas::~Compas()
{

}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param ecart Ecartement actuel du compas
//! \param longueurBranche Longueur d'une branche
//!
//! \return Retourne l'angle entre une branche et la droite coupant le compas en deux verticalement.
//!
//! \brief Calcul à l'aide des propriétés des triangles, l'angle entre une branche et la droite coupant le compas en deux verticalement pour permettre la rotation des branches
//!
//! \date 18/01/2014
///////////////////////////////////////////////////////////////////////
double Compas::angleEcartement(double ecart, double longueurBranche) //Retourne l'écartement entre une branche et la droite milieue
{
    double teta = (ecart/2)/longueurBranche; //sin(teta) = (ecart/2)/(longueurBranche)
    teta = asin(teta); //sin-1(teta) en radian
    teta *= 180/M_PI; //Conversion en degrés
    return teta;
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param ecart Ecartement actuel du compas
//! \param longueurBranche Longueur d'une branche
//!
//! \return Retourne la hauteur entre le bas du compas et le centre de la base
//!
//! \brief Calcul la hauteur entre le bas du compas et la base grâce à Pythagore pour permettre d'ajuster la hauteur de la base.
//!
//! \date 18/01/2014
///////////////////////////////////////////////////////////////////////
int Compas::hauteurCompas(double ecart, int longueurBranche)
{
    return sqrt((longueurBranche*longueurBranche)-((ecart/2)*(ecart/2))); //Pythagore
}

//***************************************Fonctions de mise à jour des valeurs***************************************
///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param e Nouvel écartement du compas
//!
//! \brief Cette fonction met à jour le fichier XML du compas avec le nouvel écartement du compas
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Compas::setEcartement(double ecartement)
{
    m_ecartement = ecartement;
    m_projetGeometrie->ui.SpinBoxCompasEcartement->setValue(ecartement);
    update();
}


void Compas::setTransparence(bool transparence)
{
    Instrument::setTransparence(transparence);
    m_projetGeometrie->ui.CheckBoxCompasTransparence->setChecked(transparence);
}

void Compas::translation(double positionX , double positionY)
{
    Instrument::translation(positionX,positionY);
    m_projetGeometrie->ui.SpinBoxCompasPositionX->setValue(positionX);
    m_projetGeometrie->ui.SpinBoxCompasPositionY->setValue(positionY);
}

void Compas::setAngle(double angle)
{
    Instrument::setAngle(angle);
    m_projetGeometrie->ui.SpinBoxCompasOrientation->setValue(angle);
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param dessin Prend le dessin du QPainter en paramètres
//!
//! \brief Cette fonction dessine un compas grâce aux valeurs de son fichier XML.
//!
//! \date 19/01/2014
///////////////////////////////////////////////////////////////////////
void Compas::paint(QPainter * dessin, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    dessin->save();

    //Rotation
    dessin->translate(x(),y());
    dessin->translate(-x(),-y());
//Dessin de la branche avec pointe
    double teta = angleEcartement(m_ecartement, m_longueur+m_hauteurPointe);
    dessin->save();
    //Rotation de la tige
    dessin->translate(x(),y());
    dessin->rotate(-teta);
    dessin->translate(-x(),-y());
    //Dessin
    dessin->setPen(Qt::black);
    QPointF pointe[3] = {QPointF(x(),y()), QPointF(x(), y()+m_hauteurPointe), QPointF(x()-m_largeur/2, y()+m_hauteurPointe)}; //Points de la pointe
    dessin->drawConvexPolygon(pointe, 3); //Dessin de la pointe
    dessin->setBrush(Qt::gray);
    dessin->drawRect(x()-m_largeur, y()+m_hauteurPointe, m_largeur, m_longueur); //Branche avec pointe
    dessin->restore();

//Dessin de la branche avec mine
    dessin->save();
    //Rotation de la tige
    dessin->translate(x()+m_ecartement,y());
    dessin->rotate(teta);
    dessin->translate(-x() -m_ecartement,-y());
    //Dessin
    dessin->setBrush(Qt::black);
    QPointF mine[4] = {QPointF(x()+m_ecartement,y()), QPointF(x()+m_ecartement, y()+m_hauteurPointe),
                      QPointF(x()+m_largeur/2+m_ecartement, y()+m_hauteurPointe), QPointF(x()+m_largeur/3+m_ecartement, y()+m_hauteurPointe/3)}; //Points de la mine
    dessin->drawConvexPolygon(mine, 4); //Dessin de la mine
    dessin->setBrush(Qt::gray);
    dessin->drawRect(x()+m_ecartement, y()+m_hauteurPointe, m_largeur, m_longueur); //Branche avec mine
    dessin->restore();

//Dessin du centre
    dessin->setBrush(Qt::blue);
    int hauteurcentre = hauteurCompas(m_ecartement, m_longueur);
    dessin->drawRect(x()+(m_ecartement/2)-m_largeur, y()+hauteurcentre, 2*m_largeur, m_hauteurBase); //Base du compas
    dessin->drawRect(x()+(m_ecartement/2)-m_largeur/2, y()+hauteurcentre+m_hauteurBase, m_largeur, m_hauteurBase/2); //Bout du compas
    //Dessin du bouton de rotation;
    dessin->setBrush(QColor(124,255,255));
    dessin->drawRect(x()+(m_ecartement/2)-m_largeur/2, y()+hauteurcentre+m_hauteurBase, m_largeur, m_hauteurBase/2);

//Dessin de la vis
    //Rotation
    dessin->save();
    dessin->translate(x()+(m_ecartement/2), y()+hauteurcentre+5*m_hauteurBase/8);
    dessin->rotate(teta/2);
    dessin->translate(-x()-(m_ecartement/2), -y()-hauteurcentre-5*m_hauteurBase/8);
    //Dessin
    dessin->setBrush(Qt::gray);
    dessin->drawEllipse(x()+(m_ecartement/2)-m_largeur/2, y()+hauteurcentre+m_hauteurBase/2, m_largeur, m_largeur); //Cercle
    dessin->drawLine(x()+(m_ecartement/2), y()+hauteurcentre+m_hauteurBase/2, x()+(m_ecartement/2), y()+hauteurcentre+3*m_hauteurBase/4); //Trait vertical
    dessin->drawLine(x()+(m_ecartement/2)-m_largeur/2, y()+hauteurcentre+5*m_hauteurBase/8, x()+(m_ecartement/2)+m_largeur/2, y()+hauteurcentre+5*m_hauteurBase/8); //Trait horizontal
    dessin->restore();
    dessin->restore();
}
