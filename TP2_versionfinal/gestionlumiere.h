#ifndef GESTIONLUMIERE_H
#define GESTIONLUMIERE_H

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
#include <QMessageBox>
#include "Lumiere.h"
#include <QTime>
#include <QSpinBox>
#include <QCoreApplication>
#include <QComboBox>
#include <QString>
class GestionLumiere : public QWidget
{
public:
    GestionLumiere(QWidget *parent = nullptr);
    QPushButton *mLumiereTurnOn;
    QPushButton *mLumiereTurnOff;
    QGridLayout *layout;
    QLabel *mLabel;
    QLabel *mProgrammationLumiere;
    QLabel *mAllumage;
    QLabel *mDuree;
    QLabel *mMatin;
    QLabel *mAprem;
    QLabel *mSoiree;
    QLabel *mNuit;
    QSpinBox *editAllumageMatin;
    QSpinBox *editDureeMatin;
    QSpinBox *editAllumageAprem;
    QSpinBox *editDureeAprem;
    QSpinBox *editAllumageSoiree;
    QSpinBox *editDureeSoiree;
    QSpinBox *editAllumageNuit;
    QSpinBox *editDureeNuit;
    QPushButton *mProgrammerLight;
    QSpinBox *editDureeLumiere;
    QComboBox *editIntensiteMinimumMatin;
    QComboBox *editIntensiteMinimumAprem;
    QComboBox *editIntensiteMinimumSoiree;
    QComboBox *editIntensiteMinimumNuit;
    Lumiere lumiere;
    int intensite;
    int intensiteVoulue;
    int intensiteDepart;
    int duree;
public slots:
    void regulerLight();
    void increaseLight();
    void decreaseLight();
};

#endif // GESTIONLUMIERE_H
