#ifndef FENETRE_H
#define FENETRE_H

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
#include <QSpinBox>
#include <QMessageBox>

class Fenetre : public QWidget
{
public:
    QGridLayout *layout;
    QLabel *mLabelFenetre;
    QPushButton *mButtonFenetre;
    Fenetre(QWidget *parent = nullptr);
};

#endif // FENETRE_H
