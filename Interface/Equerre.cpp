///////////////////////////////////////////////////////////////////////////
//! \file Equerre.cpp
//!
//! \brief Mise en place des fonctions servant à modifier le fichier XML suivant la transformation appelée.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include "Equerre.h"
#include "Geometrie.h"
#include "projetgeometrie.h"
#include "qmath.h"
#include <QDebug>

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \brief Constructeur de l'équerre, initialise toutes les valeurs du fichier XML à 0.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
Equerre::Equerre(Geometrie * geometrie)
{
    m_nomFichierXML = new QString(":/Instrument/Resources/XML/Equerre.xml");
    m_nomDocument = new QString("Equerre");
    m_nomElement = new QString("equerre");

    m_geometrie = geometrie;

    InitialisationRegle();

    update();
}


Equerre::~Equerre()
{

}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param longueur Longueur de l'équerre
//! \param largeur Largeur de l'équerre
//! \param transp Hauteur de la zone transparente
//! \param x Position en x de l'équerre
//! \param y Position en y de l'équerre
//!
//! \return Retourne le point situé sur l'hypotenuse et la zone délimitant la transparence.
//!
//! \brief Calcul le point situé sur l'hypotenuse et la zone délimitant la transparence à l'aide de Thalès.
//!
//! \date 17/01/2014
///////////////////////////////////////////////////////////////////////
QPointF Equerre::Thales(double longueur, double largeur, double transp, int x, int y)
{
    double longueurTransp =  longueur*( (largeur-transp)/largeur); //Calcul de la longueur du segment délimitant la transparence
    return QPointF(x+longueurTransp, y+transp); //Retourne les coordonnée du point de l'intersection de ce segment avec l'hypoténuse
}

void Equerre::setTransparence(bool transparence)
{
    Instrument::setTransparence(transparence);
    m_geometrie->m_projetGeometrie->ui.CheckBoxEquerreTransparence->setChecked(transparence);
}

void Equerre::translation(double positionX , double positionY)
{
    Instrument::translation(positionX,positionY);
    m_geometrie->m_projetGeometrie->ui.SpinBoxEquerrePositionX->setValue(positionX);
    m_geometrie->m_projetGeometrie->ui.SpinBoxEquerrePositionY->setValue(positionY);
}

