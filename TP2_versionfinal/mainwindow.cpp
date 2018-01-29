#include "mainwindow.h"

#include <unistd.h>
#include <iostream>
#include <QMessageBox>
#include <QInputDialog>
#include <QTime>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    tabWidget = new QTabWidget;
    mainLayout = new QVBoxLayout;

    F3 = new Appartement(this);
    c1 = new Piece(this);
    c2 = new Piece(this);
    l1 = new Piece(this);
    b1 = new Piece(this);
    l1->nomPiece = new QString("L1");
    b1->nomPiece = new QString("B1");
    c1->nomPiece = new QString("C1");
    c2->nomPiece = new QString("C2");
    c1->mLabelNomPiece->setText("C1");
    c2->mLabelNomPiece->setText("C2");
    l1->mLabelNomPiece->setText("L1");
    b1->mLabelNomPiece->setText("B1");

    tabWidget->addTab(F3, tr("Appartement"));
    tabWidget->addTab(c1, tr("Chambre C1"));
    tabWidget->addTab(c2, tr("Chambre C2"));
    tabWidget->addTab(l1, tr("salle de vie L1"));
    tabWidget->addTab(b1, tr("salle de toilette B1"));
    mainLayout->addWidget(tabWidget);
    this->setLayout(mainLayout);

    F3_state.start();
    F3_state.submitEvent("begin");
    F3_state.connectToEvent(QStringLiteral("doTurnOffAllLight"),this,&MainWindow::doTurnOffAllLight);
    F3_state.connectToEvent(QStringLiteral("setAlarmeOff"),this,&MainWindow::setAlarmeOff);
    F3_state.connectToEvent(QStringLiteral("setAlarmeOn"),this,&MainWindow::setAlarmeOn);
    F3_state.connectToEvent(QStringLiteral("doStart"),this,&MainWindow::doStart);
    F3_state.connectToEvent(QStringLiteral("doRefreshDisplay"),this,&MainWindow::doRefreshDisplay);
    F3_state.connectToEvent(QStringLiteral("doDisplayNuit"),this,&MainWindow::doDisplayNuit);
    F3_state.connectToEvent(QStringLiteral("doDisplaySoiree"),this,&MainWindow::doDisplaySoiree);
    F3_state.connectToEvent(QStringLiteral("doDisplayAprem"),this,&MainWindow::doDisplayAprem);
    F3_state.connectToEvent(QStringLiteral("doDisplayMatin"),this,&MainWindow::doDisplayMatin);

    c1->state_piece.connectToEvent(QStringLiteral("AvertirDomotiqueOuverture"),this,&MainWindow::AvertirDomotiqueOuverture);
    c2->state_piece.connectToEvent(QStringLiteral("AvertirDomotiqueOuverture"),this,&MainWindow::AvertirDomotiqueOuverture);
    l1->state_piece.connectToEvent(QStringLiteral("AvertirDomotiqueOuverture"),this,&MainWindow::AvertirDomotiqueOuverture);
    b1->state_piece.connectToEvent(QStringLiteral("AvertirDomotiqueOuverture"),this,&MainWindow::AvertirDomotiqueOuverture);

    c1->state_piece.connectToEvent(QStringLiteral("AvertirDomotiqueFermeture"),this,&MainWindow::AvertirDomotiqueFermeture);
    c2->state_piece.connectToEvent(QStringLiteral("AvertirDomotiqueFermeture"),this,&MainWindow::AvertirDomotiqueFermeture);
    l1->state_piece.connectToEvent(QStringLiteral("AvertirDomotiqueFermeture"),this,&MainWindow::AvertirDomotiqueFermeture);
    b1->state_piece.connectToEvent(QStringLiteral("AvertirDomotiqueFermeture"),this,&MainWindow::AvertirDomotiqueFermeture);


    F3_state.connectToEvent(QStringLiteral("validerAlarmeOn"),this,&MainWindow::validerAlarmeOn);
    F3_state.connectToEvent(QStringLiteral("validerAlarmeOff"),this,&MainWindow::validerAlarmeOff);
    F3_state.connectToEvent(QStringLiteral("validerFenetresOuvertes"),this,&MainWindow::validerFenetresOuvertes);
    F3_state.connectToEvent(QStringLiteral("validerFenetresFermees"),this,&MainWindow::validerFenetresFermees);

    connect(F3->mEteindreToutLumieres,&QAbstractButton::clicked,[this] { F3_state.submitEvent("clickEteindreLumieres");});
    connect(F3->mAlarme,&QAbstractButton::clicked,[this] { F3_state.submitEvent("clickAlarme");});
}

