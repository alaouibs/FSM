#ifndef APPARTEMENT_H
#define APPARTEMENT_H

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

class Appartement : public QWidget
{
public:
    QTime *time;
    int cycle;
    int debut_cycle;
    Appartement(QWidget *parent = nullptr);
    QGridLayout *layout;
    QPushButton *mEteindreToutLumieres;
    QPushButton *mAlarme;
    QLabel *mLabelAlarme;
    QLabel *mTime;
    QLabel *mLabelTime;
    QLabel *mMomentJournee;
    QLabel *mFenetreEtat;
    QLabel *mAlarmeEtat;
    int compteur;
};

#endif // APPARTEMENT_H
