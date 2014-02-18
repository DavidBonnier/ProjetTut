#include "projetgeometrie.h"

ProjetGeometrie::ProjetGeometrie()
{
    ui.setupUi(this);
    m_geometrie = new Geometrie(this);

    ui.DessinLayout->addWidget(m_geometrie);

//Connexions des boutons

    //Boutons outils
    connect(ui.BoutonPleinEcran, SIGNAL(clicked(bool)), this, SLOT(sortieFullScreen()));

    connect(ui.BoutonCrayon, SIGNAL(clicked(bool)), this, SLOT(Crayon()));
    connect(ui.BoutonEquerre, SIGNAL(clicked(bool)), this, SLOT(Equerre()));
    connect(ui.BoutonRegle, SIGNAL(clicked(bool)), this, SLOT(Regle()));
    connect(ui.BoutonCompas, SIGNAL(clicked(bool)), this, SLOT(Compas()));
    connect(ui.BoutonPoint, SIGNAL(clicked(bool)), this, SLOT(Point(bool)));
    connect(ui.BoutonTexte, SIGNAL(clicked(bool)), this, SLOT(zoneTexte()));
    connect(ui.BoutonEpaisseur, SIGNAL(clicked(bool)), this, SLOT(Epaisseur(bool)));
    connect(ui.CheckBoxGrille, SIGNAL(clicked(bool)), this, SLOT(Grille(bool)));
    //Boutons couleurs
    connect(ui.BoutonNoir, SIGNAL(triggered(bool)), this, SLOT(Noir()));
//Instruments
    //Crayon
    connect(ui.SpinBoxCrayonPositionX, SIGNAL(valueChanged(int)), this, SLOT(CrayonPositionX(int)));
    connect(ui.SpinBoxCrayonPositionY, SIGNAL(valueChanged(int)), this, SLOT(CrayonPositionY(int)));
    connect(ui.CheckBoxCrayonTransparence, SIGNAL(clicked(bool)), this, SLOT(CrayonTransparence(bool)));
    connect(ui.SpinBoxCrayonOrientation, SIGNAL(valueChanged(double)), this, SLOT(CrayonOrientation(double)));
    //Regle
    connect(ui.SpinBoxReglePositionX, SIGNAL(valueChanged(int)), this, SLOT(ReglePositionX(int)));
    connect(ui.SpinBoxReglePositionY, SIGNAL(valueChanged(int)), this, SLOT(ReglePositionY(int)));
    connect(ui.CheckBoxRegleTransparence, SIGNAL(clicked(bool)), this, SLOT(RegleTransparence(bool)));
    connect(ui.SpinBoxRegleOrientation, SIGNAL(valueChanged(double)), this, SLOT(RegleOrientation(double)));
    connect(ui.BoutonRegleTracerOK, SIGNAL(clicked(bool)), this, SLOT(RegleTracer()));
    //Equerre
    connect(ui.SpinBoxEquerrePositionX, SIGNAL(valueChanged(int)), this, SLOT(EquerrePositionX(int)));
    connect(ui.SpinBoxEquerrePositionY, SIGNAL(valueChanged(int)), this, SLOT(EquerrePositionY(int)));
    connect(ui.CheckBoxEquerreTransparence, SIGNAL(clicked(bool)), this, SLOT(EquerreTransparence(bool)));
    connect(ui.SpinBoxEquerreOrientation, SIGNAL(valueChanged(double)), this, SLOT(EquerreOrientation(double)));
    connect(ui.BoutonEquerreTracerOK, SIGNAL(clicked(bool)), this, SLOT(EquerreTracer()));
    //Compas
    connect(ui.SpinBoxCompasPositionX, SIGNAL(valueChanged(int)), this, SLOT(CompasPositionX(int)));
    connect(ui.SpinBoxCompasPositionY, SIGNAL(valueChanged(int)), this, SLOT(CompasPositionY(int)));
    connect(ui.SpinBoxCompasEcartement, SIGNAL(valueChanged(int)), this, SLOT(CompasEcartement(int)));
    connect(ui.SpinBoxCompasOrientation, SIGNAL(valueChanged(double)), this, SLOT(CompasOrientation(double)));

    connect(ui.BoutonCompasTracerOK, SIGNAL(clicked(bool)), this, SLOT(CompasFinTracer()));
    connect(ui.SpinBoxCompasTracerArc, SIGNAL(valueChanged(double)), this, SLOT(CompasAngleArriver(double)));
}

