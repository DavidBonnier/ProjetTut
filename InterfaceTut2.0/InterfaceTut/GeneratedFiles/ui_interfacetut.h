/********************************************************************************
** Form generated from reading UI file 'interfacetut.ui'
**
** Created: Mon 13. Jan 15:30:26 2014
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACETUT_H
#define UI_INTERFACETUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InterfaceClass
{
public:
    QAction *actionNouvel_Utilisateur;
    QAction *actionChanger_d_Utilisateur;
    QAction *actionSupprimer_un_Utilisateur;
    QAction *actionSauvegarder;
    QAction *actionSauvegarder_Sous;
    QAction *actionMise_en_Page;
    QAction *actionApercu_avant_impression;
    QAction *actionImprimer;
    QAction *actionQuitter;
    QAction *actionAnnuler;
    QAction *actionRefaire;
    QAction *actionCopier;
    QAction *actionColler;
    QAction *actionCouper;
    QAction *actionRaccourcis_Clavier;
    QAction *actionPrise_en_main_du_logiciel;
    QAction *actionGrille;
    QAction *actionContraste;
    QAction *actionR_glages_magn_tisme;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_9;
    QTabWidget *Onglets;
    QWidget *Cours;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_21;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *horizontalSpacer_24;
    QSpacerItem *horizontalSpacer_25;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *horizontalSpacer_27;
    QPushButton *PleinEcranCours;
    QSpacerItem *horizontalSpacer_28;
    QSpacerItem *horizontalSpacer_29;
    QSpacerItem *verticalSpacer_5;
    QWidget *Exo;
    QGridLayout *gridLayout_7;
    QPushButton *PleinEcranExo;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_30;
    QWidget *Eval;
    QGridLayout *gridLayout_8;
    QSpacerItem *verticalSpacer_7;
    QPushButton *PleinEcranEval;
    QSpacerItem *horizontalSpacer_31;
    QGridLayout *gridLayout_9;
    QWidget *Geom;
    QGridLayout *gridLayout_10;
    QPushButton *GeomPleinEcran;
    QSpacerItem *horizontalSpacer_32;
    QSpacerItem *horizontalSpacer_33;
    QSpacerItem *horizontalSpacer_34;
    QSpacerItem *horizontalSpacer_35;
    QSpacerItem *horizontalSpacer_36;
    QSpacerItem *horizontalSpacer_37;
    QSpacerItem *horizontalSpacer_38;
    QSpacerItem *horizontalSpacer_39;
    QSpacerItem *horizontalSpacer_40;
    QSpacerItem *verticalSpacer_8;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuOptions;
    QMenu *menuAide;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InterfaceClass)
    {
        if (InterfaceClass->objectName().isEmpty())
            InterfaceClass->setObjectName(QString::fromUtf8("InterfaceClass"));
        InterfaceClass->resize(1122, 778);
        actionNouvel_Utilisateur = new QAction(InterfaceClass);
        actionNouvel_Utilisateur->setObjectName(QString::fromUtf8("actionNouvel_Utilisateur"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("Resources/ajouterUti.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNouvel_Utilisateur->setIcon(icon);
        actionChanger_d_Utilisateur = new QAction(InterfaceClass);
        actionChanger_d_Utilisateur->setObjectName(QString::fromUtf8("actionChanger_d_Utilisateur"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("Resources/modif_uti.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionChanger_d_Utilisateur->setIcon(icon1);
        actionSupprimer_un_Utilisateur = new QAction(InterfaceClass);
        actionSupprimer_un_Utilisateur->setObjectName(QString::fromUtf8("actionSupprimer_un_Utilisateur"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("Resources/supprUti.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSupprimer_un_Utilisateur->setIcon(icon2);
        actionSauvegarder = new QAction(InterfaceClass);
        actionSauvegarder->setObjectName(QString::fromUtf8("actionSauvegarder"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("Resources/sauver.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSauvegarder->setIcon(icon3);
        actionSauvegarder_Sous = new QAction(InterfaceClass);
        actionSauvegarder_Sous->setObjectName(QString::fromUtf8("actionSauvegarder_Sous"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("Resources/sauver_sous.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSauvegarder_Sous->setIcon(icon4);
        actionMise_en_Page = new QAction(InterfaceClass);
        actionMise_en_Page->setObjectName(QString::fromUtf8("actionMise_en_Page"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("Resources/miseEnPage.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMise_en_Page->setIcon(icon5);
        actionApercu_avant_impression = new QAction(InterfaceClass);
        actionApercu_avant_impression->setObjectName(QString::fromUtf8("actionApercu_avant_impression"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("Resources/apercuImpression.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionApercu_avant_impression->setIcon(icon6);
        actionImprimer = new QAction(InterfaceClass);
        actionImprimer->setObjectName(QString::fromUtf8("actionImprimer"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("Resources/imprimer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImprimer->setIcon(icon7);
        actionQuitter = new QAction(InterfaceClass);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("Resources/quitter.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuitter->setIcon(icon8);
        actionAnnuler = new QAction(InterfaceClass);
        actionAnnuler->setObjectName(QString::fromUtf8("actionAnnuler"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("Resources/annuler.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAnnuler->setIcon(icon9);
        actionRefaire = new QAction(InterfaceClass);
        actionRefaire->setObjectName(QString::fromUtf8("actionRefaire"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("Resources/refaire.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRefaire->setIcon(icon10);
        actionCopier = new QAction(InterfaceClass);
        actionCopier->setObjectName(QString::fromUtf8("actionCopier"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("Resources/copier.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopier->setIcon(icon11);
        actionColler = new QAction(InterfaceClass);
        actionColler->setObjectName(QString::fromUtf8("actionColler"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("Resources/coller.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionColler->setIcon(icon12);
        actionCouper = new QAction(InterfaceClass);
        actionCouper->setObjectName(QString::fromUtf8("actionCouper"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8("Resources/couper.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCouper->setIcon(icon13);
        actionRaccourcis_Clavier = new QAction(InterfaceClass);
        actionRaccourcis_Clavier->setObjectName(QString::fromUtf8("actionRaccourcis_Clavier"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8("Resources/raccourcisClavier.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRaccourcis_Clavier->setIcon(icon14);
        actionPrise_en_main_du_logiciel = new QAction(InterfaceClass);
        actionPrise_en_main_du_logiciel->setObjectName(QString::fromUtf8("actionPrise_en_main_du_logiciel"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8("Resources/aide.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrise_en_main_du_logiciel->setIcon(icon15);
        actionGrille = new QAction(InterfaceClass);
        actionGrille->setObjectName(QString::fromUtf8("actionGrille"));
        actionGrille->setCheckable(true);
        actionContraste = new QAction(InterfaceClass);
        actionContraste->setObjectName(QString::fromUtf8("actionContraste"));
        actionR_glages_magn_tisme = new QAction(InterfaceClass);
        actionR_glages_magn_tisme->setObjectName(QString::fromUtf8("actionR_glages_magn_tisme"));
        centralWidget = new QWidget(InterfaceClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        Onglets = new QTabWidget(centralWidget);
        Onglets->setObjectName(QString::fromUtf8("Onglets"));
        Onglets->setMinimumSize(QSize(540, 671));
        Onglets->setTabShape(QTabWidget::Rounded);
        Cours = new QWidget();
        Cours->setObjectName(QString::fromUtf8("Cours"));
        gridLayout_6 = new QGridLayout(Cours);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_21, 0, 1, 1, 1);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_22, 0, 3, 1, 1);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_23, 0, 5, 1, 1);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_24, 0, 6, 1, 1);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_25, 0, 2, 1, 1);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_26, 0, 0, 1, 1);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_27, 0, 7, 1, 1);

        PleinEcranCours = new QPushButton(Cours);
        PleinEcranCours->setObjectName(QString::fromUtf8("PleinEcranCours"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8("Resources/Fullscreen.gif"), QSize(), QIcon::Normal, QIcon::Off);
        PleinEcranCours->setIcon(icon16);
        PleinEcranCours->setIconSize(QSize(32, 32));

        gridLayout_6->addWidget(PleinEcranCours, 0, 9, 1, 1);

        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_28, 0, 8, 1, 1);

        horizontalSpacer_29 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_29, 0, 4, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_5, 1, 7, 1, 1);

        Onglets->addTab(Cours, QString());
        Exo = new QWidget();
        Exo->setObjectName(QString::fromUtf8("Exo"));
        gridLayout_7 = new QGridLayout(Exo);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        PleinEcranExo = new QPushButton(Exo);
        PleinEcranExo->setObjectName(QString::fromUtf8("PleinEcranExo"));
        PleinEcranExo->setIcon(icon16);
        PleinEcranExo->setIconSize(QSize(32, 32));

        gridLayout_7->addWidget(PleinEcranExo, 0, 1, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_6, 1, 1, 1, 1);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_30, 0, 0, 1, 1);

        Onglets->addTab(Exo, QString());
        Eval = new QWidget();
        Eval->setObjectName(QString::fromUtf8("Eval"));
        gridLayout_8 = new QGridLayout(Eval);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer_7, 1, 1, 1, 1);

        PleinEcranEval = new QPushButton(Eval);
        PleinEcranEval->setObjectName(QString::fromUtf8("PleinEcranEval"));
        PleinEcranEval->setIcon(icon16);
        PleinEcranEval->setIconSize(QSize(32, 32));

        gridLayout_8->addWidget(PleinEcranEval, 0, 1, 1, 1);

        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_31, 0, 0, 1, 1);

        Onglets->addTab(Eval, QString());

        horizontalLayout_9->addWidget(Onglets);


        horizontalLayout->addLayout(horizontalLayout_9);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        Geom = new QWidget(centralWidget);
        Geom->setObjectName(QString::fromUtf8("Geom"));
        Geom->setMinimumSize(QSize(549, 689));
        gridLayout_10 = new QGridLayout(Geom);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        GeomPleinEcran = new QPushButton(Geom);
        GeomPleinEcran->setObjectName(QString::fromUtf8("GeomPleinEcran"));
        GeomPleinEcran->setIcon(icon16);
        GeomPleinEcran->setIconSize(QSize(32, 32));

        gridLayout_10->addWidget(GeomPleinEcran, 0, 9, 1, 1);

        horizontalSpacer_32 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_32, 0, 0, 1, 1);

        horizontalSpacer_33 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_33, 0, 1, 1, 1);

        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_34, 0, 2, 1, 1);

        horizontalSpacer_35 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_35, 0, 3, 1, 1);

        horizontalSpacer_36 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_36, 0, 4, 1, 1);

        horizontalSpacer_37 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_37, 0, 5, 1, 1);

        horizontalSpacer_38 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_38, 0, 6, 1, 1);

        horizontalSpacer_39 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_39, 0, 7, 1, 1);

        horizontalSpacer_40 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_10->addItem(horizontalSpacer_40, 0, 8, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_10->addItem(verticalSpacer_8, 1, 7, 1, 1);


        gridLayout_9->addWidget(Geom, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_9);

        InterfaceClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(InterfaceClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1122, 26));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuEdition = new QMenu(menuBar);
        menuEdition->setObjectName(QString::fromUtf8("menuEdition"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuAide = new QMenu(menuBar);
        menuAide->setObjectName(QString::fromUtf8("menuAide"));
        InterfaceClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InterfaceClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        InterfaceClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(InterfaceClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        InterfaceClass->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuEdition->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuAide->menuAction());
        menuFichier->addAction(actionNouvel_Utilisateur);
        menuFichier->addAction(actionChanger_d_Utilisateur);
        menuFichier->addAction(actionSupprimer_un_Utilisateur);
        menuFichier->addSeparator();
        menuFichier->addAction(actionSauvegarder);
        menuFichier->addAction(actionSauvegarder_Sous);
        menuFichier->addSeparator();
        menuFichier->addAction(actionMise_en_Page);
        menuFichier->addAction(actionApercu_avant_impression);
        menuFichier->addAction(actionImprimer);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);
        menuEdition->addAction(actionAnnuler);
        menuEdition->addAction(actionRefaire);
        menuEdition->addSeparator();
        menuEdition->addAction(actionCopier);
        menuEdition->addAction(actionColler);
        menuEdition->addAction(actionCouper);
        menuOptions->addAction(actionGrille);
        menuOptions->addAction(actionContraste);
        menuOptions->addAction(actionR_glages_magn_tisme);
        menuAide->addAction(actionRaccourcis_Clavier);
        menuAide->addAction(actionPrise_en_main_du_logiciel);

        retranslateUi(InterfaceClass);

        Onglets->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InterfaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *InterfaceClass)
    {
        InterfaceClass->setWindowTitle(QApplication::translate("InterfaceClass", "InterfaceTut", 0, QApplication::UnicodeUTF8));
        actionNouvel_Utilisateur->setText(QApplication::translate("InterfaceClass", "Nouvel Utilisateur", 0, QApplication::UnicodeUTF8));
        actionChanger_d_Utilisateur->setText(QApplication::translate("InterfaceClass", "Changer d'Utilisateur", 0, QApplication::UnicodeUTF8));
        actionSupprimer_un_Utilisateur->setText(QApplication::translate("InterfaceClass", "Supprimer un Utilisateur", 0, QApplication::UnicodeUTF8));
        actionSauvegarder->setText(QApplication::translate("InterfaceClass", "Sauvegarder", 0, QApplication::UnicodeUTF8));
        actionSauvegarder_Sous->setText(QApplication::translate("InterfaceClass", "Sauvegarder Sous", 0, QApplication::UnicodeUTF8));
        actionMise_en_Page->setText(QApplication::translate("InterfaceClass", "Mise en Page", 0, QApplication::UnicodeUTF8));
        actionApercu_avant_impression->setText(QApplication::translate("InterfaceClass", "Apercu avant impression", 0, QApplication::UnicodeUTF8));
        actionImprimer->setText(QApplication::translate("InterfaceClass", "Imprimer", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("InterfaceClass", "Quitter", 0, QApplication::UnicodeUTF8));
        actionAnnuler->setText(QApplication::translate("InterfaceClass", "Annuler", 0, QApplication::UnicodeUTF8));
        actionRefaire->setText(QApplication::translate("InterfaceClass", "Refaire", 0, QApplication::UnicodeUTF8));
        actionCopier->setText(QApplication::translate("InterfaceClass", "Copier", 0, QApplication::UnicodeUTF8));
        actionColler->setText(QApplication::translate("InterfaceClass", "Coller", 0, QApplication::UnicodeUTF8));
        actionCouper->setText(QApplication::translate("InterfaceClass", "Couper", 0, QApplication::UnicodeUTF8));
        actionRaccourcis_Clavier->setText(QApplication::translate("InterfaceClass", "Raccourcis Clavier", 0, QApplication::UnicodeUTF8));
        actionPrise_en_main_du_logiciel->setText(QApplication::translate("InterfaceClass", "Prise en main du logiciel", 0, QApplication::UnicodeUTF8));
        actionGrille->setText(QApplication::translate("InterfaceClass", "Grille", 0, QApplication::UnicodeUTF8));
        actionContraste->setText(QApplication::translate("InterfaceClass", "Contraste", 0, QApplication::UnicodeUTF8));
        actionR_glages_magn_tisme->setText(QApplication::translate("InterfaceClass", "R\303\251glages magn\303\251tisme", 0, QApplication::UnicodeUTF8));
        PleinEcranCours->setText(QString());
        Onglets->setTabText(Onglets->indexOf(Cours), QApplication::translate("InterfaceClass", "Cahier de Cours", 0, QApplication::UnicodeUTF8));
        PleinEcranExo->setText(QString());
        Onglets->setTabText(Onglets->indexOf(Exo), QApplication::translate("InterfaceClass", "Cahier d'Exercices", 0, QApplication::UnicodeUTF8));
        PleinEcranEval->setText(QString());
        Onglets->setTabText(Onglets->indexOf(Eval), QApplication::translate("InterfaceClass", "Cahier d'\303\211valuation", 0, QApplication::UnicodeUTF8));
        GeomPleinEcran->setText(QString());
        menuFichier->setTitle(QApplication::translate("InterfaceClass", "Fichier", 0, QApplication::UnicodeUTF8));
        menuEdition->setTitle(QApplication::translate("InterfaceClass", "Edition", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("InterfaceClass", "Options", 0, QApplication::UnicodeUTF8));
        menuAide->setTitle(QApplication::translate("InterfaceClass", "Aide", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InterfaceClass: public Ui_InterfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACETUT_H
