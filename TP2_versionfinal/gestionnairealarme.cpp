#include "gestionnairealarme.h"

GestionnaireAlarme::GestionnaireAlarme(QWidget *parent)
    : QWidget(parent)
    , gridLayout(this)
{
    this->mOK = new QPushButton("OK");
    mEnvoieSMS  = new QPushButton("Autre méthode : envoyer SMS");
    formulaireMDP = new QLineEdit;

    gridLayout.addWidget(formulaireMDP, 0, 0);
    gridLayout.addWidget(mOK,   1, 0);
    gridLayout.addWidget(mEnvoieSMS,   2, 0);

    motdepasse = new QString("azerty123");
    sms = new QString("sms");

    alarme.start();
    alarme.connectToEvent(QStringLiteral("RequestPassword"),this,&GestionnaireAlarme::RequestPassword);
    alarme.connectToEvent(QStringLiteral("AnalyseMDP"),this,&GestionnaireAlarme::AnalyseMDP);
    alarme.connectToEvent(QStringLiteral("WarnUserMDPisWrong"),this,&GestionnaireAlarme::WarnUserMDPisWrong);
    alarme.connectToEvent(QStringLiteral("closeWindowResquest"),this,&GestionnaireAlarme::closeWindowResquest);
    alarme.connectToEvent(QStringLiteral("changeButtontoGoSMS"),this,&GestionnaireAlarme::changeButtontoGoSMS);
    alarme.connectToEvent(QStringLiteral("changeButtontoGoMDP"),this,&GestionnaireAlarme::changeButtontoGoMDP);
    alarme.connectToEvent(QStringLiteral("AnalyseSMS"),this,&GestionnaireAlarme::AnalyseSMS);
    alarme.connectToEvent(QStringLiteral("AnalyseSMS"),this,&GestionnaireAlarme::WarnUserSMSisWrong);
}

GestionnaireAlarme::~GestionnaireAlarme() {

}

void GestionnaireAlarme::RequestPassword() {
    this->show();
}

void GestionnaireAlarme::AnalyseMDP() {
    QString MDPdonne = this->formulaireMDP->text();
    if (MDPdonne == this->motdepasse) {
        alarme.submitEvent("MDPisGood");
    } else {
        alarme.submitEvent("MDPisWrong");
    }
}

void GestionnaireAlarme::WarnUserMDPisWrong() {
    QMessageBox::warning(this, "Test", "Le mot de passe est incorrect");
}

void GestionnaireAlarme::closeWindowResquest() {
    this->close();
}


void GestionnaireAlarme::changeButtontoGoSMS() {
    this->mEnvoieSMS->setText("Utiliser MDP");
}

void GestionnaireAlarme::changeButtontoGoMDP() {
    this->mEnvoieSMS->setText("Autre méthode : envoyer SMS");
}

void GestionnaireAlarme::AnalyseSMS() {
    QString SMSdonne = this->formulaireMDP->text();
    if (SMSdonne == this->sms) {
        alarme.submitEvent("SMSisGood");
    } else {
        alarme.submitEvent("SMSisWrong");
    }
}

void GestionnaireAlarme::WarnUserSMSisWrong() {
    QMessageBox::warning(this, "Test", "le SMS donné n'est pas le bon");
}
