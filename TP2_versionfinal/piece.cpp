#include "piece.h"

Piece::Piece(QWidget *parent, QString nom, int tE, int tP)
    : QWidget(parent)
{
    layout = new QGridLayout;
    this->nomPiece = new QString(nom);
    gAlarme = new GestionnaireAlarme();
    lum = new GestionLumiere();
    temp = new Temperature();
    fenetre = new Fenetre();
    temp->temperaturePiece = tP;
    temp->temperatureEnvironnement = tE;
    mLabelNomPiece = new QLabel("Piece");
    mEtatAlarme = new QLabel("Alarme éteinte");
    mAmbianceCinema = new QPushButton("Home Cinema");
    layout->addWidget(mLabelNomPiece, 0, 0);
    layout->addWidget(mBouton1, 1, 0);
    layout->addWidget(temp, 2, 0);
    layout->addWidget(lum, 3, 0);
    layout->addWidget(fenetre, 4, 0);
    layout->addWidget(mEtatAlarme, 5, 1);
    layout->addWidget(mAmbianceCinema, 6, 0);

    this->setLayout(layout);
    state_piece.start();

    state_piece.connectToEvent(QStringLiteral("turnOffTemp"),this,&Piece::turnOffTemp);
    state_piece.connectToEvent(QStringLiteral("doAllumer"),this,&Piece::doAllumer);
    state_piece.connectToEvent(QStringLiteral("doStartLight"),this,&Piece::doStartLight);
    state_piece.connectToEvent(QStringLiteral("doTurnOffLumiere"),this,&Piece::doTurnOffLumiere);
    state_piece.connectToEvent(QStringLiteral("setTurnOn"),this,&Piece::setTurnOn);

    state_piece.connectToEvent(QStringLiteral("doTurnOffLumiereInterruption"),this,&Piece::doTurnOffLumiereInterruption);
    state_piece.connectToEvent(QStringLiteral("AnalyserAlarme"),this,&Piece::AnalyserAlarme);
    state_piece.connectToEvent(QStringLiteral("doProgrammerMatin"),this,&Piece::doProgrammerMatin);
    state_piece.connectToEvent(QStringLiteral("doProgrammerAprem"),this,&Piece::doProgrammerAprem);
    state_piece.connectToEvent(QStringLiteral("doProgrammerSoiree"),this,&Piece::doProgrammerSoiree);
    state_piece.connectToEvent(QStringLiteral("doProgrammerNuit"),this,&Piece::doProgrammerNuit);
    state_piece.connectToEvent(QStringLiteral("doValiderProgrammation"),this,&Piece::doValiderProgrammation);
    state_piece.connectToEvent(QStringLiteral("doOpenWindowPiece"),this,&Piece::doOpenWindowPiece);
    state_piece.connectToEvent(QStringLiteral("doCloseWindowPiece"),this,&Piece::doCloseWindowPiece);
    state_piece.connectToEvent(QStringLiteral("dosetAlarmeOn"),this,&Piece::dosetAlarmeOn);
    state_piece.connectToEvent(QStringLiteral("setAlarmeOff"),this,&Piece::setAlarmeOff);
    state_piece.connectToEvent(QStringLiteral("doProgrammerRadiateurMatin"),this,&Piece::doProgrammerRadiateurMatin);
    state_piece.connectToEvent(QStringLiteral("doProgrammerRadiateurAprem"),this,&Piece::doProgrammerRadiateurAprem);
    state_piece.connectToEvent(QStringLiteral("doProgrammerRadiateurSoiree"),this,&Piece::doProgrammerRadiateurSoiree);
    state_piece.connectToEvent(QStringLiteral("doProgrammerRadiateurNuit"),this,&Piece::doProgrammerRadiateurNuit);
    state_piece.connectToEvent(QStringLiteral("doDeProgrammerRadiateur"),this,&Piece::doDeProgrammerRadiateur);
    state_piece.connectToEvent(QStringLiteral("doProgrammerRadiateur"),this,&Piece::doProgrammerRadiateur);
    state_piece.connectToEvent(QStringLiteral("doAmbianceCinema"),this,&Piece::doAmbianceCinema);
    state_piece.connectToEvent(QStringLiteral("doDeprogrammer"),this,&Piece::doDeprogrammer);
    state_piece.connectToEvent(QStringLiteral("doAnalyseLight"),this,&Piece::doAnalyseLight);
    state_piece.connectToEvent(QStringLiteral("doTurnOnManually"),this,&Piece::doTurnOnManually);

    this->gAlarme->alarme.connectToEvent(QStringLiteral("RevenirAEtat"),this,&Piece::RevenirAEtat);
    this->gAlarme->alarme.connectToEvent(QStringLiteral("WarnUserProblemSolved"),this,&Piece::WarnUserProblemSolved);

    connect(temp->mTemperature,&QAbstractButton::clicked,[this] { state_piece.submitEvent("clickRadiateur");});
    connect(lum->mLumiereTurnOn,&QAbstractButton::clicked,[this] { state_piece.submitEvent("clickLumiereOn");});
    connect(lum->mLumiereTurnOff,&QAbstractButton::clicked,[this] { state_piece.submitEvent("clickLumiereOff");});
    connect(lum->mProgrammerLight,&QAbstractButton::clicked,[this] { state_piece.submitEvent("clickProgramLight");});
    connect(gAlarme->mOK,&QAbstractButton::clicked,[this] { gAlarme->alarme.submitEvent("clickOKFirst");});
    connect(gAlarme->mEnvoieSMS,&QAbstractButton::clicked,[this] { gAlarme->alarme.submitEvent("DemandeChangementMethode");});
    connect(fenetre->mButtonFenetre,&QAbstractButton::clicked,[this] { state_piece.submitEvent("clickFenetre");});
    connect(temp->mProgrammerTemperature,&QAbstractButton::clicked,[this] { state_piece.submitEvent("clickProgramRadiateur");});
    connect(mAmbianceCinema,&QAbstractButton::clicked,[this] { state_piece.submitEvent("clickAmbianceCinema");});
}

