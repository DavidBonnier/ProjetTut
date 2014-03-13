///////////////////////////////////////////////////////////////////////////
//! \file Crayon.cpp
//!
//! \brief Mise en place des fonctions pour modifier le Crayon.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include "Crayon.h"
#include "Geometrie.h"
#include "projetgeometrie.h"

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param geometrie La seule instanciation de Geometrie pour pourvoir changer l'ui.
//!
//! \brief Constructeur du Crayon, initialise toutes les données membres avec le fichier XML.
//!
//! Appelle de Initialisation qui est dans Instrument pour initialiser les données membres d'Instument.
//! Ensuite initialisation des données membres de Crayon dans le constructeur.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
Crayon::Crayon(Geometrie * geometrie)
{
    m_nomFichierXML = new QString("Resources/XML/Crayon.xml");
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
        }
        noeud = noeud.nextSibling(); //Ce code permet d'aller à l'élément suivant.
    }
    xml_doc.close();

    update();
}

//*********************************Fonctions de mise à jour des valeurs*******************************
///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param transparence Nouveau booléan pour la transparence ou non du Crayon.
//!
//! \brief Cette fonction met à jour la transparence du Crayon et la chekBox de droite.
//!
//! Appelle la fonction de la classe mère pour mettre à jour la transparence.
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Crayon::setTransparence(bool transparence)
{
    Instrument::setTransparence(transparence);
    m_geometrie->m_projetGeometrie->ui.CheckBoxCrayonTransparence->setChecked(transparence);
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param positionX Double pour la position en x de la pointe du Crayon.
//! \param positionY Double pour la position en y de la pointe du Crayon.
//!
//! \brief Cette fonction met à jour la position et les SpinBoxs de droite.
//!
//! Appelle la fonction de la classe mère pour mettre à jour la position.
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Crayon::translation(double positionX , double positionY)
{
    Instrument::translation(positionX,positionY);
    m_geometrie->m_projetGeometrie->ui.SpinBoxCrayonPositionX->setValue(positionX);
    m_geometrie->m_projetGeometrie->ui.SpinBoxCrayonPositionY->setValue(positionY);
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param angle Double qui est le nouveau angle du Crayon.
//!
//! \brief Cette fonction met à jour l'angle et la spinBox du Crayon.
//!
//! Appelle la fonction de la classe mère pour mettre à jour l'angle.
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Crayon::setAngle(double angle)
{
    Instrument::setAngle(angle);
    m_geometrie->m_projetGeometrie->ui.SpinBoxCrayonOrientation->setValue(angle);
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param dessin Prend le dessin du QPainter en paramètres
//!
//! \brief Cette fonction dessine un Crayon grâce à ses données membres.
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

    int epaisseurMine = m_largeur/2;
    int hauteurMine = m_hauteurPointe/3;
    //Rotation
    double angledessinCrayon = m_angle - 90;
	if (angledessinCrayon <0) angledessinCrayon +=360;

    dessin.translate(m_position.x(),m_position.y());
    dessin.rotate(angledessinCrayon);
    dessin.translate(-m_position.x(),-m_position.y());
    //Dessin de la mine
    QPointF pointsMine[3] = {QPointF(m_position.x(), m_position.y()), QPointF(m_position.x()-(epaisseurMine/2), m_position.y()+hauteurMine), QPointF(m_position.x()+epaisseurMine/2, m_position.y()+hauteurMine)}; //Points de la zone transparente
    dessin.drawConvexPolygon(pointsMine, 3); //Dessin de la mine
    //Dessin du reste de la pointe
    dessin.setBrush(QColor(255,203,96)); //Mise en couleur de la pointe
    QPointF pointe[4] = {QPointF(m_position.x()-(epaisseurMine/2), m_position.y()+hauteurMine), QPointF(m_position.x()+epaisseurMine/2, m_position.y()+hauteurMine),
                         QPointF(m_position.x()+m_largeur/2, m_position.y()+m_hauteurPointe), QPointF(m_position.x()-(m_largeur/2), m_position.y()+m_hauteurPointe)}; //Points du triangle principal
    dessin.drawConvexPolygon(pointe, 4); //Pointe du crayon
    //Dessin du corps du crayon
    dessin.setBrush(QColor(255,255,49));
    dessin.drawRect(m_position.x()-(m_largeur/2), m_position.y()+m_hauteurPointe, m_largeur, m_longueur);
    //Dessin du bouton rotation
    dessin.setBrush(QColor(125,255,255));
    dessin.drawRect(m_position.x()-epaisseurMine, m_position.y()+250, 2*epaisseurMine, 8*epaisseurMine);
    //Dessin de 2 traits sur le corps
    dessin.drawLine(m_position.x()-(m_largeur/5),m_position.y()+m_hauteurPointe, m_position.x()-(m_largeur/5),m_position.y()+m_hauteurPointe+m_longueur-30);
    dessin.drawLine(m_position.x()+m_largeur/5,m_position.y()+m_hauteurPointe, m_position.x()+m_largeur/5,m_position.y()+m_hauteurPointe+m_longueur-30);
    //Dessin du bouton de tracé
	dessin.setBrush(QColor(0,255,0));
    dessin.drawRect(m_position.x()-epaisseurMine, m_position.y()+50, 2*epaisseurMine, 6*epaisseurMine);
	dessin.restore();
}

///////////////////////////////////////////////////////////////////////
//! \author BIOLLEY Pierre
//!
//! \brief
//!
//! \date 07/02/2014
///////////////////////////////////////////////////////////////////////
void Crayon::MagnetiserCrayon()
{	
	if(m_geometrie->magne_actif)
	{
		int x = m_position.x();
		int y = m_position.y();	
		bool magnet = false;
		m_estMagnetise = false;
		double BestDist=99999;

		QPoint NewCoord;

		QPoint PointMagnetise;
		QLine DroiteMagnetise;

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
            DroiteCourante[0].setLine(Xequerre,Yequerre,Xequerre+ Wequerre*cos(Rotationequerre[0]*M_PI/180),Yequerre+ Wequerre*sin(Rotationequerre[0]*M_PI/180));
            DroiteCourante[1].setLine(Xequerre,Yequerre,Hequerre*cos(Rotationequerre[1]*M_PI/180) + Xequerre,Hequerre*sin(Rotationequerre[1]*M_PI/180) + Yequerre);

			for (int i =0 ; i<2 ; ++i)
			{
				QVector2D VecteurCourant (DroiteCourante[i].x2()-DroiteCourante[i].x1(),DroiteCourante[i].y2()-DroiteCourante[i].y1());

				//détermination de a et b dans y=ax+b : équation de la droiteCourante
				double LESY = DroiteCourante[i] .y2()-DroiteCourante[i] .y1();
				double LESX = DroiteCourante[i] .x2()-DroiteCourante[i] .x1();
				double d;
				if (LESX == 0) d=abs(x-DroiteCourante[i] .x1());
				else
				{
					double a = LESY/LESX;
					double b = DroiteCourante[i] .y1() - a * DroiteCourante[i] .x1();

					d = abs(a*x - y + b)/sqrt(a*a +1);
				}
				if (d<m_geometrie->m_txMagnetDist && BestDist  > d )
				{
					//projection orthogonale sur la droite courante (pas le segment)
					QVector2D BA (x-DroiteCourante[i].x1(),y-DroiteCourante[i].y1());
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
							magnet = true;
							NewCoord = Coordtemp;
							m_estMagnetise =true;
						}
					} 
				}
			}
		}



		if (m_geometrie->regle)
		{
			//Lecture Regle
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

			//détermination de a et b dans y=ax+b : équation de la droiteCourante
			double LESY = DroiteCourante.y2()-DroiteCourante.y1();
			double LESX = DroiteCourante.x2()-DroiteCourante.x1();
			double d;
			if (LESX == 0) d=abs(x-DroiteCourante.x1());
			else
			{
				double a = LESY/LESX;
				double b = DroiteCourante.y1() - a * DroiteCourante.x1();

				d = abs(a*x - y + b)/sqrt(a*a +1);
			}
			if (d<m_geometrie->m_txMagnetDist && BestDist  > d )
			{
				//projection orthogonale sur la droite courante (pas le segment)
				QVector2D BA (x-DroiteCourante.x1(),y-DroiteCourante.y1());
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
						magnet = true;
						NewCoord = Coordtemp;
						m_estMagnetise =true;
					}
				} 
			}
		}

		if (magnet)//Ecrire
		{
			m_position.setX(NewCoord.x());
			m_position.setY(NewCoord.y());
		}
	}
}

