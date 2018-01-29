#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QVBoxLayout>
#include "piece.h"
#include "appartement.h"
#include <QMessageBox>
#include "GestionAppartement.h"

class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void doTurnOffAllLight();
    void setAlarmeOn();
    void setAlarmeOff();
    void doRefreshDisplay();
    void doStart();
    void doDisplayMatin();
    void doDisplayAprem();
    void doDisplaySoiree();
    void doDisplayNuit();
    void validerAlarmeOn();
    void validerAlarmeOff();
    void validerFenetresOuvertes();
    void validerFenetresFermees();
    void AvertirDomotiqueOuverture();
    void AvertirDomotiqueFermeture();
private:
    GestionAppartement F3_state;
    QTabWidget *tabWidget;
    QVBoxLayout *mainLayout;
    Piece *c1;
    Piece *c2;
    Piece *b1;
    Piece *l1;
    Appartement *F3;
};

#endif // MAINWINDOW_H
