///////////////////////////////////////////////////////////////////////////
//! \file Compas.cpp
//!
//! \brief Mise en place des fonctions servant à modifier le fichier XML suivant la transformation appelée.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include "Compas.h"
#include "Geometrie.h"

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \brief Constructeur du compas, initialise toutes les valeurs du fichier XML à 0.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
Compas::Compas(Geometrie * geometrie)
{
    m_pointGeometrie = geometrie;

    m_nomFichierXML = new QString("Compas.xml");
    m_nomDocument = new QString("Compas");
    m_nomElement = new QString("compas");

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
    const double PI = 3.1415926;
    double teta = (ecart/2)/longueurBranche; //sin(teta) = (ecart/2)/(longueurBranche)
    teta = asin(teta); //sin-1(teta) en radian
    teta *= 180/PI; //Conversion en degrés
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

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param dessin Dessin du painter
//! \param x Position en x du compas
//! \param y Position en y du compas
//! \param ecart Ecartement du compas
//!
//! \brief Cette fonction met à jour le fichier XML du compas avec le nouvel écartement du compas
//!
//! \date 02/02/2014
///////////////////////////////////////////////////////////////////////
void Compas :: tracer ()
{

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
    update();
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
void Compas::dessinerCompas(QPainter& dessin)
{
    dessin.save();

    //Rotation
    dessin.translate(m_positionX,m_positionY);
    dessin.rotate(m_angle);
    dessin.translate(-m_positionX,-m_positionY);
//Dessin de la branche avec pointe
    double teta = angleEcartement(m_ecartement, m_longueur+m_hauteurPointe);
    dessin.save();
    //Rotation de la tige
    dessin.translate(m_positionX,m_positionY);
    dessin.rotate(-teta);
    dessin.translate(-m_positionX,-m_positionY);
    //Dessin
    dessin.setPen(Qt::black);
    QPointF pointe[3] = {QPointF(m_positionX,m_positionY), QPointF(m_positionX, m_positionY+m_hauteurPointe), QPointF(m_positionX-m_largeur/2, m_positionY+m_hauteurPointe)}; //Points de la pointe
    dessin.drawConvexPolygon(pointe, 3); //Dessin de la pointe
    dessin.setBrush(Qt::gray);
    dessin.drawRect(m_positionX-m_largeur, m_positionY+m_hauteurPointe, m_largeur, m_longueur); //Branche avec pointe
    dessin.restore();

//Dessin de la branche avec mine
    dessin.save();
    //Rotation de la tige
    dessin.translate(m_positionX+m_ecartement,m_positionY);
    dessin.rotate(teta);
    dessin.translate(-m_positionX -m_ecartement,-m_positionY);
    //Dessin
    dessin.setBrush(Qt::black);
    QPointF mine[4] = {QPointF(m_positionX+m_ecartement,m_positionY), QPointF(m_positionX+m_ecartement, m_positionY+m_hauteurPointe),
                      QPointF(m_positionX+m_largeur/2+m_ecartement, m_positionY+m_hauteurPointe), QPointF(m_positionX+m_largeur/3+m_ecartement, m_positionY+m_hauteurPointe/3)}; //Points de la mine
    dessin.drawConvexPolygon(mine, 4); //Dessin de la mine
    dessin.setBrush(Qt::gray);
    dessin.drawRect(m_positionX+m_ecartement, m_positionY+m_hauteurPointe, m_largeur, m_longueur); //Branche avec mine
    dessin.restore();

//Dessin du centre
    dessin.setBrush(Qt::blue);
    int hauteurcentre = hauteurCompas(m_ecartement, m_longueur);
    dessin.drawRect(m_positionX+(m_ecartement/2)-m_largeur, m_positionY+hauteurcentre, 2*m_largeur, m_hauteurBase); //Base du compas
    dessin.drawRect(m_positionX+(m_ecartement/2)-m_largeur/2, m_positionY+hauteurcentre+m_hauteurBase, m_largeur, m_hauteurBase/2); //Bout du compas
    //Dessin du bouton de rotation;
    dessin.setBrush(QColor(124,255,255));
    dessin.drawRect(m_positionX+(m_ecartement/2)-m_largeur/2, m_positionY+hauteurcentre+m_hauteurBase, m_largeur, m_hauteurBase/2);

//Dessin de la vis
    //Rotation
    dessin.save();
    dessin.translate(m_positionX+(m_ecartement/2), m_positionY+hauteurcentre+5*m_hauteurBase/8);
    dessin.rotate(teta/2);
    dessin.translate(-m_positionX-(m_ecartement/2), -m_positionY-hauteurcentre-5*m_hauteurBase/8);
    //Dessin
    dessin.setBrush(Qt::gray);
    dessin.drawEllipse(m_positionX+(m_ecartement/2)-m_largeur/2, m_positionY+hauteurcentre+m_hauteurBase/2, m_largeur, m_largeur); //Cercle
    dessin.drawLine(m_positionX+(m_ecartement/2), m_positionY+hauteurcentre+m_hauteurBase/2, m_positionX+(m_ecartement/2), m_positionY+hauteurcentre+3*m_hauteurBase/4); //Trait vertical
    dessin.drawLine(m_positionX+(m_ecartement/2)-m_largeur/2, m_positionY+hauteurcentre+5*m_hauteurBase/8, m_positionX+(m_ecartement/2)+m_largeur/2, m_positionY+hauteurcentre+5*m_hauteurBase/8); //Trait horizontal
    dessin.restore();
    dessin.restore();
}
