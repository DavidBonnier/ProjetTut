#-------------------------------------------------
#
# Project created by QtCreator 2014-02-03T10:34:50
#
#-------------------------------------------------

QT       += core gui
QT += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtSVG
TEMPLATE = app


SOURCES += main.cpp\
        svg.cpp \
    arc.cpp \
    ligne.cpp

HEADERS  += svg.h \
    arc.h \
    ligne.h

FORMS    += svg.ui
