#include "ligne.h"

Ligne::Ligne(QLineF ligne)
{
    m_ligne = ligne;
}

Ligne::Ligne(QPointF numero1, QPointF numero2)
{
    m_ligne = QLineF(numero1, numero2);
}

Ligne::Ligne(double x1, double y1, double x2, double y2)
{
    m_ligne = QLineF (x1, y1, x2, y2);
}

void Ligne::setPoint1 (QPointF numero1)
{
    m_ligne.setP1(numero1);
}

void Ligne::setPoint2 (QPointF numero2)
{
    m_ligne.setP2(numero2);
}

void Ligne::setAngle (double angle)
{
    m_ligne.setAngle(angle);
}
