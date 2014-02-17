#ifndef ARC_H
#define ARC_H

#include <QWidget>

class Arc : public QWidget
{
    Q_OBJECT
public:
    Arc(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);

private:
    int _x;
    int _y;
    int _w;
    int _h;
    int _sta;
    int _spa;

public slots:
    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
    void setStartAngle(int sta);
    void setSpanAngle(int spa);
};

#endif // ARC_H