ProjetGeometrie::~ProjetGeometrie()
{
    delete m_geometrie;
}

//****************************************SLOTS*******************************
//Outils
void ProjetGeometrie::sortieFullScreen()
{
    emit clickSortieFullScreen();
}
void ProjetGeometrie::Crayon()
{
    emit clickCrayon();
    m_geometrie->gererCrayon();
    m_geometrie->modifCrayon = true;
    m_geometrie->update();
}

void ProjetGeometrie::Equerre()
{
    emit clickEquerre();
    m_geometrie->gererEquerre();
    m_geometrie->modifEquerre = true;
    m_geometrie->update();
}

void ProjetGeometrie::Regle()
{
    emit clickRegle();
    m_geometrie->gererRegle();
    m_geometrie->modifRegle = true;
    m_geometrie->update();
}

void ProjetGeometrie::Compas()
{
    emit clickCompas();
    m_geometrie->gererCompas();
    m_geometrie->modifCompas = true;
    m_geometrie->update();
}

void ProjetGeometrie::Point()
{

}

void ProjetGeometrie::Epaisseur(bool b)
{

}

void ProjetGeometrie::Grille(bool b)
{
    m_geometrie->grille = b;
    m_geometrie->update();
}

void ProjetGeometrie::zoneTexte()
{
    if(m_geometrie->clickTxt)
    {
        m_geometrie->clickTxt = false;
        QApplication::restoreOverrideCursor();
    }
    else
    {
        QCursor Souris(QPixmap("Resources/curseur-zoneTexte.png"),-1,-1);
        QApplication::setOverrideCursor(Souris);
        m_geometrie->clickTxt = true;
    }
}

//Couleurs
void ProjetGeometrie::Noir()
{
    int noir[3] = {0,0,0};
}

void ProjetGeometrie::Bleu()
{
    int bleu[3] = {0,0,255};
}

void ProjetGeometrie::Vert()
{
    int vert[3] = {0,255,0};
}

void ProjetGeometrie::Jaune()
{
    int jaune[3] = {0,255,255};
}

void ProjetGeometrie::Rouge()
{
    int rouge[3] = {255,0,0};
}

