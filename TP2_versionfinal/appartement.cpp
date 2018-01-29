#include "appartement.h"

Appartement::Appartement(QWidget *parent)
    :QWidget(parent)
{
    layout = new QGridLayout;
    mTime = new QLabel("00");
    mLabelTime = new QLabel("Temps");
    mAlarme = new QPushButton("Alarme");
    mEteindreToutLumieres = new QPushButton("Eteindre toutes les lumières");
    mLabelAlarme = new QLabel("Alarme");
    mMomentJournee = new QLabel("Matin");
    mFenetreEtat = new QLabel("FenetreFerme");
    mAlarmeEtat = new QLabel("Alarme Eteinte");
    layout->addWidget(mLabelTime, 0, 0);
    layout->addWidget(mTime, 0, 1);
    layout->addWidget(mMomentJournee, 0, 2);
    layout->addWidget(mEteindreToutLumieres, 1, 0);
    layout->addWidget(mAlarme, 2, 0);
    layout->addWidget(mLabelAlarme, 2, 1);

    layout->addWidget(mFenetreEtat, 3, 0);
    layout->addWidget(mAlarmeEtat, 3, 1);

    this->setLayout(layout);
    compteur = 0;

    time = new QTime();
}