Piece::~Piece()
{

}

void Piece::turnOffTemp() {
    temp->mLabelTemperatureEtat->setText("Radiateur Eteint");
    temp->temperatureDemande = temp->temperatureEnvironnement;
    temp->regul.submitEvent("setOn");
}

void Piece::doAllumer() {
    temp->temperatureDemande = temp->editTemperature->value();
    temp->mLabelTemperatureEtat->setText("Radiateur Allumer");
    temp->regul.submitEvent("setOn");
}

void Piece::doStartLight() {
    lum->intensiteDepart = lum->intensite;
    lum->duree = lum->editDureeLumiere->value();
    lum->lumiere.submitEvent("setOn");
}

void Piece::doTurnOffLumiere() {
    lum->intensiteVoulue = 0;
    lum->intensiteDepart = lum->intensite;
    lum->duree = lum->editDureeLumiere->value();
    lum->lumiere.submitEvent("setOn");
}

void Piece::doTurnOffLumiereInterruption() {
    lum->duree = 0;
    lum->intensiteVoulue = 0;
    lum->lumiere.submitEvent("setOn");
}

void Piece::setTurnOn() {
    lum->intensiteVoulue = 100;
}

void Piece::AnalyserAlarme() {
    QMessageBox::information(this, "titre", "ou ou...");
    gAlarme->alarme.submitEvent("IntruderDetected");
}

void Piece::RevenirAEtat() {
    QMessageBox::information(this, "titre", "ouf...");
    state_piece.submitEvent("Return");
}


void Piece::WarnUserProblemSolved() {
    QMessageBox::information(this, "Validation", "Alarme éteinte");
    state_piece.submitEvent("Return");
    gAlarme->changeButtontoGoMDP();
}

void Piece::doProgrammerMatin() {
    lum->editDureeLumiere->setValue(lum->editDureeMatin->value());
    if (lum->editAllumageMatin->value() == 0) {
        QMessageBox::information(this, "ti", "on éteinds le matin");
        state_piece.submitEvent("turnOffProgrammed");
    } else if (lum->editAllumageMatin->value() == 1) {
        QMessageBox::information(this, "ti", "on allume le matin");
        lum->intensiteVoulue = lum->editIntensiteMinimumMatin->currentText().toInt();
        state_piece.submitEvent("turnOnProgrammed");
    }
}

void Piece::doProgrammerAprem() {
    lum->editDureeLumiere->setValue(lum->editDureeAprem->value());
    if (lum->editAllumageAprem->value() == 0) {
        QMessageBox::information(this, "ti", "on éteinds l'aprem");
        state_piece.submitEvent("turnOffProgrammed");
    } else if (lum->editAllumageAprem->value() == 1) {
        QMessageBox::information(this, "ti", "on allume l'aprem");
        lum->intensiteVoulue = lum->editIntensiteMinimumAprem->currentText().toInt();
        state_piece.submitEvent("turnOnProgrammed");
    }
}

