#ifndef ARC_H
#define ARC_H

#include "figure.h"
#include <QRectF>

class Arc : public Figure
{
public:
    Arc();
    Arc(int x, int m_positionY, int w, int h, double startAngle, double * spanAngle = NULL);
    Arc(QRectF rectangle, double startAngle, double * spanAngle = NULL);

private:
    QRectF m_rectangle;
    double m_startAngle;
    double * m_spanAngle;

public:
    inline void setRect(QRectF rectangle){m_rectangle = rectangle;}
    inline void setRect(int x, int y, int w, int h){m_rectangle = QRectF(x,y,w,h);}
    inline void setStartAngle(double startAngle){m_startAngle = startAngle;}
    inline void setSpanAngle(double spanAngle){m_spanAngle = new double(spanAngle);}

    inline QRectF getRectangle() {return m_rectangle;}
    inline double getStart() {return m_startAngle;}
    inline double * getSpan() {return m_spanAngle;}
};

#endif // ARC_H
