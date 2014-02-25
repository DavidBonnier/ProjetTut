#include "Equerre.h"
#include "Geometrie.h"
#include "qmath.h"
#include <QDebug>
#define PI 3.141592653589793238462
void Equerre ::  MagnetiserEquerre (QList <Figure *> tableauFigure)
{

	const int TxMagnetAng =45;
	const int TxMagnetDist =45;
	
	//recherche des valeurs du XML------------------------------------------------------------
	QDomDocument dom("Equerre"); // Création de l'objet DOM
		QFile xml_doc("Equerre.xml"); // On choisit le fichier contenant les informations XML.
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
	int x = posX;
	int y = posY;
	double rotation[2] = {angle,angle -90};
	// Détection des bords de l'instrument à magnétiser ici l'equerre
	droitesOutilCourant[0].setLine(x,y,w*cos(rotation[0]*PI/180) + x,w*sin(rotation[0]*PI/180) + y);
	if(rotation[1]<0) rotation[1] +=360;

	droitesOutilCourant[1].setLine(x,y,h*cos(rotation[1]*PI/180) + x,h*sin(rotation[1]*PI/180) + y);
	
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
			QLine* DroiteCourante = dynamic_cast<QLine*>(tableauFigure[j]);//Changement?
			if(DroiteCourante!=NULL)
			{
				double angletemp;
				//vecteur de la droite courante
				QVector2D VecteurCourant  (DroiteCourante->x1()-DroiteCourante->x2(),DroiteCourante->y1()-DroiteCourante->y2());
				//angle entre les deux droites
				angletemp = qAcos ((VecteurO.x()*VecteurCourant.x() + VecteurO.y()*VecteurCourant.y())/(sqrt(VecteurO.x()*VecteurO.x() + VecteurO.y()*VecteurO.y()) * sqrt(VecteurCourant.x()*VecteurCourant.x() + VecteurCourant.y()*VecteurCourant.y())));
				if (abs(angletemp) < TxMagnetAng || abs(angletemp)-180 < TxMagnetAng )
				{
					//détermination de a et b dans y=ax+b : équation de la droiteCourante
					double a = (DroiteCourante->y2()-DroiteCourante->y1())/(DroiteCourante->x1()-DroiteCourante->x2());
					double b = DroiteCourante->y1() - a * DroiteCourante->x1();
					
					
					double d = abs(a*droitesOutilCourant[i].x1() + droitesOutilCourant[i].y1() + b)/sqrt(a*a +1);
					if (BestDist + BestAngle > d+angletemp && d<TxMagnetDist)
					{
						BestDist =d;
						BestAngle = angletemp;
						magnet = true;
						NewCoord.setX(((DroiteCourante->x2()-DroiteCourante->x1())*droitesOutilCourant[i].x1()+(DroiteCourante->y2()-DroiteCourante->y1())*droitesOutilCourant[i].y1()-b)/((DroiteCourante->x2()-DroiteCourante->x1())+(DroiteCourante->y2()-DroiteCourante->y1())+a));
						NewCoord.setY(a*NewCoord.x()+b);

						NewAngle=rotation[i]+angletemp;
						if(NewAngle>=360) NewAngle-=360;
						else if(NewAngle<0) NewAngle+=360;

					}
					//test à partir de l'autre bout de l'équerre
					d = abs(a*droitesOutilCourant[i].x2() + droitesOutilCourant[i].y2() + b)/sqrt(a*a +1);
					if (BestDist + BestAngle > d+angletemp && d<TxMagnetDist)
					{
						BestDist = d;
						BestAngle = angletemp;
						magnet = true;
						NewCoord.setX(((DroiteCourante->x2()-DroiteCourante->x1())*droitesOutilCourant[i].x2()+(DroiteCourante->y2()-DroiteCourante->y1())*droitesOutilCourant[i].y2()-b)/((DroiteCourante->x2()-DroiteCourante->x1())+(DroiteCourante->y2()-DroiteCourante->y1())+a));
						NewCoord.setY(a*NewCoord.x()+b);
						//décalage car les coordonnée sont celle du premier point
						NewCoord.setX(NewCoord.x()-(droitesOutilCourant[i].x2()-droitesOutilCourant[i].x1()));
						NewCoord.setY(NewCoord.y()-(droitesOutilCourant[i].y2()-droitesOutilCourant[i].y1()));

						NewAngle=rotation[i]+angletemp;
						if(NewAngle>=360) NewAngle-=360;
						else if(NewAngle<0) NewAngle+=360;
					}


					
				}
			}
		}
		//on a l'equerre nous regardons donc le magnétisme avec la regle
		if (pointGeometrie->regle)
		{
			//Lecture Regle
			QDomDocument dom("Regle"); // Création de l'objet DOM
			QFile xml_doc("Regle.xml"); // On choisit le fichier contenant les informations XML.
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
			Xregle= pointGeometrie->regle->posX;
			Yregle= pointGeometrie->regle->posY;
			double Rotationregle = pointGeometrie->regle->angle;
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
			DroiteCourante.setLine(Xregle,Yregle,Xregle+ Wregle*cos(Rotationregle*PI/180),Yregle+ Wregle*sin(Rotationregle*PI/180));
			
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
		posX = NewCoord.x();
		posY = NewCoord.y();
		angle += NewAngle;
	}
}