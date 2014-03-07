///////////////////////////////////////////////////////////////////////////
//! \file Geometrie.cpp
//!
//! \brief Mise en place des fonctions servant à gérer tous les instruments.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

#include <QDateTime>

#include "Geometrie.h"
#include "projetgeometrie.h"

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \brief Costructeur de Geometrie, il défini les pointeurs à NULL, les modifications à false et créer un premier ordre de tracage des instruments.
//!
//! \date 30/01/2014
///////////////////////////////////////////////////////////////////////
Geometrie::Geometrie(ProjetGeometrie* projetGeometrie)
{
    m_projetGeometrie = projetGeometrie;
	largeurViewport = width() - width()%100; //Arrondissement aux centaines inferieures
	hauteurViewport = height() - height()%100;
	id_point = 0;
    clickTxt = false;
	clickPoint = false;
    txtSelectionne = false;
    stockTxt.clear();
    setMouseTracking(true);

    regle = NULL;
    compas = NULL;
    equerre = NULL;
    crayon = NULL;
	grille = true;

    modifCompas = false;
    modifCrayon = false;
    modifEquerre = false;
    modifRegle = false;
	
	
    ordreInstruments[0] = 'C'; //Crayon
    ordreInstruments[1] = 'e';
    ordreInstruments[2] = 'r';
    ordreInstruments[3] = 'c'; //Compas

    m_rectangleViewport = new QRect (0,0,1500,1500);
    m_nbGraduation = 500;
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \brief Destructeur de Geometrie, il libère la mémoire
//!
//! \date 30/01/2014
///////////////////////////////////////////////////////////////////////
Geometrie::~Geometrie()
{
    delete regle;
    delete compas;
    delete equerre;
    delete crayon;
    stockTxt.clear();
}

///////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//!
//! \brief Cette fonction instancie ou détruit une règle suivant la présence ou non de celle-ci.
//!
//! \date 31/01/2014
///////////////////////////////////////////////////////////////////////
bool Geometrie::gererRegle()
{
    if (regle == NULL)
    {
        regle = new Regle(this);
        return true;
    }
    else
    {
        delete regle;
        regle = NULL;
        return false;
    }
}

///////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//!
//! \brief Cette fonction instancie ou détruit un compas suivant la présence ou non de celui-ci.
//!
//! \date 31/01/2014
///////////////////////////////////////////////////////////////////////
bool Geometrie::gererCompas()
{
    if (compas == NULL)
    {
        compas = new Compas(this);
        return true;
    }
    else
    {
        delete compas;
        compas = NULL;
        return false;
    }
}

///////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//!
//! \brief Cette fonction instancie ou détruit un crayon suivant la présence ou non de celui-ci.
//!
//! \date 31/01/2014
///////////////////////////////////////////////////////////////////////
bool Geometrie::gererCrayon()
{
    if (crayon == NULL)
    {
        crayon = new Crayon(this);
        return true;
    }
    else
    {
        delete crayon;
        crayon = NULL;
        return false;
    }
}

///////////////////////////////////////////////////////////////////////
//! \author ROCHE Hugo
//!
//! \brief Cette fonction instancie ou détruit une équerre suivant la présence ou non de celle-ci.
//!
//! \date 31/01/2014
///////////////////////////////////////////////////////////////////////
bool Geometrie::gererEquerre()
{
    if (equerre == NULL)
    {
        equerre = new Equerre(this);
        return true;
    }
    else
    {
        delete equerre;
        equerre = NULL;
        return false;
    }
}

///////////////////////////////////////////////////////////////////////
//! \author JACQUIN Dylan
//!
//! \param event Evenement de tracé.
//!
//! \brief Cette fonction trie le tableau des positions des intruments et les dessine dans l'ordre,elle trace aussi la grille.
//!
//! \date 31/01/2014
///////////////////////////////////////////////////////////////////////
void Geometrie::paintEvent (QPaintEvent *event)
{
    if (modifCrayon) //Si il y a une modification de crayon
    {
        if (!(ordreInstruments[0] == 'C')) //Si la dernière modification n'est pas un crayon, on modifie l'ordre des dessins
        {
            //Recherche de la posittion du crayon
            int i=0; //Position du crayon
            while (ordreInstruments[i] != 'C')
                i++;
            //Décalage à droite à partir de la position du crayon
            while (i != 0)
            {
                ordreInstruments[i] = ordreInstruments[i-1];
                i--;
            }
            //Positionnement du crayon au début
            ordreInstruments[0] = 'C';
        }
    }
    if (modifCompas) //Si il y a une modification de compas
    {
        if (!(ordreInstruments[0] == 'c')) //Si la dernière modification n'est pas un compas, on modifie l'ordre des dessins
        {
            //Recherche de la posittion du compas
            int i=0; //Position du compas
            while (ordreInstruments[i] != 'c')
                i++;
            //Décalage à droite à partir de la position du compas
            while (i != 0)
            {
                ordreInstruments[i] = ordreInstruments[i-1];
                i--;
            }
            //Positionnement du compas au début
            ordreInstruments[0] = 'c';
        }
    }
    if (modifEquerre) //Si il y a une modification d'equerre
    {
        if (!(ordreInstruments[0] == 'e')) //Si la dernière modification n'est pas une equerre, on modifie l'ordre des dessins
        {
            //Recherche de la posittion de l'equerre
            int i=0; //Position de l'equerre
            while (ordreInstruments[i] != 'e')
                i++;
            //Décalage à droite à partir de la position de l'equerre
            while (i != 0)
            {
                ordreInstruments[i] = ordreInstruments[i-1];
                i--;
            }
            //Positionnement de l'equerre au début
            ordreInstruments[0] = 'e';
        }
    }
    if (modifRegle) //Si il y a une modification de regle
    {
        if (!(ordreInstruments[0] == 'r')) //Si la dernière modification n'est pas une regle, on modifie l'ordre des dessins
        {
            //Recherche de la posittion de la regle
            int i=0; //Position de la regle
            while (ordreInstruments[i] != 'r')
                i++;
            //Décalage à droite à partir de la position de la regle
            while (i != 0)
            {
                ordreInstruments[i] = ordreInstruments[i-1];
                i--;
            }
            //Positionnement de la regle au début
            ordreInstruments[0] = 'r';
        }
    }

	int largeurViewport = width() - width()%100 //Arrondissement aux centaines inferieures
	   ,hauteurViewport = height() - height()%100;

    QPainter dessin(this);
	dessin.setViewport(0,0, largeurViewport, hauteurViewport);
	dessin.setWindow(-largeurViewport/2, -hauteurViewport/2, largeurViewport, hauteurViewport);
	//Dessin ou non de la grille
	if (grille)
	{
		//Préparation de la grille
		dessin.save();
		QPen EpaisseurGrille, EpaisseurGrilleCentre;
		EpaisseurGrille.setWidth(1);
		EpaisseurGrilleCentre.setWidth(3);

		//Graduations verticales
        for (int i=-largeurViewport/2 ; i<largeurViewport ; i+=50)
            if(i == 0) //Graduation du milieu en vertical
			{
                dessin.setPen(EpaisseurGrilleCentre);
                dessin.drawLine(i,-hauteurViewport/2 , i, hauteurViewport);
			}
			else
			{
				dessin.setPen(EpaisseurGrille);
                dessin.drawLine(i,-hauteurViewport/2 , i,hauteurViewport);
			}

		//Horizontales
        for (int i=-hauteurViewport/2 ; i<hauteurViewport ; i+=50)
            if(i == 0) //Graduation du milieu en vertical
			{
				dessin.setPen(EpaisseurGrilleCentre);
                dessin.drawLine(-largeurViewport/2,i , largeurViewport, i);
			}
			else
			{
				dessin.setPen(EpaisseurGrille);
                dessin.drawLine(-largeurViewport/2,i, largeurViewport,i);
			}

		dessin.restore();
	}

    QPainter * peintre;
    peintre = new QPainter(this);
	peintre->setViewport(0,0, largeurViewport, hauteurViewport);
	peintre->setWindow(-largeurViewport/2, -hauteurViewport/2, largeurViewport, hauteurViewport);
    dessinerFigure(peintre);
    delete peintre;

    //Parcours du tableau pour tracer les instruments (à l'envers car trace du fond au dessus)
    for (int i=4 ; i>=0 ; i--)
    {
        if(ordreInstruments[i] == 'r')
            if(regle != NULL)
                regle->dessinerRegle(dessin);
        if(ordreInstruments[i] == 'c')
            if(compas != NULL)
                compas->dessinerCompas(dessin);
        if(ordreInstruments[i] == 'e')
            if(equerre != NULL)
                equerre->dessinerEquerre(dessin);
        if(ordreInstruments[i] == 'C')
            if(crayon != NULL)
                crayon->dessinerCrayon(dessin);
    }
}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param dessinTrait Prend le dessinTrait du QPainter en paramètre
//!
//! \brief Cette fonction dessine tout les traits et arcs du dossier.
//!
//! \date 01/02/2014
///////////////////////////////////////////////////////////////////////
void Geometrie::dessinerFigure(QPainter * peintre)
{
    QPen pen;
    pen.setColor(m_projetGeometrie->m_couleurTrait); //Changement de la couleur des traits
    pen.setWidth(m_projetGeometrie->ui.spinBoxEpaisseur->value()); //Changement de l'épaisseur

    peintre->setPen(pen);

    for (int i = 0; i<tableauFigure.size(); i++)
    {
        Arc* monArc = dynamic_cast<Arc*> (tableauFigure[i]);
        if(monArc!=NULL)
        {
            if(monArc->getSpan() != NULL)
                peintre->drawArc(monArc->getRectangle(),monArc->getStart(),*monArc->getSpan());
        }
        else
        {
            Ligne* maLigne = dynamic_cast<Ligne*> (tableauFigure[i]);
            if(maLigne!=NULL)
                peintre->drawLine(maLigne->getQLine());
            else
            {
                Point* monPoint = dynamic_cast<Point*> (tableauFigure[i]);
                if(monPoint!=NULL)
                {
                    peintre->drawLine(monPoint->getHorizontalLine());
                    peintre->drawLine(monPoint->getVerticalLine());
                }
            }
        }
		tableauFigure[i]->installEventFilter(this); //Mise en place de l'event filter pour pouvoir l'effacer
    }
}

QString Geometrie::generationSVG()
{
    QString fichierTemp ("./temps.svg");
    QString fichierTemp2 ("./temps2.svg");


    QPainter * peintreGeneration;
    peintreGeneration = new QPainter;

    QSvgGenerator * generator;
    generator = new QSvgGenerator;
    generator->setFileName(fichierTemp);

    peintreGeneration->begin(generator);
    dessinerFigure(peintreGeneration);
    peintreGeneration->end();
    delete generator;
    delete peintreGeneration;

    peintreGeneration = new QPainter;
    generator = new QSvgGenerator;
    generator->setFileName(fichierTemp2);
    peintreGeneration->begin(generator);
    QSvgRenderer(fichierTemp).render(peintreGeneration);

    //Ajout de la grille
    if(grille)
    {


        ++3
    }

    peintreGeneration->end();
    delete generator;
    delete peintreGeneration;

    QFile * sauvegardeFichier;
    sauvegardeFichier = new QFile(fichierTemp);

    QDateTime courantDateTime = QDateTime::currentDateTime();
    QString nomFichier ("./" + courantDateTime.toString("dd-MM-yyyy_hh-mm-ss")+".svg");
    if(QFile::exists(nomFichier))
        QFile::remove(nomFichier);
    sauvegardeFichier->copy(nomFichier);
    sauvegardeFichier->close();
    delete sauvegardeFichier;
    QFile::remove(fichierTemp);

    return nomFichier;
}

void Geometrie::mousePressEvent(QMouseEvent *clic)
{
	//Lorsque l'on clique quelque part sur l'image, on crée un QPixmap : c'est en quelque sorte un screenshot de la fenêtre active
	QPixmap pixmap = QPixmap::grabWindow(winId());

	//On récupère la couleur du pixel sur lequel on a cliqué
	QRgb color = pixmap.toImage().pixel(clic->x(), clic->y());

	//On transforme ce QRgb en QColor
	QColor detec(color);

	//Si cette couleur est égale à l'une des couleurs de l'instrument, alors on a cliqué sur cet instrument

	//Règle--------------------------------------------------------
	if(detec == QColor(255,255,51) || detec == QColor(255,255,153))
	{
		//Le corps de la règle
		regle->clic(clic,false,false);
	}

	if(detec == QColor(127,255,255))
	{
		//Le bouton de rotation de la règle
		regle->clic(clic,true,false);
	}

	//Équerre--------------------------------------------------------
	if(detec == QColor(255,255,50) || detec == QColor(255,255,152))
	{
		//Le corps de l'équerre
		equerre->clic(clic,false,false);
	}

	if(detec == QColor(126,255,255))
	{
		//Le bouton de rotation de l'équerre
		equerre->clic(clic,true,false);
	}

	//Crayon--------------------------------------------------------
	if(detec == QColor(255,255,49) || detec == QColor(255,203,96))
	{
		//Le corps du crayon
		crayon->clic(clic,false,false);
	}

	if(detec == QColor(125,255,255))
	{
		//Le bouton de rotation de la règle
		crayon->clic(clic,true,false);
	}

	//Compas--------------------------------------------------------
	if(detec == QColor(160,160,164) || detec == QColor(0,0,255))
	{
		//Le corps du crayon
		compas->clic(clic,false,false);
	}

	if(detec == QColor(124,255,255))
	{
		//Le bouton de rotation du crayon
		compas->clic(clic,true,false);
	}

	if(detec == QColor(255,0,0))
	{
		//Le bouton d'écartement du compas
		compas->clic(clic,false,true);
	}

	//Désélection si on clique sur un pixel blanc ou noir
	if(detec == QColor(240,240,240) || detec == QColor(0,0,0))
	{
		if(regle != NULL)
			regle->deselectionner();
		if(equerre != NULL)
			equerre->deselectionner();
		if(crayon !=NULL)
			crayon->deselectionner();
		if(compas !=NULL)
			compas->deselectionner();
	}
	//-------------------------------------------------------------

	//Création des zones de texte
    if(clickTxt)
    {
        txt = new QTextEdit(this);
        txt->installEventFilter(this);
		txt->setFixedHeight(35);
		txt->setFixedWidth(100);
		txt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        txt->move(clic->x(), clic->y());
        txt->setContextMenuPolicy(Qt::NoContextMenu);
        txt->show();
        stockTxt.push_back(txt);
        clickTxt = false;
		emit curseur();
    }
    //Création des points
    else if(clickPoint)
	{
        Point * nouveauPoint;
        nouveauPoint = new Point(clic->pos());
        tableauFigure.push_back(nouveauPoint);

        clickPoint = false;
        emit pointcree();
    }
}

bool Geometrie::eventFilter(QObject * obj, QEvent * e)
{
	//Gestion du texte
    if(e->type() == QEvent::MouseButtonPress) //Clic de souris
    {
        if(!txtSelectionne)
        {
            txtSelectionne = true;
            for(int i = 0; i < stockTxt.size(); i++)
            {
                if(obj == stockTxt[i])
                {
                    id_txtSelectionne = i;
                    break;
                }
            }
        }
        else
            txtSelectionne = false;
        return true;
    }

    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent* ke = static_cast <QKeyEvent*> (e);
        if(ke->key() == Qt::Key_Delete)
        {
            if(txtSelectionne && stockTxt[id_txtSelectionne] != NULL)
            {
                txtSelectionne = false;
                delete stockTxt[id_txtSelectionne];
                return true;
            }
        }
    }

	//Gestion de la suppression des tracés
	if (e->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* me = static_cast <QMouseEvent*> (e);
        if (me->button() == Qt::RightButton) //Clic droit de la souris
		{
			for(int i=0; tableauFigure.size(); i++)
			{
				if(obj == tableauFigure[i])
				{
					tableauFigure.removeAt(i);
				}
			}
		}
	}

    return QObject::eventFilter(obj, e);
}

