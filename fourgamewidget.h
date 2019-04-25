#ifndef FOURGAMEWIDGET_H
#define FOURGAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QColor>
#include <QLabel>
#include "winnerdialog.h"

class FourGameWidget : public QWidget
{
    Q_OBJECT

public:
    FourGameWidget(QWidget *parent = nullptr);

private slots:
    void buttonClicked();
    void newGameButtonClicked();

private:
    int meret;
    int player;
    int scorePlayer1;
    int scorePlayer2;
    int** gameTable;
    QGridLayout* tableLayout;
    QGridLayout* newGameButtonsGrid;
    QVBoxLayout* mainLayout;
    QGridLayout* scoreLayout;
    QPushButton* newGameButton3;
    QPushButton* newGameButton5;
    QPushButton* newGameButton7;
    QLabel* Player1Label;
    QLabel* Player2Label;
    QVector<QVector<QPushButton*>> buttonTable;
    void newGame();
    void generateTable();
    void stepGame(int x,int y);
    void checkIfOver();
    void clearGrid();
    WinnerDialog* WinDiag;
};

#endif // FOURGAMEWIDGET_H
