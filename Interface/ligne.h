#ifndef LIGNE_H
#define LIGNE_H

#include <QLineF>
#include "figure.h"

class Ligne : public Figure
{
public:
    Ligne();
    Ligne(QLineF ligne);
    inline QLineF getQLine() {return m_ligne;}
    inline void setQLine(QLineF ligne) {m_ligne = ligne;}

private:
    QLineF m_ligne;
};

#endif // LIGNE_H
