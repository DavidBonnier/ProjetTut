#include "arc.h"

Arc::Arc()
{
    m_spanAngle = NULL;
}

Arc::Arc(int x, int y, int w, int h, double startAngle, double * spanAngle)
{
    m_rectangle = QRectF(x,y,w,h);
    m_startAngle = startAngle;
    m_spanAngle = spanAngle;

}


Arc::Arc(QRectF rectangle, double startAngle, double * spanAngle)
{
    m_rectangle = rectangle;
    m_startAngle = startAngle;
    m_spanAngle = spanAngle;
}
