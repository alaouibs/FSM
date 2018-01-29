#include "temperature.h"

Temperature::Temperature(QWidget *parent, int tE, int tP)
    : QWidget(parent)
{
    temperatureEnvironnement = tE;
    temperaturePiece = tP;
    temperatureDemande = 0;

    layout = new QGridLayout;
    mTemperature  = new QPushButton("Temperature");
    mLabel = new QLabel("00");

    mLabelTemperatureEtat = new QLabel("Temperature Etat");
    editTemperature = new QSpinBox();
    editTemperature->setMinimum(tE+2);
    editTemperature->setMaximum(40);

    mMatin = new QLabel("Matin");
    mAprem = new QLabel("Aprem");
    mSoiree = new QLabel("Soirée");
    mNuit = new QLabel("Nuit");

    editAllumageMatin = new QSpinBox();
    editAllumageAprem = new QSpinBox();
    editAllumageSoiree = new QSpinBox();
    editAllumageNuit = new QSpinBox();

    editAllumageMatin->setMinimum(tE+2);
    editAllumageMatin->setMaximum(40);
    editAllumageAprem->setMinimum(tE+2);
    editAllumageAprem->setMaximum(40);
    editAllumageSoiree->setMinimum(tE+2);
    editAllumageSoiree->setMaximum(40);
    editAllumageNuit->setMinimum(tE+2);
    editAllumageNuit->setMaximum(40);

    mProgrammerTemperature = new QPushButton("Programmer Temperature");

    layout->addWidget(mMatin, 1, 0);
    layout->addWidget(mAprem, 2, 0);
    layout->addWidget(mSoiree, 3, 0);
    layout->addWidget(mNuit, 4, 0);

    layout->addWidget(editAllumageMatin, 1, 1);
    layout->addWidget(editAllumageAprem, 2, 1);
    layout->addWidget(editAllumageSoiree, 3, 1);
    layout->addWidget(editAllumageNuit, 4, 1);

    layout->addWidget(editTemperature, 0, 0);
    layout->addWidget(mLabel, 0, 2);
    layout->addWidget(mTemperature, 0, 1);
    layout->addWidget(mLabelTemperatureEtat, 0, 3);
    layout->addWidget(mProgrammerTemperature, 5, 0);
    this->setLayout(layout);

    regul.start();
    regul.connectToEvent(QStringLiteral("increase"),this,&Temperature::increase);
    regul.connectToEvent(QStringLiteral("decrease"),this,&Temperature::decrease);
    regul.connectToEvent(QStringLiteral("reguler"),this,&Temperature::reguler);
}


void Temperature::reguler() {
    if (temperaturePiece < temperatureDemande) {
        regul.submitEvent("tooCold");
    } else if (temperaturePiece > temperatureDemande) {
        regul.submitEvent("tooHot");
    } else {
        regul.submitEvent("setOff");
    }
}


void Temperature::increase() {
    temperaturePiece++;
    const QString diff =  QString("%1")
                               .arg(temperaturePiece,  2, 10, QChar('0'));
    mLabel->setText(diff);
}

void Temperature::decrease() {
    temperaturePiece--;
    const QString diff =  QString("%1")
                               .arg(temperaturePiece,  2, 10, QChar('0'));
    mLabel->setText(diff);
}
