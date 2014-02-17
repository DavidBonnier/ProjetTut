#ifndef LINE_H
#define LINE_H

#include <QWidget>
#include <QLineF>

class Ligne : public QWidget
{
    Q_OBJECT
public:
    Ligne(QWidget *parent = 0);
    inline QLineF* getQLine() {return line;};
    inline void setQLine(QLineF * ligne) {line = ligne;};

private:
    QLineF * line;
};

#endif // LINE_H
