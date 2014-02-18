///////////////////////////////////////////////////////////////////////////
//! \file Geometrie.cpp
//!
//! \brief Mise en place des fonctions servant à gérer tous les instruments.
//!
//! \date 12/01/2014
///////////////////////////////////////////////////////////////////////////

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

    clickTxt = false;
    txtSelectionne = false;
    stockTxt.clear();
    setMouseTracking(true);

    regle = NULL;
    compas = NULL;
    equerre = NULL;
    crayon = NULL;
	grille = false;

    modifCompas = false;
    modifCrayon = false;
    modifEquerre = false;
    modifRegle = false;

    ordreInstruments[0] = 'C'; //Crayon
    ordreInstruments[1] = 'e';
    ordreInstruments[2] = 'r';
    ordreInstruments[3] = 'c'; //Compas

    nomFichierTemp = new QString("temps.svg");
    nomFichier = new QString("enregistrement.svg");
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
//! \brief Cette fonction trie le tableau des positions des intruments et les dessine dans l'ordre, elle trace aussi la grille.
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

    QPainter dessin(this);
	//Dessin ou non de la grille
	if (grille)
	{
		//Graduations verticales
		for (int i=0 ; i<width() ; i+=50)
			if(i-25<=width()/2 && i+25>=width()/2) //Graduation du milieu en vertical
			{
				dessin.drawLine(i-1,0 , i-1, height());
				dessin.drawLine(i,0 , i, height());
				dessin.drawLine(i+1,0 , i+1, height());
			}
			else
				dessin.drawLine(i,0 , i,height());

		//Horizontales
		for (int i=0 ; i<height() ; i+=50)
			if(i-25<=height()/2 && i+25>=height()/2) //Graduation du milieu en vertical
			{
				dessin.drawLine(0,i-1 , width(), i-1);
				dessin.drawLine(0,i , width(), i);
				dessin.drawLine(0,i+1 , width(), i+1);
			}
			else
				dessin.drawLine(0,i, width(),i);
	}
	
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

    QPainter * dessinTrait;
    dessinTrait = new QPainter(this);
    dessinerFigure(dessinTrait);
    delete dessinTrait;
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
void Geometrie::dessinerFigure(QPainter* dessinTrait)
{
    QSvgGenerator * generator;
    generator = new QSvgGenerator;
    generator->setFileName(*nomFichierTemp);
    generator->setTitle(tr("Generation de SVG pour le tracage de geometrie"));
    generator->setDescription(tr("Sauvgarde de SVG pour la geometrie tracer."));

    dessinTrait->begin(generator);
    if(QFile::exists(*nomFichier))
    {
        QSvgRenderer * renderer;
        renderer = new QSvgRenderer(*nomFichier);
        renderer->render(dessinTrait);
        delete renderer;
    }

    for (int i = 0; i<tableauFigure.size(); i++)
    {
        Arc* monArc = dynamic_cast<Arc*> (tableauFigure[i]);
        if(monArc!=NULL)
        {
            if(monArc->getSpan() != NULL)
                dessinTrait->drawArc(monArc->getRectangle(),monArc->getStart(),monArc->getSpan());
        }
        else
        {
            Ligne* maLigne = dynamic_cast<Ligne*> (tableauFigure[i]);
            if(maLigne!=NULL)
                dessinTrait->drawLine(maLigne->getQLine());
        }
    }
    dessinTrait->end();
    delete generator;

    /*QFile sauvegardeFichier (*nomFichierTemp);
    sauvegardeFichier.copy(*nomFichier);*/
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
		regle->clic(clic,false);
	}

	if(detec == QColor(127,255,255))
	{
		//Le bouton de rotation de la règle
		regle->clic(clic,true);
	}

	//Équerre--------------------------------------------------------
	if(detec == QColor(255,255,50) || detec == QColor(255,255,152))
	{
		//Le corps de l'équerre
		equerre->clic(clic,false);
	}

	if(detec == QColor(126,255,255))
	{
		//Le bouton de rotation de l'équerre
		equerre->clic(clic,true);
	}

	//Crayon--------------------------------------------------------
	if(detec == QColor(255,255,49) || detec == QColor(255,203,96))
	{
		//Le corps du crayon
		crayon->clic(clic,false);
	}

	if(detec == QColor(125,255,255))
	{
		//Le bouton de rotation de la règle
		crayon->clic(clic,true);
	}

	//Compas--------------------------------------------------------
	if(detec == QColor(160,160,164) || detec == QColor(0,0,255))
	{
		//Le corps du crayon
		compas->clic(clic,false);
	}

	if(detec == QColor(124,255,255))
	{
		//Le bouton de rotation du crayon
		compas->clic(clic,true);
	}

	//Désélection sion clique sur un pixel blanc ou noir
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

    if(clickTxt)
    {
        txt = new QTextEdit(this);
        txt->installEventFilter(this);
		txt->setFixedHeight(35);
		txt->setFixedWidth(100);
		txt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        txt->move(clic->pos().x(), clic->pos().y());
        txt->setContextMenuPolicy(Qt::NoContextMenu);
        txt->show();
        stockTxt.push_back(txt);
        clickTxt = false;
		emit curseur();
    }
}

bool Geometrie::eventFilter(QObject * obj, QEvent * e)
{
    if(e->type() == QEvent::MouseButtonPress)
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
        if (compas->m_moveSelected || compas->m_rotateSelectedLeft || compas->m_rotateSelectedRight)
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
