#ifndef FIGURE_H
#define FIGURE_H

#include <QWidget>

class Figure : public QWidget
{
    Q_OBJECT
public:
    Figure(QWidget *parent = 0);

    inline void setFin(bool finTracer){m_finTracer = finTracer;}
    inline bool getFin(){return m_finTracer;}

private:
    bool m_finTracer;
};

#endif // FIGURE_H
