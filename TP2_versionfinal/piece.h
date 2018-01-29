#ifndef CHAMBREC1_H
#define CHAMBREC1_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "Regulateur.h"
#include "PieceState.h"
#include "temperature.h"
#include "gestionlumiere.h"
#include <QSpinBox>
#include <QMessageBox>
#include "gestionnairealarme.h"
#include "Alarme.h"
#include "fenetre.h"

class Piece : public QWidget
{
    Q_OBJECT
public:
    Piece(QWidget *parent = nullptr, QString nom = QString("Piece"), int tE = 20, int tP = 20);
    ~Piece();
    QPushButton *mBouton1;
    PieceState state_piece;
    QPushButton *mAmbianceCinema;
    QString *nomPiece;
    Temperature *temp;
    Fenetre *fenetre;
    GestionnaireAlarme *gAlarme;
    GestionLumiere *lum;
    QLabel *mLabelNomPiece;
    QLabel *mEtatAlarme;

public slots:
    void turnOffTemp();
    void doAllumer();
    void doStartLight();
    void doTurnOffLumiere();
    void doTurnOffLumiereInterruption();
    void AnalyserAlarme();
    void RevenirAEtat();
    void WarnUserProblemSolved();
    void doProgrammerMatin();
    void doProgrammerAprem();
    void doProgrammerSoiree();
    void doProgrammerNuit();
    void doValiderProgrammation();
    void doOpenWindowPiece();
    void doCloseWindowPiece();
    void dosetAlarmeOn();
    void setAlarmeOff();
    void doProgrammerRadiateurMatin();
    void doProgrammerRadiateurAprem();
    void doProgrammerRadiateurSoiree();
    void doProgrammerRadiateurNuit();
    void setTurnOn();
    void doAmbianceCinema();
    void doProgrammerRadiateur();
    void doDeProgrammerRadiateur();
    void doDeprogrammer();
    void doAnalyseLight();
    void doTurnOnManually();
private:
    QGridLayout *layout;
};

#endif // CHAMBREC1_H