void Equerre::setAngle(double angle)
{
    Instrument::setAngle(angle);
    m_geometrie->m_projetGeometrie->ui.SpinBoxEquerreOrientation->setValue(angle);
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param dessin Prend le dessin du QPainter en paramètre
//!
//! \brief Cette fonction dessine une équerre grâce aux valeurs de son fichier XML.
//!
//! \date 17/01/2014
///////////////////////////////////////////////////////////////////////
void Equerre::dessinerEquerre(QPainter& dessin)
{
    dessin.save();

    int hauteurZoneTransp = m_largeur/7;

    if (m_transparence) //S'il y a de la transparence
        dessin.setPen(Qt::black);
    else //Pas de transparence
        dessin.setBrush(QColor(255,255,152)); //Couleur du petit rectangle

    //Rotation
    dessin.translate(m_position.x(),m_position.y());
    dessin.rotate(m_angle);
    dessin.translate(-m_position.x(),-m_position.y());
    //Dessin de la zone transparente
    QPointF pointHyp = Thales(m_longueur, m_largeur, hauteurZoneTransp, m_position.x(), m_position.y());
    QPointF pointsZoneTranparent[4] = {QPointF(m_position.x(), m_position.y()), QPointF(m_position.x()+m_longueur, m_position.y()), pointHyp, QPointF(m_position.x(), m_position.y()+hauteurZoneTransp)}; //Points de la zone transparente
    dessin.drawConvexPolygon(pointsZoneTranparent, 4); //Dessin de la zone transparente
    //Dessin de la zone principale
    dessin.setBrush(QColor(255,255,50)); //Mise en couleur de la partie principale de l'equerre
    QPointF triangle[3] = {pointHyp, QPointF(m_position.x(), m_position.y()+hauteurZoneTransp), QPointF(m_position.x(), m_position.y()+m_largeur)}; //Points du triangle principal
    dessin.drawConvexPolygon(triangle, 3); //Triangle principal
    //Dessin du bouton rotation
    dessin.setBrush(QColor(126,255,255));
    dessin.drawEllipse(QPointF(m_position.x()+250,m_position.y()+50),15,15);
    //Dessin des graduations
    dessin.setFont(QFont("Arial", 8)); //Police et taille des charactères
    int chiffre = 0; //Chiffre actuel sur l'équerre
    QString grad[] = {"0","1","2","3","4","5","6","7"}; //Chiffres sur l'équerre
    int hauteurMaxGrad = hauteurZoneTransp/2;
    for (int i=0 ; i<m_longueur ; i+=m_graduation*5) //5 pixels entre chaque graduations
    {
        if (i%50 == 0) //Graduation cm
        {
            dessin.drawLine(m_position.x()+i,m_position.y(), m_position.x()+i,m_position.y()+hauteurMaxGrad);
            dessin.drawText(m_position.x()+2+i, m_position.y()-3+m_largeur/8, grad[chiffre]); //Affichage des chiffres
            chiffre++;
        }
        else if (i%25 == 0) //Graduation 1/2 cm
            dessin.drawLine(m_position.x()+i,m_position.y(), m_position.x()+i,m_position.y()+hauteurMaxGrad/2);
        else //Graduation mm
            dessin.drawLine(m_position.x()+i,m_position.y(), m_position.x()+i,m_position.y()+hauteurMaxGrad/4);
    }
    dessin.restore();
}

void Equerre ::  MagnetiserEquerre (QList <Figure *> tableauFigure)
{
    const int TxMagnetAng =45;
    const int TxMagnetDist =45;

    //recherche des valeurs du XML------------------------------------------------------------
    QDomDocument dom("Equerre"); // Création de l'objet DOM
    QFile xml_doc(":/Instrument/Resources/XML/Equerre.xml"); // On choisit le fichier contenant les informations XML.
    if(!xml_doc.open(QIODevice::ReadOnly)) // Si l'on n'arrive pas à ouvrir le fichier XML.
    {
            QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre ouvert. Verifiez que le nom est le bon et que le document est bien place");
            return;
    }
    if (!dom.setContent(&xml_doc)) // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.
    {
            xml_doc.close();
            QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre attribue a l'objet QDomDocument.");
            return;
    }
    QDomElement dom_element = dom.documentElement();
    QDomNode noeud = dom_element.firstChild();
    int w, h;
    while(!noeud.isNull()) //Parours du fichier
    {
        QDomElement element = noeud.toElement(); // On utilise cette propriété afin de transformer le nœud en éléments.
                                                    //Cela nous permet aussi de récupérer l'élément ou nœud courant.
        if(!element.isNull()) //S'il y a un élément dans le noeud
        {
            /*
            if (element.tagName() == "positionX")
                x = element.text().toInt();
            if (element.tagName() == "positionY")
                y = element.text().toInt();
                */
            if (element.tagName() == "longueur")
                w = element.text().toInt();
            if (element.tagName() == "largeur")
                h = element.text().toInt();
            /*
            if (element.tagName() == "rotation")
                rotation = element.text().toDouble();
            if (element.tagName() == "graduation")
                graduation = element.text().toInt();
                */
        }
        noeud = noeud.nextSibling(); //Ce code permet d'aller à l'élément suivant.
    }
    xml_doc.close();
    //fin recherche---------------------------------------------------------------------------
    QLine droitesOutilCourant [2];
    int x = m_position.x();
    int y = m_position.y();
    double rotation[2] = {m_angle,m_angle -90};
    // Détection des bords de l'instrument à magnétiser ici l'equerre
    droitesOutilCourant[0].setLine(x,y,w*cos(rotation[0]*M_PI/180) + x,w*sin(rotation[0]*M_PI/180) + y);
    if(rotation[1]<0) rotation[1] +=360;

    droitesOutilCourant[1].setLine(x,y,h*cos(rotation[1]*M_PI/180) + x,h*sin(rotation[1]*M_PI/180) + y);

    bool magnet = false;
    double BestAngle=99999;
    double BestDist=99999;

    QPoint NewCoord;
    double NewAngle;

    QPoint PointMagnetise;
    QLine DroiteMagnetise;

    //parcour des droite à vérifier le magnétisme(celles de l'outil)
    for ( int i = 0 ; i<=1 ; ++i)
    {
        //vecteur de la droite courante de l'outil
        QVector2D VecteurO (droitesOutilCourant[i].x1()-droitesOutilCourant[i].x2(),droitesOutilCourant[i].y1()-droitesOutilCourant[i].y2());

        //Parcours des droites aux quelles on peut se magnétiser
        for (int j=0 ; j<tableauFigure.size(); ++j)//A changer si list
        {
            Ligne* DroiteCourante = dynamic_cast<Ligne*>(tableauFigure[j]);//Changement?
            if(DroiteCourante!=NULL)
            {
                double angletemp;
                //vecteur de la droite courante
                QVector2D VecteurCourant  (DroiteCourante->getQLine().x1()-DroiteCourante->getQLine().x2(),DroiteCourante->getQLine().y1()-DroiteCourante->getQLine().y2());
                //angle entre les deux droites
                angletemp = 180* qAcos ((VecteurO.x()*VecteurCourant.x() + VecteurO.y()*VecteurCourant.y())/(sqrt(VecteurO.x()*VecteurO.x() + VecteurO.y()*VecteurO.y()) * sqrt(VecteurCourant.x()*VecteurCourant.x() + VecteurCourant.y()*VecteurCourant.y())))/M_PI;
                if (abs(angletemp) < TxMagnetAng || abs(angletemp)-180 < TxMagnetAng )
                {
                    //détermination de a et b dans y=ax+b : équation de la droiteCourante
                    double LESY = DroiteCourante->getQLine().y2()-DroiteCourante->getQLine().y1();
                    double LESX = DroiteCourante->getQLine().x2()-DroiteCourante->getQLine().x1();
                    double a = LESY/LESX;
                    double b = DroiteCourante->getQLine().y1() - a * DroiteCourante->getQLine().x1();

                    double d = abs(a*droitesOutilCourant[i].x1() - droitesOutilCourant[i].y1() + b)/sqrt(a*a +1);
                    if (BestDist + BestAngle > d+angletemp && d<TxMagnetDist)
                    {
                        //projection orthogonale sur la droite courante (pas le segment)
                        QVector2D BA (droitesOutilCourant[i].x1()-DroiteCourante->getQLine().x1(),droitesOutilCourant[i].y1()-DroiteCourante->getQLine().y1());
                        VecteurCourant.normalize();
                        QVector2D BH = (BA.x()*VecteurCourant.x() + BA.y() * VecteurCourant.y())*VecteurCourant;

                        QPoint Coordtemp  (DroiteCourante->getQLine().x1()+BH.x(),DroiteCourante->getQLine().y1()+BH.y());
                        //tri des X et des Y des coord de la regle pour vérifier que le nouveau point est bien sur la regle(->le segment)
                        int bas = qMin(DroiteCourante->getQLine().x1(),DroiteCourante->getQLine().x2());
                        int haut = qMax(DroiteCourante->getQLine().x1(),DroiteCourante->getQLine().x2());

                        if( Coordtemp.x() >= bas && Coordtemp.x() <= haut)
                        {
                            bas  = qMin(DroiteCourante->getQLine().y1(),DroiteCourante->getQLine().y2());
                            haut = qMax(DroiteCourante->getQLine().y1(),DroiteCourante->getQLine().y2());

                            if( Coordtemp.y() >= bas && Coordtemp.y()<= haut)
                            {
                                BestDist =d;
                                BestAngle = angletemp;
                                magnet = true;

                                NewCoord = Coordtemp;
                                NewAngle=angletemp;
                            }
                        }

                    }
                    //test à partir de l'autre bout de l'équerre
                    d = abs(a*droitesOutilCourant[i].x2() - droitesOutilCourant[i].y2() + b)/sqrt(a*a +1);
                    if (BestDist + BestAngle > d+angletemp && d<TxMagnetDist)
                    {
                        //projection orthogonale sur la droite courante (pas le segment)
                        QVector2D BA (droitesOutilCourant[i].x2()-DroiteCourante->getQLine().x1(),droitesOutilCourant[i].y2()-DroiteCourante->getQLine().y1());
                        VecteurCourant.normalize();
                        QVector2D BH = (BA.x()*VecteurCourant.x() + BA.y() * VecteurCourant.y())*VecteurCourant;

                        QPoint Coordtemp  (DroiteCourante->getQLine().x1()+BH.x(),DroiteCourante->getQLine().y1()+BH.y());
                        //tri des X et des Y des coord de la regle pour vérifier que le nouveau point est bien sur la regle(->le segment)
                        int bas = qMin(DroiteCourante->getQLine().x1(),DroiteCourante->getQLine().x2());
                        int haut = qMax(DroiteCourante->getQLine().x1(),DroiteCourante->getQLine().x2());

                        if( Coordtemp.x() >= bas && Coordtemp.x() <= haut)
                        {
                            bas  = qMin(DroiteCourante->getQLine().y1(),DroiteCourante->getQLine().y2());
                            haut = qMax(DroiteCourante->getQLine().y1(),DroiteCourante->getQLine().y2());

                            if( Coordtemp.y() >= bas && Coordtemp.y()<= haut)
                            {
                                BestDist =d;
                                BestAngle = angletemp;
                                magnet = true;

                                NewCoord = Coordtemp;
                                NewCoord.setX(NewCoord.x()+VecteurO.x());
                                NewCoord.setY(NewCoord.y()+VecteurO.y());
                                NewAngle=angletemp;
                            }
                        }
                    }



                }
            }
        }
        //on a l'equerre nous regardons donc le magnétisme avec la regle
        if (m_geometrie->regle)
        {
            //Lecture Regle
            QDomDocument dom("Regle"); // Création de l'objet DOM
            QFile xml_doc(":/Instrument/Resources/XML/Regle.xml"); // On choisit le fichier contenant les informations XML.
            if(!xml_doc.open(QIODevice::ReadOnly)) // Si l'on n'arrive pas à ouvrir le fichier XML.
            {
                    QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre ouvert. Verifiez que le nom est le bon et que le document est bien place");
                    return;
            }
            if (!dom.setContent(&xml_doc)) // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.
            {
                    xml_doc.close();
                    QMessageBox::warning(this,"Erreur a l'ouverture du document XML","Le document XML n'a pas pu etre attribue a l'objet QDomDocument.");
                    return;
            }
            QDomElement dom_element = dom.documentElement();
            QDomNode noeud = dom_element.firstChild();
            int Xregle,Yregle, Wregle, Hregle;
            Xregle= m_geometrie->regle->getPositionX();
            Yregle= m_geometrie->regle->getPositionY();
            double Rotationregle = m_geometrie->regle->getAngle();
            while(!noeud.isNull()) //Parours du fichier
            {
                QDomElement element = noeud.toElement(); // On utilise cette propriété afin de transformer le nœud en éléments.
                                                            //Cela nous permet aussi de récupérer l'élément ou nœud courant.
                if(!element.isNull()) //S'il y a un élément dans le noeud
                {
                    /*
                    if (element.tagName() == "positionX")
                        Xregle = element.text().toInt();
                    if (element.tagName() == "positionY")
                        Yregle = element.text().toInt();*/
                    if (element.tagName() == "longueur")
                        Wregle = element.text().toInt();
                    if (element.tagName() == "largeur")
                        Hregle = element.text().toInt();
                    /*if (element.tagName() == "rotation")
                        Rotationregle = element.text().toDouble();	*/
                }
                noeud = noeud.nextSibling(); //Ce code permet d'aller à l'élément suivant.
            }
            xml_doc.close();
            //Vecteur de la droite de la regle
            QLine DroiteCourante;
            DroiteCourante.setLine(Xregle,Yregle,Xregle+ Wregle*cos(Rotationregle*M_PI/180),Yregle+ Wregle*sin(Rotationregle*M_PI/180));

            QVector2D VecteurCourant (DroiteCourante.x2()-DroiteCourante.x1(),DroiteCourante.y2()-DroiteCourante.y1());

            double angletemp;

            //angle entre les deux droites
            //angletemp = qAcos ((VecteurO.x()*VecteurCourant.x()+VecteurO.y()*VecteurCourant.y())/(sqrt(VecteurO.x()*VecteurO.x() + VecteurO.y()*VecteurO.y()) * sqrt(VecteurCourant.x()*VecteurCourant.x() + VecteurCourant.y()*VecteurCourant.y())));
            //angletemp = abs(abs(Rotationregle - angle)-180);
            angletemp = Rotationregle - rotation[i];
            if (angletemp>0) angletemp-=180;
            else angletemp+=180;
            if (abs (angletemp )< TxMagnetAng )
            {
                //détermination de a et b dans y=ax+b : équation de la droiteCourante
                double LESY = DroiteCourante.y2()-DroiteCourante.y1();
                double LESX = DroiteCourante.x2()-DroiteCourante.x1();
                double a = LESY/LESX;
                double b = DroiteCourante.y1() - a * DroiteCourante.x1();

                double d = abs(a*droitesOutilCourant[i].x1() - droitesOutilCourant[i].y1() + b)/sqrt(a*a +1);
                if (d<TxMagnetDist && BestDist + BestAngle > d+angletemp )
                {
                    //projection orthogonale sur la droite courante (pas le segment)
                    QVector2D BA (droitesOutilCourant[i].x1()-DroiteCourante.x1(),droitesOutilCourant[i].y1()-DroiteCourante.y1());
                    VecteurCourant.normalize();
                    QVector2D BH = (BA.x()*VecteurCourant.x() + BA.y() * VecteurCourant.y())*VecteurCourant;

                    QPoint Coordtemp  (DroiteCourante.x1()+BH.x(),DroiteCourante.y1()+BH.y());
                    //tri des X et des Y des coord de la regle pour vérifier que le nouveau point est bien sur la regle(->le segment)
                    int bas = qMin(DroiteCourante.x1(),DroiteCourante.x2());
                    int haut = qMax(DroiteCourante.x1(),DroiteCourante.x2());

                    if( Coordtemp.x() >= bas && Coordtemp.x() <= haut)
                    {
                        bas  = qMin(DroiteCourante.y1(),DroiteCourante.y2());
                        haut = qMax(DroiteCourante.y1(),DroiteCourante.y2());

                        if( Coordtemp.y() >= bas && Coordtemp.y()<= haut)
                        {
                            BestDist =d;
                            BestAngle = angletemp;
                            magnet = true;

                            NewCoord = Coordtemp;
                            NewAngle=angletemp;
                        }
                    }

                }
                //test à partir de l'autre bout de l'équerre
                d = abs(a*droitesOutilCourant[i].x2() - droitesOutilCourant[i].y2() + b)/sqrt(a*a +1);
                if (BestDist + BestAngle > d+angletemp && d<TxMagnetDist)
                {
                    //projection orthogonale sur la droite courante (pas le segment)
                    QVector2D BA (droitesOutilCourant[i].x2()-DroiteCourante.x1(),droitesOutilCourant[i].y2()-DroiteCourante.y1());
                    VecteurCourant.normalize();
                    QVector2D BH = (BA.x()*VecteurCourant.x() + BA.y() * VecteurCourant.y())*VecteurCourant;

                    QPoint Coordtemp  (DroiteCourante.x1()+BH.x(),DroiteCourante.y1()+BH.y());
                    //tri des X et des Y des coord de la regle pour vérifier que le nouveau point est bien sur la regle(->le segment)
                    int bas = qMin(DroiteCourante.x1(),DroiteCourante.x2());
                    int haut = qMax(DroiteCourante.x1(),DroiteCourante.x2());

                    if( Coordtemp.x() >= bas && Coordtemp.x() <= haut)
                    {
                        bas  = qMin(DroiteCourante.y1(),DroiteCourante.y2());
                        haut = qMax(DroiteCourante.y1(),DroiteCourante.y2());

                        if( Coordtemp.y() >= bas && Coordtemp.y() <= haut)
                        {
                            BestDist =d;
                            BestAngle = angletemp;
                            magnet = true;

                            NewCoord = Coordtemp;
                            NewCoord.setX(NewCoord.x()+VecteurO.x());
                            NewCoord.setY(NewCoord.y()+VecteurO.y());
                            NewAngle=angletemp;
                        }
                    }
                }
            }
        }
    }

    if (magnet)//Ecrire
    {
        m_position.setX(NewCoord.x());
        m_position.setY(NewCoord.y());
        m_angle += NewAngle;
    }
}

