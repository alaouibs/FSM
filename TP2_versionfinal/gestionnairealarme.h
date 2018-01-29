#ifndef GESTIONNAIREALARME_H
#define GESTIONNAIREALARME_H

#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include "Alarme.h"
#include <QMessageBox>

class GestionnaireAlarme : public QWidget
{
public:
    GestionnaireAlarme(QWidget * parent = nullptr);
    QGridLayout gridLayout;
    ~GestionnaireAlarme();
    QLineEdit *formulaireMDP;
    QPushButton *mOK;
    QPushButton *mEnvoieSMS;

    QString *motdepasse;
    QString *sms;
    Alarme alarme;
public slots:
    void AnalyseMDP();
    void RequestPassword();
    void WarnUserMDPisWrong();
    void closeWindowResquest();
    void changeButtontoGoSMS();
    void changeButtontoGoMDP();
    void AnalyseSMS();
    void WarnUserSMSisWrong();
};

#endif // GESTIONNAIREALARME_H
