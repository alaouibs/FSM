#ifndef TEMPERATURE_H
#define TEMPERATURE_H

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
#include <QMessageBox>
#include <QSpinBox>

class Temperature : public QWidget
{
    Q_OBJECT
public:
    Temperature(QWidget *parent = nullptr, int tE = 20, int tP = 20);
    virtual ~Temperature() {};
    int temperatureEnvironnement;
    int temperaturePiece;
    int temperatureDemande;
    Regulateur regul;
    QGridLayout *layout;
    QPushButton *mTemperature;
    QLabel *mLabel;
    QLabel *mLabelTemperatureEtat;
    QSpinBox *editTemperature;

    QLabel *mMatin;
    QLabel *mAprem;
    QLabel *mSoiree;
    QLabel *mNuit;
    QSpinBox *editAllumageMatin;
    QSpinBox *editAllumageAprem;
    QSpinBox *editAllumageSoiree;
    QSpinBox *editAllumageNuit;

    QPushButton *mProgrammerTemperature;
public slots:
    void reguler();
    void increase();
    void decrease();
};

#endif // TEMPERATURE_H