//Instruments
//Crayon
void ProjetGeometrie::CrayonPositionX(int x)
{
    if (m_geometrie->crayon)
    {
        m_geometrie->crayon->translation(x, ui.SpinBoxCrayonPositionY->value());
        m_geometrie->modifCrayon = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::CrayonPositionY(int y)
{
    if (m_geometrie->crayon)
    {
        m_geometrie->crayon->translation(ui.SpinBoxCrayonPositionX->value(), y);
        m_geometrie->modifCrayon = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::CrayonTransparence(bool b)
{
    if (m_geometrie->crayon)
    {
        m_geometrie->crayon->setTransparence(b);
        m_geometrie->modifCrayon = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::CrayonOrientation(double orientation)
{
    //Rotation infinie
    if (ui.SpinBoxCrayonOrientation->value() < 0)
        ui.SpinBoxCrayonOrientation->setValue(360 + ui.SpinBoxCrayonOrientation->value());
    if (ui.SpinBoxCrayonOrientation->value() > 360)
        ui.SpinBoxCrayonOrientation->setValue(ui.SpinBoxCrayonOrientation->value() - 360);

    if (m_geometrie->crayon)
    {
        m_geometrie->crayon->setAngle(orientation);
        m_geometrie->modifCrayon = true;
        m_geometrie->update();
    }
}
//Règle
void ProjetGeometrie::ReglePositionX(int x)
{
    if (m_geometrie->regle)
    {
        m_geometrie->regle->translation(x, ui.SpinBoxReglePositionY->value());
        m_geometrie->modifRegle = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::ReglePositionY(int y)
{
    if (m_geometrie->regle)
    {
        m_geometrie->regle->translation(ui.SpinBoxReglePositionX->value(), y);
        m_geometrie->modifRegle = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::RegleTransparence(bool b)
{
    if (m_geometrie->regle)
    {
        m_geometrie->regle->setTransparence(b);
        m_geometrie->modifRegle = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::RegleOrientation(double orientation)
{
    //Rotation infinie
    if (ui.SpinBoxRegleOrientation->value() < 0)
        ui.SpinBoxRegleOrientation->setValue(360 + ui.SpinBoxRegleOrientation->value());
    if (ui.SpinBoxRegleOrientation->value() > 360)
        ui.SpinBoxRegleOrientation->setValue(ui.SpinBoxRegleOrientation->value() - 360);

    if (m_geometrie->regle)
    {
        m_geometrie->regle->setAngle(orientation);
        m_geometrie->modifRegle = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::RegleTracer()
{
    if (m_geometrie->regle)
    {
        m_geometrie->regle->tracer(ui.SpinBoxRegleTracerPoint1->value(), ui.SpinBoxRegleTracerPoint2->value());
        m_geometrie->modifRegle = true;
        m_geometrie->update();
    }
}
//Equerre
void ProjetGeometrie::EquerrePositionX(int x)
{
    if (m_geometrie->equerre)
    {
        m_geometrie->equerre->translation(x, ui.SpinBoxEquerrePositionY->value());
        m_geometrie->modifEquerre = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::EquerrePositionY(int y)
{
    if (m_geometrie->equerre)
    {
        m_geometrie->equerre->translation(ui.SpinBoxEquerrePositionX->value(), y);
        m_geometrie->modifEquerre = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::EquerreTransparence(bool b)
{
    if (m_geometrie->equerre)
    {
        m_geometrie->equerre->setTransparence(b);
        m_geometrie->modifEquerre = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::EquerreOrientation(double orientation)
{
    //Rotation infinie
    if (ui.SpinBoxEquerreOrientation->value() < 0)
        ui.SpinBoxEquerreOrientation->setValue(360 + ui.SpinBoxEquerreOrientation->value());
    if (ui.SpinBoxEquerreOrientation->value() > 360)
        ui.SpinBoxEquerreOrientation->setValue(ui.SpinBoxEquerreOrientation->value() - 360);

    if (m_geometrie->equerre)
    {
        m_geometrie->equerre->setAngle(orientation);
        m_geometrie->modifEquerre = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::EquerreTracer()
{
    if (m_geometrie->equerre)
    {
        m_geometrie->equerre->tracer(ui.SpinBoxEquerreTracerPoint1->value(), ui.SpinBoxEquerreTracerPoint2->value());
        m_geometrie->modifEquerre = true;
        m_geometrie->update();
    }
}
//Compas
void ProjetGeometrie::CompasPositionX(int x)
{
    if (m_geometrie->compas)
    {
        m_geometrie->compas->translation(x, ui.SpinBoxCompasPositionY->value());
        m_geometrie->modifCompas = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::CompasPositionY(int y)
{
    if (m_geometrie->compas)
    {
        m_geometrie->compas->translation(ui.SpinBoxCompasPositionX->value(), y);
        m_geometrie->modifCompas = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::CompasEcartement(int ecartement)
{
    if (m_geometrie->compas)
    {
        m_geometrie->compas->setEcartement(ecartement);
        m_geometrie->modifCompas = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::CompasOrientation(double orientation)
{
    //Rotation infinie
    if (ui.SpinBoxCompasOrientation->value() < 0)
        ui.SpinBoxCompasOrientation->setValue(360 + ui.SpinBoxCompasOrientation->value());
    if (ui.SpinBoxCompasOrientation->value() > 360)
        ui.SpinBoxCompasOrientation->setValue(ui.SpinBoxCompasOrientation->value() - 360);

    if (m_geometrie->compas)
    {
        m_geometrie->compas->setAngle(orientation);
        m_geometrie->modifCompas = true;
        m_geometrie->update();
    }
}

void ProjetGeometrie::CompasFinTracer()
{
    if (m_geometrie->compas)
        m_geometrie->compas->finTracer();
    ui.SpinBoxCompasTracerArc->setValue(0);
    m_geometrie->update();
}

void ProjetGeometrie::CompasAngleArriver(double angleArriver)
{
    if(angleArriver !=0)
    {
        if (m_geometrie->compas)
            m_geometrie->compas->tracer(angleArriver);
        m_geometrie->update();
    }
}