///////////////////////////////////////////////////////////////////////
//! \author BIOLLEY Pierre
//!
//! \brief
//!
//! \date 07/02/2014
///////////////////////////////////////////////////////////////////////
void Crayon::traceCrayon()
{
	if (m_estMagnetise)
	{
		if (m_premierContact)
		{
			m_droiteEnCours = new Ligne(QLineF(m_position.x(), m_position.y(), m_position.x(), m_position.y()));
			m_geometrie->tableauFigure.push_back(m_droiteEnCours);
			m_premierContact = false;
		}
		else
		{
			if ( m_position.x()<m_droiteEnCours->getQLine().x1())
			{
				m_droiteEnCours->setQLine(QLineF(m_position.x(),m_position.y(),m_droiteEnCours->getQLine().x2(),m_droiteEnCours->getQLine().y2()));
			}
			else if ( m_position.x()>m_droiteEnCours->getQLine().x2())
			{
				m_droiteEnCours->setQLine(QLineF(m_droiteEnCours->getQLine().x1(),m_droiteEnCours->getQLine().y1(),m_position.x(),m_position.y()));
			}
			else if(m_position.y()>m_droiteEnCours->getQLine().y1())
			{
				m_droiteEnCours->setQLine(QLineF(m_position.x(),m_position.y(),m_droiteEnCours->getQLine().x2(),m_droiteEnCours->getQLine().y2()));

			}
			else if(m_position.y()<m_droiteEnCours->getQLine().y2())
			{
				m_droiteEnCours->setQLine(QLineF(m_droiteEnCours->getQLine().x1(),m_droiteEnCours->getQLine().y1(),m_position.x(),m_position.y()));
			}
			m_geometrie->tableauFigure[m_geometrie->tableauFigure.size()-1] = m_droiteEnCours;
		}
	}
	else
	{
		m_premierContact = true;
	}
}
