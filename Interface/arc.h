#ifndef ARC_H
#define ARC_H

#include "figure.h"
#include <QRectF>

class Arc : public Figure
{
public:
    Arc();
    Arc(int x, int m_positionY, int w, int h, int startAngle, int * spanAngle = NULL);
    Arc(QRectF rectangle, int startAngle, int * spanAngle = NULL);

private:
    QRectF m_rectangle;
    int m_startAngle;
    int * m_spanAngle;

public:
    inline void setRect(QRectF rectangle){m_rectangle = rectangle;}
    inline void setRect(int x, int y, int w, int h){m_rectangle = QRectF(x,y,w,h);}
    inline void setStartAngle(int startAngle){m_startAngle = startAngle;}
    inline void setSpanAngle(int * spanAngle){m_spanAngle = spanAngle;}

    inline QRectF getRectangle() {return m_rectangle;}
    inline int getStart() {return m_startAngle;}
    inline int getSpan() {return *m_spanAngle;}
};

#endif // ARC_H
