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

void Regle ::  MagnetiserRegle (QList <Figure *> tableauFigure)
{	
	if(m_geometrie->magne_actif)
	{
		//recherche des valeurs du XML------------------------------------------------------------
		QDomDocument dom("Regle"); // Création de l'objet DOM
		QFile xml_doc("Resources/XML/Regle.xml"); // On choisit le fichier contenant les informations XML.
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
		QLine droitesOutilCourant;
		int x = m_position.x();
		int y = m_position.y();
		double rotation = m_angle;
		// Détection des bords de l'instrument à magnétiser ici l'equerre
		droitesOutilCourant.setLine(x,y,w*cos(rotation*PI/180) + x,w*sin(rotation*PI/180) + y);
		QPoint Point3 ((w/2)*cos(rotation*PI/180) + x,(w/2)*sin(rotation*PI/180) + y);
		if(rotation<0) rotation +=360;

		bool magnet = false;
		double BestAngle=99999;
		double BestDist=99999;

		QPoint NewCoord;
		double NewAngle;

		QPoint PointMagnetise;
		QLine DroiteMagnetise;

		//vecteur de la droite courante de l'outil
		QVector2D VecteurO (droitesOutilCourant.x1()-droitesOutilCourant.x2(),droitesOutilCourant.y1()-droitesOutilCourant.y2());

		//Parcours des droites aux quelles on peut se magnétiser
		for (int j=0 ; j<tableauFigure.size(); ++j)//A changer si list
		{
			Ligne* DroiteCourante = dynamic_cast<Ligne*>(tableauFigure[j]);//Changement?
			if(DroiteCourante!=NULL)
			{
				double angletemp;
				//vecteur de la droite courante
				QVector2D VecteurCourant  (DroiteCourante->getQLine().x1()-DroiteCourante->getQLine().x2(),DroiteCourante->getQLine().y1()-DroiteCourante->getQLine().y2());

				if (VecteurCourant.y()<0) VecteurCourant=-VecteurCourant;
				//angle entre les deux droites
				/*double COSSIN = (VecteurO.x()*VecteurCourant.x() + VecteurO.y()*VecteurCourant.y())/(sqrt(VecteurO.x()*VecteurO.x() + VecteurO.y()*VecteurO.y()) * sqrt(VecteurCourant.x()*VecteurCourant.x() + VecteurCourant.y()*VecteurCourant.y()));
				angletemp =  180*qAcos (COSSIN)/PI *qAsin(COSSIN)/abs(qAsin(COSSIN));*/


				double angleCourant = 180*qAcos(VecteurCourant.x()/(1 * sqrt(VecteurCourant.x()*VecteurCourant.x() + VecteurCourant.y()*VecteurCourant.y())))/PI;
				angletemp = angleCourant - rotation;

				if (abs(angletemp) < m_geometrie->m_txMagnetAng || abs(abs(angletemp)-180 )< m_geometrie->m_txMagnetAng )
				{
					//détermination de a et b dans y=ax+b : équation de la droiteCourante
					double LESY = DroiteCourante->getQLine().y2()-DroiteCourante->getQLine().y1();
					double LESX = DroiteCourante->getQLine().x2()-DroiteCourante->getQLine().x1();
					double d;
					if (LESX == 0) d=abs(droitesOutilCourant.x1()-DroiteCourante->getQLine() .x1());
					else
					{
						double a = LESY/LESX;
						double b = DroiteCourante->getQLine() .y1() - a * DroiteCourante->getQLine() .x1();

						d = abs(a*droitesOutilCourant.x1() - droitesOutilCourant.y1() + b)/sqrt(a*a +1);
					}
					if (BestDist + BestAngle > d+angletemp && d<m_geometrie->m_txMagnetDist)
					{
						//projection orthogonale sur la droite courante (pas le segment)
						QVector2D BA (droitesOutilCourant.x1()-DroiteCourante->getQLine().x1(),droitesOutilCourant.y1()-DroiteCourante->getQLine().y1());
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
								if (angletemp<0)
								{
									if (abs(angletemp)<m_geometrie->m_txMagnetAng)NewAngle=angletemp;
									else NewAngle= angletemp+180;
								}
								else 
								{
									if (angletemp<m_geometrie->m_txMagnetAng)NewAngle=angletemp;
									else NewAngle= angletemp-180;
								}

							}
						} 

					}
					//test à partir de l'autre bout de la regle
					if (LESX == 0) d=abs(droitesOutilCourant.x2()-DroiteCourante->getQLine() .x1());
					else
					{
						double a = LESY/LESX;
						double b = DroiteCourante->getQLine() .y1() - a * DroiteCourante->getQLine() .x1();

						d = abs(a*droitesOutilCourant.x2() - droitesOutilCourant.y2() + b)/sqrt(a*a +1);
					}
				
					if (BestDist + BestAngle > d+angletemp && d<m_geometrie->m_txMagnetDist)
					{
						//projection orthogonale sur la droite courante (pas le segment)
						QVector2D BA (droitesOutilCourant.x2()-DroiteCourante->getQLine().x1(),droitesOutilCourant.y2()-DroiteCourante->getQLine().y1());
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
								if (angletemp<0)
								{
									if (abs(angletemp)<m_geometrie->m_txMagnetAng)NewAngle=angletemp;
									else NewAngle= angletemp+180;
								}
								else 
								{
									if (angletemp<m_geometrie->m_txMagnetAng)NewAngle=angletemp;
									else NewAngle= angletemp-180;
								}
							}
						}
					}
					//test à partir du milieu de la regle
					if (LESX == 0) d=abs(Point3.x()-DroiteCourante->getQLine() .x1());
					else
					{
						double a = LESY/LESX;
						double b = DroiteCourante->getQLine() .y1() - a * DroiteCourante->getQLine() .x1();

						d = abs(a*Point3.x() - Point3.y() + b)/sqrt(a*a +1);
					}
				
					if (BestDist + BestAngle > d+angletemp && d<m_geometrie->m_txMagnetDist)
					{
						//projection orthogonale sur la droite courante (pas le segment)
						QVector2D BA (Point3.x()-DroiteCourante->getQLine().x1(),Point3.y()-DroiteCourante->getQLine().y1());
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
								NewCoord.setX(NewCoord.x()+VecteurO.x()/2);
								NewCoord.setY(NewCoord.y()+VecteurO.y()/2);
								if (angletemp<0)
								{
									if (abs(angletemp)<m_geometrie->m_txMagnetAng)NewAngle=angletemp;
									else NewAngle= angletemp+180;
								}
								else 
								{
									if (angletemp<m_geometrie->m_txMagnetAng)NewAngle=angletemp;
									else NewAngle= angletemp-180;
								}
							}
						}
					}
				}
			}
		}
		//on a la regle nous regardons donc le magnétisme avec l'equerre
		if (m_geometrie->equerre)
		{
			//Lecture equerre
			QDomDocument dom("Equerre"); // Création de l'objet DOM
			QFile xml_doc("Resources/XML/Equerre.xml"); // On choisit le fichier contenant les informations XML.
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
			int Xequerre,Yequerre, Wequerre, Hequerre;
			Xequerre= m_geometrie->equerre->getPositionX();
			Yequerre= m_geometrie->equerre->getPositionY();
			double Rotationequerre[2] = {m_geometrie->equerre->getAngle(),m_geometrie->equerre->getAngle()+90};
			if (Rotationequerre[1] >360) Rotationequerre[1]-=360;
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
						Wequerre = element.text().toInt();
					if (element.tagName() == "largeur")
						Hequerre = element.text().toInt();	
					/*if (element.tagName() == "rotation")
					Rotationregle = element.text().toDouble();	*/	
				}
				noeud = noeud.nextSibling(); //Ce code permet d'aller à l'élément suivant.
			}
			xml_doc.close();
			//Vecteur de la droite de la regle
			QLine DroiteCourante[2];
			DroiteCourante[0].setLine(Xequerre,Yequerre,Xequerre+ Wequerre*cos(Rotationequerre[0]*PI/180),Yequerre+ Wequerre*sin(Rotationequerre[0]*PI/180));
			DroiteCourante[1].setLine(Xequerre,Yequerre,Hequerre*cos(Rotationequerre[1]*PI/180) + Xequerre,Hequerre*sin(Rotationequerre[1]*PI/180) + Yequerre);



			double angletemp;

			//angle entre les deux droites
			//angletemp = qAcos ((VecteurO.x()*VecteurCourant.x()+VecteurO.y()*VecteurCourant.y())/(sqrt(VecteurO.x()*VecteurO.x() + VecteurO.y()*VecteurO.y()) * sqrt(VecteurCourant.x()*VecteurCourant.x() + VecteurCourant.y()*VecteurCourant.y())));
			//angletemp = abs(abs(Rotationregle - angle)-180);

			for (int i =0 ; i<2 ; ++i)
			{
				QVector2D VecteurCourant (DroiteCourante[i].x2()-DroiteCourante[i].x1(),DroiteCourante[i].y2()-DroiteCourante[i].y1());
				angletemp = Rotationequerre[i] - rotation;
				if (i==0)
				{
					if (angletemp>0) angletemp-=180;
					else angletemp+=180;
				}
				if (abs (angletemp )< m_geometrie->m_txMagnetAng )
				{

					//détermination de a et b dans y=ax+b : équation de la droiteCourante
					double LESY = DroiteCourante[i] .y2()-DroiteCourante[i] .y1();
					double LESX = DroiteCourante[i] .x2()-DroiteCourante[i] .x1();
					double d;
					if (LESX == 0) d=abs(droitesOutilCourant.x1()-DroiteCourante[i] .x1());
					else
					{
						double a = LESY/LESX;
						double b = DroiteCourante[i] .y1() - a * DroiteCourante[i] .x1();

						d = abs(a*droitesOutilCourant.x1() - droitesOutilCourant.y1() + b)/sqrt(a*a +1);
					}
					if (d<m_geometrie->m_txMagnetDist && BestDist + BestAngle > d+angletemp )
					{
						//projection orthogonale sur la droite courante (pas le segment)
						QVector2D BA (droitesOutilCourant.x1()-DroiteCourante[i].x1(),droitesOutilCourant.y1()-DroiteCourante[i].y1());
						VecteurCourant.normalize();
						QVector2D BH = (BA.x()*VecteurCourant.x() + BA.y() * VecteurCourant.y())*VecteurCourant;

						QPoint Coordtemp  (DroiteCourante[i] .x1()+BH.x(),DroiteCourante[i] .y1()+BH.y());
						//tri des X et des Y des coord de l'equerre pour vérifier que le nouveau point est bien sur l'equerre(->le segment)
						int bas = qMin(DroiteCourante[i] .x1(),DroiteCourante[i] .x2());
						int haut = qMax(DroiteCourante[i] .x1(),DroiteCourante[i] .x2());

						if( Coordtemp.x() >= bas && Coordtemp.x() <= haut)
						{
							bas  = qMin(DroiteCourante[i] .y1(),DroiteCourante[i] .y2());
							haut = qMax(DroiteCourante[i] .y1(),DroiteCourante[i] .y2());

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
					//test à partir de l'autre bout de la regle
					if (LESX == 0) d=abs(droitesOutilCourant.x2()-DroiteCourante[i] .x1());
					else
					{
						double a = LESY/LESX;
						double b = DroiteCourante[i] .y1() - a * DroiteCourante[i] .x1();
						d = abs(a*droitesOutilCourant.x2() - droitesOutilCourant.y2() + b)/sqrt(a*a +1);
					
					}
				
					if (BestDist + BestAngle > d+angletemp && d<m_geometrie->m_txMagnetDist)
					{
						//projection orthogonale sur la droite courante (pas le segment)
						QVector2D BA (droitesOutilCourant.x2()-DroiteCourante[i] .x1(),droitesOutilCourant.y2()-DroiteCourante[i] .y1());
						VecteurCourant.normalize();
						QVector2D BH = (BA.x()*VecteurCourant.x() + BA.y() * VecteurCourant.y())*VecteurCourant;

						QPoint Coordtemp  (DroiteCourante[i] .x1()+BH.x(),DroiteCourante[i] .y1()+BH.y());
						//tri des X et des Y des coord de la regle pour vérifier que le nouveau point est bien sur la regle(->le segment)
						int bas = qMin(DroiteCourante[i] .x1(),DroiteCourante[i] .x2());
						int haut = qMax(DroiteCourante[i] .x1(),DroiteCourante[i] .x2());

						if( Coordtemp.x() >= bas && Coordtemp.x() <= haut)
						{
							bas  = qMin(DroiteCourante[i] .y1(),DroiteCourante[i] .y2());
							haut = qMax(DroiteCourante[i] .y1(),DroiteCourante[i] .y2());

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
					//test à partir du milieu de la regle
					if (LESX == 0) d=abs(Point3.x()-DroiteCourante[i] .x1());
					else
					{
						double a = LESY/LESX;
						double b = DroiteCourante[i] .y1() - a * DroiteCourante[i] .x1();
						d = abs(a*Point3.x() - Point3.y() + b)/sqrt(a*a +1);
					
					}
				
					if (BestDist + BestAngle > d+angletemp && d<m_geometrie->m_txMagnetDist)
					{
						//projection orthogonale sur la droite courante (pas le segment)
						QVector2D BA (Point3.x()-DroiteCourante[i] .x1(),Point3.y()-DroiteCourante[i] .y1());
						VecteurCourant.normalize();
						QVector2D BH = (BA.x()*VecteurCourant.x() + BA.y() * VecteurCourant.y())*VecteurCourant;

						QPoint Coordtemp  (DroiteCourante[i] .x1()+BH.x(),DroiteCourante[i] .y1()+BH.y());
						//tri des X et des Y des coord de la regle pour vérifier que le nouveau point est bien sur la regle(->le segment)
						int bas = qMin(DroiteCourante[i] .x1(),DroiteCourante[i] .x2());
						int haut = qMax(DroiteCourante[i] .x1(),DroiteCourante[i] .x2());

						if( Coordtemp.x() >= bas && Coordtemp.x() <= haut)
						{
							bas  = qMin(DroiteCourante[i] .y1(),DroiteCourante[i] .y2());
							haut = qMax(DroiteCourante[i] .y1(),DroiteCourante[i] .y2());

							if( Coordtemp.y() >= bas && Coordtemp.y() <= haut)
							{
								BestDist =d;
								BestAngle = angletemp;
								magnet = true;

								NewCoord = Coordtemp;
								NewCoord.setX(NewCoord.x()+VecteurO.x()/2);
								NewCoord.setY(NewCoord.y()+VecteurO.y()/2);
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
}