MainWindow::~MainWindow()
{

}



void MainWindow::doTurnOffAllLight() {
    c2->state_piece.submitEvent("Interruption");
    c1->state_piece.submitEvent("Interruption");
    l1->state_piece.submitEvent("Interruption");
    b1->state_piece.submitEvent("Interruption");
}

void MainWindow::setAlarmeOn() {
    F3->mLabelAlarme->setText("Alarm On");
    c1->state_piece.submitEvent("setAlarmeOn");
    c2->state_piece.submitEvent("setAlarmeOn");
    l1->state_piece.submitEvent("setAlarmeOn");
    b1->state_piece.submitEvent("setAlarmeOn");
}

void MainWindow::setAlarmeOff() {
    F3->mLabelAlarme->setText("Alarm Off");
    c1->state_piece.submitEvent("setAlarmeOff");
    c2->state_piece.submitEvent("setAlarmeOff");
    l1->state_piece.submitEvent("setAlarmeOff");
    b1->state_piece.submitEvent("setAlarmeOff");
}

void MainWindow::doStart() {
    F3->time->start();
}


void MainWindow::doRefreshDisplay() {
    unsigned int s = (F3->time->elapsed()/1000);
    const QString diff =  QString("%1")
    .arg(s,  2, 10, QChar('0'));

    F3->mTime->setText(diff);
    if (((s % 10) == 0) && s>1) {
        F3_state.submitEvent("ChangementMomentJournee");
    }
}


void MainWindow::doDisplayMatin() {
    F3->mMomentJournee->setText("Matin");
    c1->state_piece.submitEvent("ProgrammerMatin");
    c2->state_piece.submitEvent("ProgrammerMatin");
    b1->state_piece.submitEvent("ProgrammerMatin");
    l1->state_piece.submitEvent("ProgrammerMatin");
}

void MainWindow::doDisplayAprem() {
    F3->mMomentJournee->setText("Aprem");
    c1->state_piece.submitEvent("ProgrammerAprem");
    c2->state_piece.submitEvent("ProgrammerAprem");
    b1->state_piece.submitEvent("ProgrammerAprem");
    l1->state_piece.submitEvent("ProgrammerAprem");
}

void MainWindow::doDisplaySoiree() {
    F3->mMomentJournee->setText("Soiree");
    c1->state_piece.submitEvent("ProgrammerSoiree");
    c2->state_piece.submitEvent("ProgrammerSoiree");
    b1->state_piece.submitEvent("ProgrammerSoiree");
    l1->state_piece.submitEvent("ProgrammerSoiree");

}

void MainWindow::doDisplayNuit() {
    F3->mMomentJournee->setText("Nuit");
    c1->state_piece.submitEvent("ProgrammerNuit");
    c2->state_piece.submitEvent("ProgrammerNuit");
    b1->state_piece.submitEvent("ProgrammerNuit");
    l1->state_piece.submitEvent("ProgrammerNuit");

}

void MainWindow::validerAlarmeOn() {
    F3->mAlarmeEtat->setText("Alarme Allumée");
}

void MainWindow::validerAlarmeOff() {
    F3->mAlarmeEtat->setText("Alarme Eteinte");
}

void MainWindow::validerFenetresOuvertes() {
    F3->mFenetreEtat->setText("Fenetre Ouvertes");
}

void MainWindow::validerFenetresFermees() {
    F3->mFenetreEtat->setText("Fenetre Fermées");
}


void MainWindow::AvertirDomotiqueOuverture() {
    F3_state.submitEvent("OuvertureFenetre");
}

void MainWindow::AvertirDomotiqueFermeture() {
    F3_state.submitEvent("FermetureFenetre");
}