void Piece::doProgrammerSoiree() {
    lum->editDureeLumiere->setValue(lum->editDureeSoiree->value());
    if (lum->editAllumageSoiree->value() == 0) {
        QMessageBox::information(this, "ti", "on éteinds la soiree");
        state_piece.submitEvent("turnOffProgrammed");
    } else if (lum->editAllumageSoiree->value() == 1) {
        QMessageBox::information(this, "ti", "on allume la soiree");
        lum->intensiteVoulue = lum->editIntensiteMinimumSoiree->currentText().toInt();
        state_piece.submitEvent("turnOnProgrammed");
    }
}

void Piece::doProgrammerNuit() {
    lum->editDureeLumiere->setValue(lum->editDureeNuit->value());
    if (lum->editAllumageNuit->value() == 0) {
        QMessageBox::information(this, "ti", "on éteinds la nuit");
        state_piece.submitEvent("turnOffProgrammed");
    } else if (lum->editAllumageNuit->value() == 1) {
        QMessageBox::information(this, "ti", "on allume la nuit");
        lum->intensiteVoulue = lum->editIntensiteMinimumNuit->currentText().toInt();
        state_piece.submitEvent("turnOnProgrammed");
    }
}

void Piece::doProgrammerRadiateurMatin() {
    temp->editTemperature->setValue(temp->editAllumageMatin->value());
    state_piece.submitEvent("TurnRadiateurOn");
}

void Piece::doProgrammerRadiateurAprem() {
    temp->editTemperature->setValue(temp->editAllumageAprem->value());
    state_piece.submitEvent("TurnRadiateurOn");
}

void Piece::doProgrammerRadiateurSoiree() {
    temp->editTemperature->setValue(temp->editAllumageSoiree->value());
    state_piece.submitEvent("TurnRadiateurOn");
}

void Piece::doProgrammerRadiateurNuit() {
    temp->editTemperature->setValue(temp->editAllumageNuit->value());
    state_piece.submitEvent("TurnRadiateurOn");
}

void Piece::doValiderProgrammation() {
    lum->mProgrammerLight->setText("Quitter programmation");
}

void Piece::doDeprogrammer() {
    lum->mProgrammerLight->setText("Programmer Lumières");
}

void Piece::doOpenWindowPiece() {
    fenetre->mLabelFenetre->setText("Fenêtre ouverte");
    gAlarme->alarme.submitEvent("IntruderDetected");
}

void Piece::doCloseWindowPiece() {
    fenetre->mLabelFenetre->setText("Fenêtre fermée");
}

void Piece::dosetAlarmeOn() {
    QMessageBox::information(this, "oui", "oui");
    this->mEtatAlarme->setText("Alarm On");
    this->gAlarme->alarme.submitEvent("UserSetAlarmeOn");

    temp->temperatureDemande = temp->temperatureEnvironnement;
    temp->regul.submitEvent("setOn");

    lum->intensiteVoulue = 0;
    lum->lumiere.submitEvent("setOn");
}

void Piece::setAlarmeOff() {
    this->mEtatAlarme->setText("Alarm Off");
    this->gAlarme->alarme.submitEvent("UserSetAlarmeOff");

}

void Piece::doAmbianceCinema() {
    QMessageBox::information(this, "it", "oui");
    lum->intensiteVoulue = 30;
    lum->duree = 5;
    state_piece.submitEvent("clickLumiereOn");
    state_piece.submitEvent("fermerFenetres");
    state_piece.submitEvent("DeprogrammationRadiateur");
    temp->editTemperature->setValue(25);
    state_piece.submitEvent("TurnRadiateurOn");
}

void Piece::doProgrammerRadiateur() {
    temp->mProgrammerTemperature->setText("Quitter Programmation Temperature");
}

void Piece::doDeProgrammerRadiateur() {
    temp->mProgrammerTemperature->setText("Programmer Temperature");
}

void Piece::doAnalyseLight() {
    if (lum->intensite == 0) {
        state_piece.submitEvent("itsTurnOff");
    } else {
        state_piece.submitEvent("itsTurnOn");
    }
}


void Piece::doTurnOnManually() {
    lum->intensiteVoulue = 100;
    QMessageBox::information(this, "ti", "oiejor");
}
