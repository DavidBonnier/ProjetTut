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

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param geometrie La seule instanciation de Geometrie pour pourvoir changer l'ui.
//!
//! \brief Constructeur du Equerre, initialise toutes les données membres avec le fichier XML.
//!
//! Appelle de InitialisationRegle qui est dans Regle pour initialiser les données membres de Regle.
//! Cette dernière appelle la fonction Initialisation d'Instrument.
//! Ensuite initialisation des données membres de Compas dans le constructeur.
//!
//! \date 16/01/2014
///////////////////////////////////////////////////////////////////////
Equerre::Equerre(Geometrie * geometrie)
{
    m_nomFichierXML = new QString("Resources/XML/Equerre.xml");
    m_nomDocument = new QString("Equerre");
    m_nomElement = new QString("equerre");

    m_geometrie = geometrie;

    InitialisationRegle();

    update();
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

//**********************************Fonctions de mise à jour des valeurs*******************************
///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param transparence Nouveau booléan pour la transparence ou non de l'Equerre.
//!
//! \brief Cette fonction met à jour la transparence de l'Equerre et la chekBox de droite.
//!
//! Appelle la fonction de la classe mère pour mettre à jour la transparence.
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Equerre::setTransparence(bool transparence)
{
    Instrument::setTransparence(transparence);
    m_geometrie->m_projetGeometrie->ui.CheckBoxEquerreTransparence->setChecked(transparence);
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param positionX Double pour la position en x de l'angle droit de l'Equerre.
//! \param positionY Double pour la position en y de l'angle droit de l'Equerre.
//!
//! \brief Cette fonction met à jour la position et les SpinBoxs de droite.
//!
//! Appelle la fonction de la classe mère pour mettre à jour la position.
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Equerre::translation(double positionX , double positionY)
{
    Instrument::translation(positionX,positionY);
    m_geometrie->m_projetGeometrie->ui.SpinBoxEquerrePositionX->setValue(positionX);
    m_geometrie->m_projetGeometrie->ui.SpinBoxEquerrePositionY->setValue(positionY);
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param angle Double qui est le nouveau angle de l'Equerre.
//!
//! \brief Cette fonction met à jour l'angle, la spinBox de l'Equerre et modifie la ligne si il en a une en cours.
//!
//! Appelle la fonction de la classe mère pour mettre à jour l'angle.
//!
//! \date 15/01/2014
///////////////////////////////////////////////////////////////////////
void Equerre::setAngle(double angle)
{
    Instrument::setAngle(angle);
    m_geometrie->m_projetGeometrie->ui.SpinBoxEquerreOrientation->setValue(angle);
    if(!m_geometrie->tableauFigure.isEmpty())
    {
        Ligne* maLigne = dynamic_cast<Ligne*> (m_geometrie->tableauFigure[m_geometrie->tableauFigure.size()-1]);
        if(maLigne && !maLigne->getFin())
            maLigne->setAngle(-m_angle);
    }
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param dessin Prend le dessin du QPainter en paramètres
//!
//! \brief Cette fonction dessine une Equerre grâce à ses données membres.
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

///////////////////////////////////////////////////////////////////////
//! \author BIOLLEY Pierre
//!
//! \brief
//!
//! \date 07/02/2014
///////////////////////////////////////////////////////////////////////
void Equerre::MagnetiserEquerre()
{
	if(m_geometrie->magne_actif)
    {
		QLine droitesOutilCourant [2];
		int x = m_position.x();
		int y = m_position.y();
		double rotation[2] = {m_angle,m_angle -90};
		// Détection des bords de l'instrument à magnétiser ici l'equerre
        droitesOutilCourant[0].setLine(x,y,m_longeur*cos(rotation[0]*M_PI/180) + x,m_longeur*sin(rotation[0]*M_PI/180) + y);
		if(rotation[1]<0) rotation[1] +=360;

        droitesOutilCourant[1].setLine(x,y,m_largeur*cos(rotation[1]*M_PI/180) + x,m_largeur*sin(rotation[1]*M_PI/180) + y);

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

					if (VecteurCourant.y()<0) VecteurCourant=-VecteurCourant;
					//angle entre les deux droites
					/*double COSSIN = (VecteurO.x()*VecteurCourant.x() + VecteurO.y()*VecteurCourant.y())/(sqrt(VecteurO.x()*VecteurO.x() + VecteurO.y()*VecteurO.y()) * sqrt(VecteurCourant.x()*VecteurCourant.x() + VecteurCourant.y()*VecteurCourant.y()));
					angletemp =  180*qAcos (COSSIN)/PI *qAsin(COSSIN)/abs(qAsin(COSSIN));*/


                    double angleCourant = 180*qAcos(VecteurCourant.x()/(1 * sqrt(VecteurCourant.x()*VecteurCourant.x() + VecteurCourant.y()*VecteurCourant.y())))/M_PI;
					angletemp = angleCourant - rotation[i];

					if (abs(angletemp) < m_geometrie->m_txMagnetAng || abs(abs(angletemp)-180 )< m_geometrie->m_txMagnetAng )
					{
						//détermination de a et b dans y=ax+b : équation de la droiteCourante
						double LESY = DroiteCourante->getQLine().y2()-DroiteCourante->getQLine().y1();
						double LESX = DroiteCourante->getQLine().x2()-DroiteCourante->getQLine().x1();
						double d;
						if (LESX == 0) d=abs(droitesOutilCourant[i].x1()-DroiteCourante->getQLine() .x1());
						else
						{
							double a = LESY/LESX;
							double b = DroiteCourante->getQLine() .y1() - a * DroiteCourante->getQLine() .x1();

							d = abs(a*droitesOutilCourant[i].x1() - droitesOutilCourant[i].y1() + b)/sqrt(a*a +1);
						}
						if (BestDist + BestAngle > d+angletemp && d<m_geometrie->m_txMagnetDist)
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
						//test à partir de l'autre bout de l'équerre
						if (LESX != 0) 
						{
							double a = LESY/LESX;
							double b = DroiteCourante->getQLine() .y1() - a * DroiteCourante->getQLine() .x1();

							d = abs(a*droitesOutilCourant[i].x2() - droitesOutilCourant[i].y2() + b)/sqrt(a*a +1);
						}
					
						if (BestDist + BestAngle > d+angletemp && d<m_geometrie->m_txMagnetDist)
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
			//on a l'equerre nous regardons donc le magnétisme avec la regle
			if (m_geometrie->regle)
			{
				int Xregle,Yregle, Wregle, Hregle;
                Xregle = m_geometrie->regle->getPositionX();
                Yregle = m_geometrie->regle->getPositionY();
                Wregle = m_geometrie->regle->getLongueur();
                Hregle = m_geometrie->regle->getLargeur();

                //Vecteur de la droite de l'equerre
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
				if (abs (angletemp )< m_geometrie->m_txMagnetAng )
				{
					//détermination de a et b dans y=ax+b : équation de la droiteCourante
					double LESY = DroiteCourante.y2()-DroiteCourante.y1();
					double LESX = DroiteCourante.x2()-DroiteCourante.x1();
					double d;
					if (LESX == 0) d=abs(droitesOutilCourant[i].x1()-DroiteCourante.x1());
					else
					{
						double a = LESY/LESX;
						double b = DroiteCourante.y1() - a * DroiteCourante.x1();

						d = abs(a*droitesOutilCourant[i].x1() - droitesOutilCourant[i].y1() + b)/sqrt(a*a +1);
					}
					if (d<m_geometrie->m_txMagnetDist && BestDist + BestAngle > d+angletemp )
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
					if (LESX != 0)
					{
						double a = LESY/LESX;
						double b = DroiteCourante.y1() - a * DroiteCourante.x1();

						d = abs(a*droitesOutilCourant[i].x2() - droitesOutilCourant[i].y2() + b)/sqrt(a*a +1);
					}
				
					if (BestDist + BestAngle > d+angletemp && d<m_geometrie->m_txMagnetDist)
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
}