void Geometrie::mouseMoveEvent(QMouseEvent *move)
{
	//Regle--------------------------------------------------------
	if (regle)
	{
        if (regle->m_moveSelected || regle->m_rotateSelectedLeft || regle->m_rotateSelectedRight)
		{
			regle->move(move);
			modifRegle = true;
			update();
		}
	}
	//Equerre--------------------------------------------------------
	if (equerre)
	{
        if (equerre->m_moveSelected || equerre->m_rotateSelectedLeft || equerre->m_rotateSelectedRight)
		{
			equerre->move(move);
			modifEquerre = true;
			update();
		}
	}
	//Crayon--------------------------------------------------------
	if (crayon)
	{
        if (crayon->m_moveSelected || crayon->m_rotateSelectedLeft || crayon->m_rotateSelectedRight)
		{
			crayon->move(move);
			modifCrayon = true;
			update();
		}
	}
	//Compas--------------------------------------------------------
	if (compas)
	{
		if (compas->m_moveSelected || compas->m_rotateSelectedLeft || compas->m_rotateSelectedRight || compas->m_ecartSelected)
		{
			compas->move(move);
			modifCompas = true;
			update();
		}
	}

    if(txtSelectionne && stockTxt[id_txtSelectionne] != NULL)
    {
        stockTxt[id_txtSelectionne]->move(move->pos().x(), move->pos().y());
        update();
    }
}
