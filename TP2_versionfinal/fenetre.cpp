#include "fenetre.h"

Fenetre::Fenetre(QWidget *parent)
    :QWidget(parent)
{
    layout = new QGridLayout;

    mLabelFenetre = new QLabel("Fenêtre fermée");
    mButtonFenetre = new QPushButton("Fenetre");

    layout->addWidget(mLabelFenetre, 0, 1);
    layout->addWidget(mButtonFenetre, 0, 0);
    this->setLayout(layout);
}
