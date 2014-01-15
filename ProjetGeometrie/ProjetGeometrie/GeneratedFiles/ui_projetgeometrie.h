/********************************************************************************
** Form generated from reading UI file 'projetgeometrie.ui'
**
** Created: Sun 12. Jan 17:52:25 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJETGEOMETRIE_H
#define UI_PROJETGEOMETRIE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjetGeometrieClass
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *BoutonCompas;
    QPushButton *BoutonRegle;
    QPushButton *BoutonEquerre;
    QPushButton *BoutonCrayon;
    QPushButton *BoutonPleinEcran;
    QCheckBox *CheckBoxGrille;
    QPushButton *BoutonPoint;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *BoutonBleu;
    QPushButton *BoutonVert;
    QPushButton *BoutonRouge;
    QPushButton *BoutonJaune;
    QPushButton *BoutonNoir;
    QPushButton *BoutonTexte;
    QPushButton *BoutonEpaisseur;
    QSpacerItem *horizontalSpacer;
    QScrollArea *ScrollAreaOptionsOutils;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QDockWidget *DockWidgetCrayon;
    QWidget *dockWidgetContents_3;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *GroupBoxCrayonPosition;
    QHBoxLayout *horizontalLayout_3;
    QLabel *LabelPositionX;
    QDoubleSpinBox *SpinBoxCrayonPositionX;
    QLabel *LabelPositionY;
    QDoubleSpinBox *SpinBoxCrayonPositionY;
    QCheckBox *CheckBoxCrayonTransparence;
    QWidget *WidgetCrayonOrientation;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LabelCrayonOrientation;
    QSpinBox *SpinBoxCrayonOrientation;
    QFrame *line_3;
    QDockWidget *DockWidgetRegle;
    QWidget *dockWidgetContents_4;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *GroupBoxReglePosition;
    QHBoxLayout *horizontalLayout_5;
    QLabel *LabelReglePositionX;
    QDoubleSpinBox *SpinBoxReglePositionX;
    QLabel *LabelReglePotitionY;
    QDoubleSpinBox *SpinBoxReglePositionY;
    QCheckBox *CheckBoxRegleTransparence;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *LabelRegleOrientation;
    QSpinBox *SpinBoxRegleOrientation;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_7;
    QSpinBox *SpinBoxRegleTracerPoint1;
    QSpinBox *SpinBoxRegleTracerPoint2;
    QPushButton *BoutonRegleTracerOK;
    QFrame *line_2;
    QDockWidget *DockWidgetEquerre;
    QWidget *dockWidgetContents_5;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *GroupBoxEquerrePosition;
    QHBoxLayout *horizontalLayout_8;
    QLabel *LabelEquerrePositionX;
    QDoubleSpinBox *SpinBoxEquerrePositionX;
    QLabel *LabelEquerrePositionY;
    QDoubleSpinBox *SpinBoxEquerrePositionY;
    QCheckBox *CheckBoxEquerreTransparence;
    QWidget *WidgetEquerreOrientation;
    QHBoxLayout *horizontalLayout_9;
    QLabel *LabelEquerreOrientation;
    QSpinBox *SpinBoxEquerreOrientation;
    QGroupBox *GroupBoxEquerreTracer;
    QHBoxLayout *horizontalLayout_10;
    QSpinBox *SpinBoxEquerreTracerPoint1;
    QSpinBox *SpinBoxEquerreTracerPoint2;
    QPushButton *BoutonEquerreTracerOK;
    QFrame *line;
    QDockWidget *DockWidgetCompas;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *GroupBoxPositionCompas;
    QHBoxLayout *horizontalLayout_11;
    QLabel *LabelCompasPositionX;
    QDoubleSpinBox *SpinBoxCompasPositionX;
    QLabel *LabelCompasPositionY;
    QDoubleSpinBox *SpinBoxCompasPositionY;
    QCheckBox *CheckBoxCompasTransparence;
    QWidget *WidgetCompasOption;
    QFormLayout *formLayout;
    QLabel *LabelEcartementCompas;
    QSpinBox *SpinBoxCompasEcartement;
    QSpinBox *SpinBoxCompasOrientation;
    QLabel *LabelCompasOrientation;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *ProjetGeometrieClass)
    {
        if (ProjetGeometrieClass->objectName().isEmpty())
            ProjetGeometrieClass->setObjectName(QString::fromUtf8("ProjetGeometrieClass"));
        ProjetGeometrieClass->resize(891, 610);
        horizontalLayout = new QHBoxLayout(ProjetGeometrieClass);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(ProjetGeometrieClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 14, 0, 1, 1);

        BoutonCompas = new QPushButton(widget);
        BoutonCompas->setObjectName(QString::fromUtf8("BoutonCompas"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Test/Resources/compas.gif"), QSize(), QIcon::Normal, QIcon::Off);
        BoutonCompas->setIcon(icon);
        BoutonCompas->setIconSize(QSize(50, 50));
        BoutonCompas->setCheckable(true);

        gridLayout->addWidget(BoutonCompas, 5, 0, 1, 3);

        BoutonRegle = new QPushButton(widget);
        BoutonRegle->setObjectName(QString::fromUtf8("BoutonRegle"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Test/Resources/regle.gif"), QSize(), QIcon::Normal, QIcon::Off);
        BoutonRegle->setIcon(icon1);
        BoutonRegle->setIconSize(QSize(50, 50));
        BoutonRegle->setCheckable(true);

        gridLayout->addWidget(BoutonRegle, 4, 0, 1, 3);

        BoutonEquerre = new QPushButton(widget);
        BoutonEquerre->setObjectName(QString::fromUtf8("BoutonEquerre"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Test/Resources/equerre.gif"), QSize(), QIcon::Normal, QIcon::Off);
        BoutonEquerre->setIcon(icon2);
        BoutonEquerre->setIconSize(QSize(50, 50));
        BoutonEquerre->setCheckable(true);

        gridLayout->addWidget(BoutonEquerre, 3, 0, 1, 3);

        BoutonCrayon = new QPushButton(widget);
        BoutonCrayon->setObjectName(QString::fromUtf8("BoutonCrayon"));
        BoutonCrayon->setMouseTracking(false);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Test/Resources/crayon.gif"), QSize(), QIcon::Normal, QIcon::Off);
        BoutonCrayon->setIcon(icon3);
        BoutonCrayon->setIconSize(QSize(50, 50));
        BoutonCrayon->setCheckable(true);
        BoutonCrayon->setChecked(false);
        BoutonCrayon->setAutoRepeatDelay(100);
        BoutonCrayon->setAutoDefault(false);
        BoutonCrayon->setDefault(false);
        BoutonCrayon->setFlat(false);

        gridLayout->addWidget(BoutonCrayon, 2, 0, 1, 3);

        BoutonPleinEcran = new QPushButton(widget);
        BoutonPleinEcran->setObjectName(QString::fromUtf8("BoutonPleinEcran"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Test/Resources/SortieFullScreen.gif"), QSize(), QIcon::Normal, QIcon::Off);
        BoutonPleinEcran->setIcon(icon4);
        BoutonPleinEcran->setIconSize(QSize(50, 50));

        gridLayout->addWidget(BoutonPleinEcran, 1, 0, 1, 3);

        CheckBoxGrille = new QCheckBox(widget);
        CheckBoxGrille->setObjectName(QString::fromUtf8("CheckBoxGrille"));
        CheckBoxGrille->setMinimumSize(QSize(60, 30));
        CheckBoxGrille->setIconSize(QSize(30, 30));

        gridLayout->addWidget(CheckBoxGrille, 13, 0, 1, 8);

        BoutonPoint = new QPushButton(widget);
        BoutonPoint->setObjectName(QString::fromUtf8("BoutonPoint"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Test/Resources/Point.gif"), QSize(), QIcon::Normal, QIcon::Off);
        BoutonPoint->setIcon(icon5);
        BoutonPoint->setIconSize(QSize(50, 50));

        gridLayout->addWidget(BoutonPoint, 6, 0, 1, 3);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        BoutonBleu = new QPushButton(widget_6);
        BoutonBleu->setObjectName(QString::fromUtf8("BoutonBleu"));
        BoutonBleu->setMinimumSize(QSize(30, 30));
        BoutonBleu->setStyleSheet(QString::fromUtf8("background : rgb(0, 0, 255)"));

        horizontalLayout_4->addWidget(BoutonBleu);

        BoutonVert = new QPushButton(widget_6);
        BoutonVert->setObjectName(QString::fromUtf8("BoutonVert"));
        BoutonVert->setMinimumSize(QSize(30, 30));
        BoutonVert->setStyleSheet(QString::fromUtf8("background : rgb(0, 255, 0)"));

        horizontalLayout_4->addWidget(BoutonVert);

        BoutonRouge = new QPushButton(widget_6);
        BoutonRouge->setObjectName(QString::fromUtf8("BoutonRouge"));
        BoutonRouge->setEnabled(true);
        BoutonRouge->setMinimumSize(QSize(30, 30));
        BoutonRouge->setStyleSheet(QString::fromUtf8("background : rgb(255, 0, 0)"));

        horizontalLayout_4->addWidget(BoutonRouge);

        BoutonJaune = new QPushButton(widget_6);
        BoutonJaune->setObjectName(QString::fromUtf8("BoutonJaune"));
        BoutonJaune->setEnabled(true);
        BoutonJaune->setMinimumSize(QSize(30, 30));
        BoutonJaune->setStyleSheet(QString::fromUtf8("background : rgb(255, 255, 0)"));

        horizontalLayout_4->addWidget(BoutonJaune);


        gridLayout->addWidget(widget_6, 8, 1, 1, 11);

        BoutonNoir = new QPushButton(widget);
        BoutonNoir->setObjectName(QString::fromUtf8("BoutonNoir"));
        BoutonNoir->setMinimumSize(QSize(30, 30));
        BoutonNoir->setMaximumSize(QSize(30, 30));
        BoutonNoir->setStyleSheet(QString::fromUtf8("background : rgb(0, 0, 0)"));

        gridLayout->addWidget(BoutonNoir, 8, 0, 1, 1);

        BoutonTexte = new QPushButton(widget);
        BoutonTexte->setObjectName(QString::fromUtf8("BoutonTexte"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Test/Resources/T.gif"), QSize(), QIcon::Normal, QIcon::Off);
        BoutonTexte->setIcon(icon6);
        BoutonTexte->setIconSize(QSize(50, 50));

        gridLayout->addWidget(BoutonTexte, 7, 0, 1, 3);

        BoutonEpaisseur = new QPushButton(widget);
        BoutonEpaisseur->setObjectName(QString::fromUtf8("BoutonEpaisseur"));
        BoutonEpaisseur->setMinimumSize(QSize(30, 30));
        BoutonEpaisseur->setMaximumSize(QSize(30, 30));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Test/Resources/Trait.gif"), QSize(), QIcon::Normal, QIcon::Off);
        BoutonEpaisseur->setIcon(icon7);
        BoutonEpaisseur->setIconSize(QSize(25, 25));

        gridLayout->addWidget(BoutonEpaisseur, 10, 0, 3, 1);


        horizontalLayout->addWidget(widget);

        horizontalSpacer = new QSpacerItem(119, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ScrollAreaOptionsOutils = new QScrollArea(ProjetGeometrieClass);
        ScrollAreaOptionsOutils->setObjectName(QString::fromUtf8("ScrollAreaOptionsOutils"));
        ScrollAreaOptionsOutils->setMinimumSize(QSize(230, 0));
        ScrollAreaOptionsOutils->setMaximumSize(QSize(230, 16777215));
        ScrollAreaOptionsOutils->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -279, 211, 871));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        DockWidgetCrayon = new QDockWidget(scrollAreaWidgetContents);
        DockWidgetCrayon->setObjectName(QString::fromUtf8("DockWidgetCrayon"));
        DockWidgetCrayon->setEnabled(true);
        DockWidgetCrayon->setMinimumSize(QSize(174, 160));
        DockWidgetCrayon->setMaximumSize(QSize(200, 524287));
        DockWidgetCrayon->setLayoutDirection(Qt::LeftToRight);
        DockWidgetCrayon->setAutoFillBackground(false);
        DockWidgetCrayon->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        DockWidgetCrayon->setFloating(false);
        DockWidgetCrayon->setFeatures(QDockWidget::AllDockWidgetFeatures);
        DockWidgetCrayon->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        GroupBoxCrayonPosition = new QGroupBox(dockWidgetContents_3);
        GroupBoxCrayonPosition->setObjectName(QString::fromUtf8("GroupBoxCrayonPosition"));
        horizontalLayout_3 = new QHBoxLayout(GroupBoxCrayonPosition);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        LabelPositionX = new QLabel(GroupBoxCrayonPosition);
        LabelPositionX->setObjectName(QString::fromUtf8("LabelPositionX"));

        horizontalLayout_3->addWidget(LabelPositionX);

        SpinBoxCrayonPositionX = new QDoubleSpinBox(GroupBoxCrayonPosition);
        SpinBoxCrayonPositionX->setObjectName(QString::fromUtf8("SpinBoxCrayonPositionX"));
        SpinBoxCrayonPositionX->setDecimals(1);

        horizontalLayout_3->addWidget(SpinBoxCrayonPositionX);

        LabelPositionY = new QLabel(GroupBoxCrayonPosition);
        LabelPositionY->setObjectName(QString::fromUtf8("LabelPositionY"));

        horizontalLayout_3->addWidget(LabelPositionY);

        SpinBoxCrayonPositionY = new QDoubleSpinBox(GroupBoxCrayonPosition);
        SpinBoxCrayonPositionY->setObjectName(QString::fromUtf8("SpinBoxCrayonPositionY"));
        SpinBoxCrayonPositionY->setDecimals(1);

        horizontalLayout_3->addWidget(SpinBoxCrayonPositionY);


        verticalLayout_3->addWidget(GroupBoxCrayonPosition);

        CheckBoxCrayonTransparence = new QCheckBox(dockWidgetContents_3);
        CheckBoxCrayonTransparence->setObjectName(QString::fromUtf8("CheckBoxCrayonTransparence"));

        verticalLayout_3->addWidget(CheckBoxCrayonTransparence);

        WidgetCrayonOrientation = new QWidget(dockWidgetContents_3);
        WidgetCrayonOrientation->setObjectName(QString::fromUtf8("WidgetCrayonOrientation"));
        horizontalLayout_2 = new QHBoxLayout(WidgetCrayonOrientation);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        LabelCrayonOrientation = new QLabel(WidgetCrayonOrientation);
        LabelCrayonOrientation->setObjectName(QString::fromUtf8("LabelCrayonOrientation"));

        horizontalLayout_2->addWidget(LabelCrayonOrientation);

        SpinBoxCrayonOrientation = new QSpinBox(WidgetCrayonOrientation);
        SpinBoxCrayonOrientation->setObjectName(QString::fromUtf8("SpinBoxCrayonOrientation"));
        SpinBoxCrayonOrientation->setMaximum(360);

        horizontalLayout_2->addWidget(SpinBoxCrayonOrientation);

        SpinBoxCrayonOrientation->raise();
        LabelCrayonOrientation->raise();

        verticalLayout_3->addWidget(WidgetCrayonOrientation);

        DockWidgetCrayon->setWidget(dockWidgetContents_3);

        verticalLayout_4->addWidget(DockWidgetCrayon);

        line_3 = new QFrame(scrollAreaWidgetContents);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_3);

        DockWidgetRegle = new QDockWidget(scrollAreaWidgetContents);
        DockWidgetRegle->setObjectName(QString::fromUtf8("DockWidgetRegle"));
        DockWidgetRegle->setEnabled(true);
        DockWidgetRegle->setMinimumSize(QSize(174, 222));
        DockWidgetRegle->setMaximumSize(QSize(200, 524287));
        DockWidgetRegle->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);"));
        DockWidgetRegle->setFloating(false);
        DockWidgetRegle->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        verticalLayout_6 = new QVBoxLayout(dockWidgetContents_4);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        GroupBoxReglePosition = new QGroupBox(dockWidgetContents_4);
        GroupBoxReglePosition->setObjectName(QString::fromUtf8("GroupBoxReglePosition"));
        horizontalLayout_5 = new QHBoxLayout(GroupBoxReglePosition);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        LabelReglePositionX = new QLabel(GroupBoxReglePosition);
        LabelReglePositionX->setObjectName(QString::fromUtf8("LabelReglePositionX"));

        horizontalLayout_5->addWidget(LabelReglePositionX);

        SpinBoxReglePositionX = new QDoubleSpinBox(GroupBoxReglePosition);
        SpinBoxReglePositionX->setObjectName(QString::fromUtf8("SpinBoxReglePositionX"));
        SpinBoxReglePositionX->setDecimals(1);

        horizontalLayout_5->addWidget(SpinBoxReglePositionX);

        LabelReglePotitionY = new QLabel(GroupBoxReglePosition);
        LabelReglePotitionY->setObjectName(QString::fromUtf8("LabelReglePotitionY"));

        horizontalLayout_5->addWidget(LabelReglePotitionY);

        SpinBoxReglePositionY = new QDoubleSpinBox(GroupBoxReglePosition);
        SpinBoxReglePositionY->setObjectName(QString::fromUtf8("SpinBoxReglePositionY"));
        SpinBoxReglePositionY->setDecimals(1);

        horizontalLayout_5->addWidget(SpinBoxReglePositionY);


        verticalLayout_6->addWidget(GroupBoxReglePosition);

        CheckBoxRegleTransparence = new QCheckBox(dockWidgetContents_4);
        CheckBoxRegleTransparence->setObjectName(QString::fromUtf8("CheckBoxRegleTransparence"));

        verticalLayout_6->addWidget(CheckBoxRegleTransparence);

        widget_3 = new QWidget(dockWidgetContents_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_6 = new QHBoxLayout(widget_3);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        LabelRegleOrientation = new QLabel(widget_3);
        LabelRegleOrientation->setObjectName(QString::fromUtf8("LabelRegleOrientation"));

        horizontalLayout_6->addWidget(LabelRegleOrientation);

        SpinBoxRegleOrientation = new QSpinBox(widget_3);
        SpinBoxRegleOrientation->setObjectName(QString::fromUtf8("SpinBoxRegleOrientation"));
        SpinBoxRegleOrientation->setMaximum(360);

        horizontalLayout_6->addWidget(SpinBoxRegleOrientation);


        verticalLayout_6->addWidget(widget_3);

        groupBox_4 = new QGroupBox(dockWidgetContents_4);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_4);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        SpinBoxRegleTracerPoint1 = new QSpinBox(groupBox_4);
        SpinBoxRegleTracerPoint1->setObjectName(QString::fromUtf8("SpinBoxRegleTracerPoint1"));

        horizontalLayout_7->addWidget(SpinBoxRegleTracerPoint1);

        SpinBoxRegleTracerPoint2 = new QSpinBox(groupBox_4);
        SpinBoxRegleTracerPoint2->setObjectName(QString::fromUtf8("SpinBoxRegleTracerPoint2"));

        horizontalLayout_7->addWidget(SpinBoxRegleTracerPoint2);

        BoutonRegleTracerOK = new QPushButton(groupBox_4);
        BoutonRegleTracerOK->setObjectName(QString::fromUtf8("BoutonRegleTracerOK"));
        BoutonRegleTracerOK->setMaximumSize(QSize(30, 30));

        horizontalLayout_7->addWidget(BoutonRegleTracerOK);


        verticalLayout_6->addWidget(groupBox_4);

        DockWidgetRegle->setWidget(dockWidgetContents_4);

        verticalLayout_4->addWidget(DockWidgetRegle);

        line_2 = new QFrame(scrollAreaWidgetContents);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_2);

        DockWidgetEquerre = new QDockWidget(scrollAreaWidgetContents);
        DockWidgetEquerre->setObjectName(QString::fromUtf8("DockWidgetEquerre"));
        DockWidgetEquerre->setMinimumSize(QSize(174, 222));
        DockWidgetEquerre->setMaximumSize(QSize(200, 524287));
        DockWidgetEquerre->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 0);"));
        DockWidgetEquerre->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QString::fromUtf8("dockWidgetContents_5"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_5);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        GroupBoxEquerrePosition = new QGroupBox(dockWidgetContents_5);
        GroupBoxEquerrePosition->setObjectName(QString::fromUtf8("GroupBoxEquerrePosition"));
        horizontalLayout_8 = new QHBoxLayout(GroupBoxEquerrePosition);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        LabelEquerrePositionX = new QLabel(GroupBoxEquerrePosition);
        LabelEquerrePositionX->setObjectName(QString::fromUtf8("LabelEquerrePositionX"));

        horizontalLayout_8->addWidget(LabelEquerrePositionX);

        SpinBoxEquerrePositionX = new QDoubleSpinBox(GroupBoxEquerrePosition);
        SpinBoxEquerrePositionX->setObjectName(QString::fromUtf8("SpinBoxEquerrePositionX"));
        SpinBoxEquerrePositionX->setDecimals(1);

        horizontalLayout_8->addWidget(SpinBoxEquerrePositionX);

        LabelEquerrePositionY = new QLabel(GroupBoxEquerrePosition);
        LabelEquerrePositionY->setObjectName(QString::fromUtf8("LabelEquerrePositionY"));

        horizontalLayout_8->addWidget(LabelEquerrePositionY);

        SpinBoxEquerrePositionY = new QDoubleSpinBox(GroupBoxEquerrePosition);
        SpinBoxEquerrePositionY->setObjectName(QString::fromUtf8("SpinBoxEquerrePositionY"));
        SpinBoxEquerrePositionY->setDecimals(1);

        horizontalLayout_8->addWidget(SpinBoxEquerrePositionY);


        verticalLayout_2->addWidget(GroupBoxEquerrePosition);

        CheckBoxEquerreTransparence = new QCheckBox(dockWidgetContents_5);
        CheckBoxEquerreTransparence->setObjectName(QString::fromUtf8("CheckBoxEquerreTransparence"));

        verticalLayout_2->addWidget(CheckBoxEquerreTransparence);

        WidgetEquerreOrientation = new QWidget(dockWidgetContents_5);
        WidgetEquerreOrientation->setObjectName(QString::fromUtf8("WidgetEquerreOrientation"));
        horizontalLayout_9 = new QHBoxLayout(WidgetEquerreOrientation);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        LabelEquerreOrientation = new QLabel(WidgetEquerreOrientation);
        LabelEquerreOrientation->setObjectName(QString::fromUtf8("LabelEquerreOrientation"));

        horizontalLayout_9->addWidget(LabelEquerreOrientation);

        SpinBoxEquerreOrientation = new QSpinBox(WidgetEquerreOrientation);
        SpinBoxEquerreOrientation->setObjectName(QString::fromUtf8("SpinBoxEquerreOrientation"));
        SpinBoxEquerreOrientation->setMaximum(360);

        horizontalLayout_9->addWidget(SpinBoxEquerreOrientation);


        verticalLayout_2->addWidget(WidgetEquerreOrientation);

        GroupBoxEquerreTracer = new QGroupBox(dockWidgetContents_5);
        GroupBoxEquerreTracer->setObjectName(QString::fromUtf8("GroupBoxEquerreTracer"));
        horizontalLayout_10 = new QHBoxLayout(GroupBoxEquerreTracer);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        SpinBoxEquerreTracerPoint1 = new QSpinBox(GroupBoxEquerreTracer);
        SpinBoxEquerreTracerPoint1->setObjectName(QString::fromUtf8("SpinBoxEquerreTracerPoint1"));

        horizontalLayout_10->addWidget(SpinBoxEquerreTracerPoint1);

        SpinBoxEquerreTracerPoint2 = new QSpinBox(GroupBoxEquerreTracer);
        SpinBoxEquerreTracerPoint2->setObjectName(QString::fromUtf8("SpinBoxEquerreTracerPoint2"));

        horizontalLayout_10->addWidget(SpinBoxEquerreTracerPoint2);

        BoutonEquerreTracerOK = new QPushButton(GroupBoxEquerreTracer);
        BoutonEquerreTracerOK->setObjectName(QString::fromUtf8("BoutonEquerreTracerOK"));
        BoutonEquerreTracerOK->setMaximumSize(QSize(30, 30));

        horizontalLayout_10->addWidget(BoutonEquerreTracerOK);


        verticalLayout_2->addWidget(GroupBoxEquerreTracer);

        DockWidgetEquerre->setWidget(dockWidgetContents_5);

        verticalLayout_4->addWidget(DockWidgetEquerre);

        line = new QFrame(scrollAreaWidgetContents);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        DockWidgetCompas = new QDockWidget(scrollAreaWidgetContents);
        DockWidgetCompas->setObjectName(QString::fromUtf8("DockWidgetCompas"));
        DockWidgetCompas->setMinimumSize(QSize(174, 198));
        DockWidgetCompas->setMaximumSize(QSize(200, 524287));
        DockWidgetCompas->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);"));
        DockWidgetCompas->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_5 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        GroupBoxPositionCompas = new QGroupBox(dockWidgetContents_2);
        GroupBoxPositionCompas->setObjectName(QString::fromUtf8("GroupBoxPositionCompas"));
        horizontalLayout_11 = new QHBoxLayout(GroupBoxPositionCompas);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        LabelCompasPositionX = new QLabel(GroupBoxPositionCompas);
        LabelCompasPositionX->setObjectName(QString::fromUtf8("LabelCompasPositionX"));

        horizontalLayout_11->addWidget(LabelCompasPositionX);

        SpinBoxCompasPositionX = new QDoubleSpinBox(GroupBoxPositionCompas);
        SpinBoxCompasPositionX->setObjectName(QString::fromUtf8("SpinBoxCompasPositionX"));
        SpinBoxCompasPositionX->setDecimals(1);

        horizontalLayout_11->addWidget(SpinBoxCompasPositionX);

        LabelCompasPositionY = new QLabel(GroupBoxPositionCompas);
        LabelCompasPositionY->setObjectName(QString::fromUtf8("LabelCompasPositionY"));

        horizontalLayout_11->addWidget(LabelCompasPositionY);

        SpinBoxCompasPositionY = new QDoubleSpinBox(GroupBoxPositionCompas);
        SpinBoxCompasPositionY->setObjectName(QString::fromUtf8("SpinBoxCompasPositionY"));
        SpinBoxCompasPositionY->setDecimals(1);

        horizontalLayout_11->addWidget(SpinBoxCompasPositionY);


        verticalLayout_5->addWidget(GroupBoxPositionCompas);

        CheckBoxCompasTransparence = new QCheckBox(dockWidgetContents_2);
        CheckBoxCompasTransparence->setObjectName(QString::fromUtf8("CheckBoxCompasTransparence"));

        verticalLayout_5->addWidget(CheckBoxCompasTransparence);

        WidgetCompasOption = new QWidget(dockWidgetContents_2);
        WidgetCompasOption->setObjectName(QString::fromUtf8("WidgetCompasOption"));
        WidgetCompasOption->setEnabled(true);
        formLayout = new QFormLayout(WidgetCompasOption);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        LabelEcartementCompas = new QLabel(WidgetCompasOption);
        LabelEcartementCompas->setObjectName(QString::fromUtf8("LabelEcartementCompas"));

        formLayout->setWidget(1, QFormLayout::LabelRole, LabelEcartementCompas);

        SpinBoxCompasEcartement = new QSpinBox(WidgetCompasOption);
        SpinBoxCompasEcartement->setObjectName(QString::fromUtf8("SpinBoxCompasEcartement"));

        formLayout->setWidget(1, QFormLayout::FieldRole, SpinBoxCompasEcartement);

        SpinBoxCompasOrientation = new QSpinBox(WidgetCompasOption);
        SpinBoxCompasOrientation->setObjectName(QString::fromUtf8("SpinBoxCompasOrientation"));
        SpinBoxCompasOrientation->setMaximum(360);

        formLayout->setWidget(3, QFormLayout::FieldRole, SpinBoxCompasOrientation);

        LabelCompasOrientation = new QLabel(WidgetCompasOption);
        LabelCompasOrientation->setObjectName(QString::fromUtf8("LabelCompasOrientation"));

        formLayout->setWidget(3, QFormLayout::LabelRole, LabelCompasOrientation);


        verticalLayout_5->addWidget(WidgetCompasOption);

        DockWidgetCompas->setWidget(dockWidgetContents_2);

        verticalLayout_4->addWidget(DockWidgetCompas);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        ScrollAreaOptionsOutils->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(ScrollAreaOptionsOutils);


        retranslateUi(ProjetGeometrieClass);

        QMetaObject::connectSlotsByName(ProjetGeometrieClass);
    } // setupUi

    void retranslateUi(QWidget *ProjetGeometrieClass)
    {
        ProjetGeometrieClass->setWindowTitle(QApplication::translate("ProjetGeometrieClass", "ProjetGeometrie", 0, QApplication::UnicodeUTF8));
        BoutonRegle->setText(QString());
        BoutonEquerre->setText(QString());
        BoutonCrayon->setText(QString());
        CheckBoxGrille->setText(QApplication::translate("ProjetGeometrieClass", "Grille", 0, QApplication::UnicodeUTF8));
        BoutonPoint->setText(QString());
        BoutonBleu->setText(QString());
        BoutonVert->setText(QString());
        BoutonRouge->setText(QString());
        BoutonJaune->setText(QString());
        BoutonNoir->setText(QString());
        BoutonTexte->setText(QString());
        BoutonEpaisseur->setText(QString());
        DockWidgetCrayon->setWindowTitle(QApplication::translate("ProjetGeometrieClass", "Crayon", 0, QApplication::UnicodeUTF8));
        GroupBoxCrayonPosition->setTitle(QApplication::translate("ProjetGeometrieClass", "Position", 0, QApplication::UnicodeUTF8));
        LabelPositionX->setText(QApplication::translate("ProjetGeometrieClass", "x", 0, QApplication::UnicodeUTF8));
        LabelPositionY->setText(QApplication::translate("ProjetGeometrieClass", "y", 0, QApplication::UnicodeUTF8));
        CheckBoxCrayonTransparence->setText(QApplication::translate("ProjetGeometrieClass", "transparence", 0, QApplication::UnicodeUTF8));
        LabelCrayonOrientation->setText(QApplication::translate("ProjetGeometrieClass", "Orientation", 0, QApplication::UnicodeUTF8));
        DockWidgetRegle->setWindowTitle(QApplication::translate("ProjetGeometrieClass", "R\303\250gle", 0, QApplication::UnicodeUTF8));
        GroupBoxReglePosition->setTitle(QApplication::translate("ProjetGeometrieClass", "Position", 0, QApplication::UnicodeUTF8));
        LabelReglePositionX->setText(QApplication::translate("ProjetGeometrieClass", "x", 0, QApplication::UnicodeUTF8));
        LabelReglePotitionY->setText(QApplication::translate("ProjetGeometrieClass", "y", 0, QApplication::UnicodeUTF8));
        CheckBoxRegleTransparence->setText(QApplication::translate("ProjetGeometrieClass", "transparence", 0, QApplication::UnicodeUTF8));
        LabelRegleOrientation->setText(QApplication::translate("ProjetGeometrieClass", "Orientation", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("ProjetGeometrieClass", "Tracer", 0, QApplication::UnicodeUTF8));
        BoutonRegleTracerOK->setText(QApplication::translate("ProjetGeometrieClass", "OK", 0, QApplication::UnicodeUTF8));
        DockWidgetEquerre->setWindowTitle(QApplication::translate("ProjetGeometrieClass", "Equerre", 0, QApplication::UnicodeUTF8));
        GroupBoxEquerrePosition->setTitle(QApplication::translate("ProjetGeometrieClass", "Position", 0, QApplication::UnicodeUTF8));
        LabelEquerrePositionX->setText(QApplication::translate("ProjetGeometrieClass", "x", 0, QApplication::UnicodeUTF8));
        LabelEquerrePositionY->setText(QApplication::translate("ProjetGeometrieClass", "y", 0, QApplication::UnicodeUTF8));
        CheckBoxEquerreTransparence->setText(QApplication::translate("ProjetGeometrieClass", "transparence", 0, QApplication::UnicodeUTF8));
        LabelEquerreOrientation->setText(QApplication::translate("ProjetGeometrieClass", "Orientation", 0, QApplication::UnicodeUTF8));
        GroupBoxEquerreTracer->setTitle(QApplication::translate("ProjetGeometrieClass", "Tracer", 0, QApplication::UnicodeUTF8));
        BoutonEquerreTracerOK->setText(QApplication::translate("ProjetGeometrieClass", "OK", 0, QApplication::UnicodeUTF8));
        DockWidgetCompas->setWindowTitle(QApplication::translate("ProjetGeometrieClass", "Compas", 0, QApplication::UnicodeUTF8));
        GroupBoxPositionCompas->setTitle(QApplication::translate("ProjetGeometrieClass", "Position", 0, QApplication::UnicodeUTF8));
        LabelCompasPositionX->setText(QApplication::translate("ProjetGeometrieClass", "x", 0, QApplication::UnicodeUTF8));
        LabelCompasPositionY->setText(QApplication::translate("ProjetGeometrieClass", "y", 0, QApplication::UnicodeUTF8));
        CheckBoxCompasTransparence->setText(QApplication::translate("ProjetGeometrieClass", "transparence", 0, QApplication::UnicodeUTF8));
        LabelEcartementCompas->setText(QApplication::translate("ProjetGeometrieClass", "Ecartement", 0, QApplication::UnicodeUTF8));
        LabelCompasOrientation->setText(QApplication::translate("ProjetGeometrieClass", "Orientation", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProjetGeometrieClass: public Ui_ProjetGeometrieClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJETGEOMETRIE_H
