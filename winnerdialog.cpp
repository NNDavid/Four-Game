#include "winnerdialog.h"
#include <QHBoxLayout>

WinnerDialog::WinnerDialog(int winner,QWidget *parent) :
    QDialog(parent)
{
    if(winner==1) _label = new QLabel(trUtf8("Játékos 1 győzött"));
    else _label = new QLabel(trUtf8("Játékos 2 győzött"));
    setFixedSize(200,80);
    setWindowTitle(trUtf8("Beállítások"));
    setModal(true); // előugró ablak, rögtön megkapja a fókuszt


    _okButton = new QPushButton(trUtf8("OK"));
    _okButton->setFixedSize(75, 23); // a gombok mérete rögzített
    connect(_okButton, SIGNAL(clicked()), this, SLOT(accept())); // elfogadás állapota


    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout->addWidget(_label);

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(_okButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}
