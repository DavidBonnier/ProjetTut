///////////////////////////////////////////////////////////////////////////
//! \file arc.cpp
//!
//! \brief Création d'arc.
//!
//! Plusieurs constructeurs pour instialiser les paramètres pour tracer un arc.
//!
//! \date 01/02/2014
//! \version 1.0
///////////////////////////////////////////////////////////////////////////
#include "arc.h"

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param x, y, w, h Entier qui sont les paramètre du rectangle.
//! \param startAngle Double qui est l'angle de départ de l'arc.
//! \param spanAngle Double* qui est l'angle d'arriver de l'arc.
//!
//! \brief Constructeur d'Arc paramètre de spanAngle a NULL.
//!
//! \date 01/02/2014
///////////////////////////////////////////////////////////////////////
Arc::Arc(int x, int y, int w, int h, double startAngle, double * spanAngle)
{
    m_rectangle = QRectF(x,y,w,h);
    m_startAngle = startAngle;
    m_spanAngle = spanAngle;

}

///////////////////////////////////////////////////////////////////////
//! \author BONNIER David
//!
//! \param rectangle QRectF qui est le retangle anglobant de l'arc.
//! \param startAngle Double qui est l'angle de départ de l'arc.
//! \param spanAngle Double* qui est l'angle d'arriver de l'arc.
//!
//! \brief Constructeur d'Arc paramètre de spanAngle a NULL.
//!
//! \date 01/02/2014
///////////////////////////////////////////////////////////////////////
Arc::Arc(QRectF rectangle, double startAngle, double * spanAngle)
{
    m_rectangle = rectangle;
    m_startAngle = startAngle;
    m_spanAngle = spanAngle;
}
