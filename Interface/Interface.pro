#-------------------------------------------------
#
# Project created by QtCreator 2014-02-06T11:48:48
#
#-------------------------------------------------

QT += core gui
QT += xml
QT += printsupport
QT += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interface
TEMPLATE = app


SOURCES += main.cpp\
    interface.cpp \
    Compas.cpp \
    Crayon.cpp \
    Equerre.cpp \
    Geometrie.cpp \
    projetgeometrie.cpp \
    Regle.cpp \
    user.cpp \
    arc.cpp \
    ligne.cpp \
    instrument.cpp \
    figure.cpp \
    point.cpp

HEADERS  += interface.h \
    Compas.h \
    Crayon.h \
    Equerre.h \
    Geometrie.h \
    projetgeometrie.h \
    Regle.h \
    user.h \
    arc.h \
    ligne.h \
    instrument.h \
    figure.h \
    arc.h \
    point.h

FORMS    += interface.ui \
    projetgeometrie.ui

OTHER_FILES += Compas.xml \
    Crayon.xml \
    Equerre.xml \
    Regle.xml \
    Utilisateurs.xml

RESOURCES += interface.qrc \
    projetgeometrie.qrc

