#include "gestionlumiere.h"

GestionLumiere::GestionLumiere(QWidget *parent)
    :QWidget(parent)
{
    layout = new QGridLayout;
    mLumiereTurnOn  = new QPushButton("Allumer Lumieres");
    mLumiereTurnOff  = new QPushButton("Éteindre Lumieres");
    mLabel = new QLabel("00");
    mProgrammationLumiere = new QLabel("Programmation des lumières");
    mAllumage = new QLabel("Allumage (1/0)");
    mDuree = new QLabel("Durée");
    mProgrammerLight = new QPushButton("Programmer Lumières");
    editAllumageMatin = new QSpinBox();
    editDureeMatin = new QSpinBox();
    editAllumageAprem = new QSpinBox();
    editDureeAprem = new QSpinBox();
    editAllumageSoiree = new QSpinBox();
    editDureeSoiree = new QSpinBox();
    editAllumageNuit = new QSpinBox();
    editDureeNuit = new QSpinBox();

    mMatin = new QLabel("Matin");
    mAprem = new QLabel("Aprem");
    mSoiree = new QLabel("Soirée");
    mNuit = new QLabel("Nuit");

    editAllumageMatin->setMinimum(0);
    editAllumageMatin->setMaximum(1);
    editAllumageAprem->setMinimum(0);
    editAllumageAprem->setMaximum(1);
    editAllumageSoiree->setMinimum(0);
    editAllumageSoiree->setMaximum(1);
    editAllumageNuit->setMinimum(0);
    editAllumageNuit->setMaximum(1);

    editDureeMatin->setMinimum(1);
    editDureeMatin->setMaximum(10);
    editDureeAprem->setMinimum(1);
    editDureeAprem->setMaximum(10);
    editDureeSoiree->setMinimum(1);
    editDureeSoiree->setMaximum(10);
    editDureeNuit->setMinimum(1);
    editDureeNuit->setMaximum(10);
    editDureeLumiere = new QSpinBox();
    editDureeLumiere->setMinimum(1);
    editDureeLumiere->setMaximum(10);
    editIntensiteMinimumMatin = new QComboBox();
    editIntensiteMinimumMatin->addItem("20");
    editIntensiteMinimumMatin->addItem("30");
    editIntensiteMinimumMatin->addItem("40");
    editIntensiteMinimumMatin->addItem("50");
    editIntensiteMinimumMatin->addItem("60");
    editIntensiteMinimumMatin->addItem("70");
    editIntensiteMinimumMatin->addItem("80");
    editIntensiteMinimumMatin->addItem("90");
    editIntensiteMinimumMatin->addItem("100");
    editIntensiteMinimumAprem = new QComboBox();
    editIntensiteMinimumAprem->addItem("20");
    editIntensiteMinimumAprem->addItem("30");
    editIntensiteMinimumAprem->addItem("40");
    editIntensiteMinimumAprem->addItem("50");
    editIntensiteMinimumAprem->addItem("60");
    editIntensiteMinimumAprem->addItem("70");
    editIntensiteMinimumAprem->addItem("80");
    editIntensiteMinimumAprem->addItem("90");
    editIntensiteMinimumAprem->addItem("100");
    editIntensiteMinimumSoiree = new QComboBox();
    editIntensiteMinimumSoiree->addItem("20");
    editIntensiteMinimumSoiree->addItem("30");
    editIntensiteMinimumSoiree->addItem("40");
    editIntensiteMinimumSoiree->addItem("50");
    editIntensiteMinimumSoiree->addItem("60");
    editIntensiteMinimumSoiree->addItem("70");
    editIntensiteMinimumSoiree->addItem("80");
    editIntensiteMinimumSoiree->addItem("90");
    editIntensiteMinimumSoiree->addItem("100");
    editIntensiteMinimumNuit = new QComboBox();
    editIntensiteMinimumNuit->addItem("20");
    editIntensiteMinimumNuit->addItem("30");
    editIntensiteMinimumNuit->addItem("40");
    editIntensiteMinimumNuit->addItem("50");
    editIntensiteMinimumNuit->addItem("60");
    editIntensiteMinimumNuit->addItem("70");
    editIntensiteMinimumNuit->addItem("80");
    editIntensiteMinimumNuit->addItem("90");
    editIntensiteMinimumNuit->addItem("100");
    layout->addWidget(editDureeLumiere, 0, 0);
    layout->addWidget(mLumiereTurnOn, 0, 1);
    layout->addWidget(mLumiereTurnOff, 0, 2);
    layout->addWidget(mLabel, 0, 3);

    layout->addWidget(mProgrammationLumiere, 1, 0);
    layout->addWidget(mAllumage, 2, 1);
    layout->addWidget(mDuree, 2, 2);

    layout->addWidget(mMatin, 3, 0);
    layout->addWidget(mAprem, 4, 0);
    layout->addWidget(mSoiree, 5, 0);
    layout->addWidget(mNuit, 6, 0);

    layout->addWidget(editAllumageMatin, 3, 1);
    layout->addWidget(editAllumageAprem, 4, 1);
    layout->addWidget(editAllumageSoiree, 5, 1);
    layout->addWidget(editAllumageNuit, 6, 1);

    layout->addWidget(editDureeMatin, 3, 2);
    layout->addWidget(editDureeAprem, 4, 2);
    layout->addWidget(editDureeSoiree, 5, 2);
    layout->addWidget(editDureeNuit, 6, 2);

    layout->addWidget(editIntensiteMinimumMatin, 3, 3);
    layout->addWidget(editIntensiteMinimumAprem, 4, 3);
    layout->addWidget(editIntensiteMinimumSoiree, 5, 3);
    layout->addWidget(editIntensiteMinimumNuit, 6, 3);

    layout->addWidget(mProgrammerLight, 7, 0);
    this->setLayout(layout);

    lumiere.start();
    lumiere.connectToEvent(QStringLiteral("regulerLight"),this,&GestionLumiere::regulerLight);
    lumiere.connectToEvent(QStringLiteral("increaseLight"),this,&GestionLumiere::increaseLight);
    lumiere.connectToEvent(QStringLiteral("decreaseLight"),this,&GestionLumiere::decreaseLight);

    intensite = 0;
    intensiteVoulue = 100;
    intensiteDepart = 0;
}


void GestionLumiere::regulerLight() {
    if (intensite < intensiteVoulue) {
        lumiere.submitEvent("tooDark");
    } else if (intensite > intensiteVoulue) {
        lumiere.submitEvent("tooBright");
    } else {
        lumiere.submitEvent("setOff");
    }

}

void GestionLumiere::increaseLight() {
    intensite = intensite + (intensiteVoulue - intensiteDepart)/(duree);
    if (intensite > intensiteVoulue) {
        intensite = intensiteVoulue;
        lumiere.submitEvent("setOff");
    }
    const QString diff =  QString("%1")
                               .arg(intensite,  2, 10, QChar('0'));
    mLabel->setText(diff);
}

void GestionLumiere::decreaseLight() {
    intensite = intensite - (intensiteDepart - intensiteVoulue)/(duree);
    if (intensite < intensiteVoulue) {
        intensite = intensiteVoulue;
        lumiere.submitEvent("setOff");
    }
    const QString diff =  QString("%1")
                               .arg(intensite,  2, 10, QChar('0'));

    mLabel->setText(diff);
}
