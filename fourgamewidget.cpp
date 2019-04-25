#include "fourgamewidget.h"
#include "ui_fourgamewidget.h"
#include "winnerdialog.h"
#include<QPushButton>
#include<QThread>
FourGameWidget::FourGameWidget(QWidget *parent) :QWidget (parent)
{
   setFixedSize(500,500);
   setWindowTitle(tr("FourGame"));
   newGameButton3=new QPushButton(trUtf8("Új játék 3x3"));
   newGameButton5=new QPushButton(trUtf8("Új játék 5x5"));
   newGameButton7=new QPushButton(trUtf8("Új játék 7x7"));
   connect(newGameButton3,SIGNAL(clicked()),this,SLOT(newGameButtonClicked()));
   connect(newGameButton5,SIGNAL(clicked()),this,SLOT(newGameButtonClicked()));
   connect(newGameButton7,SIGNAL(clicked()),this,SLOT(newGameButtonClicked()));
   mainLayout=new QVBoxLayout();
   scoreLayout=new QGridLayout();
   meret=3;
   tableLayout=new QGridLayout();
   newGameButtonsGrid = new QGridLayout();
   newGameButtonsGrid->addWidget(newGameButton3,0,0);
   newGameButtonsGrid->addWidget(newGameButton5,0,1);
   newGameButtonsGrid->addWidget(newGameButton7, 0,2);
   Player1Label=new QLabel();
   Player1Label->setFont(QFont("Times New Roman",30,QFont::Bold));
   Player1Label->setStyleSheet("QLabel {background-color:rgb(255,0,0)}");
   Player2Label=new QLabel();
   Player2Label->setFont(QFont("Times New Roman",30,QFont::Bold));
   Player2Label->setStyleSheet("QLabel {background-color:rgb(0,0,255)}");
   scoreLayout->addWidget(Player1Label);
   scoreLayout->addWidget(Player2Label);
   mainLayout->addLayout(newGameButtonsGrid);
   mainLayout->addLayout(tableLayout);
   mainLayout->addLayout(scoreLayout);
   setLayout(mainLayout);
   newGame();
}
void FourGameWidget::generateTable()
{

    gameTable = new int*[meret];
    buttonTable.resize(meret);
    for(int i=0;i<meret;i++)
    {
        gameTable[i]=new int[meret];
        buttonTable[i].resize(meret);
        for(int j=0;j<meret;j++)
        {
            gameTable[i][j]=0;
            buttonTable[i][j]=new QPushButton(this);
            buttonTable[i][j]->setFont(QFont("Times New Roman",900/(meret*meret),QFont::Bold));
            buttonTable[i][j]->setText(QString::number(0));
            tableLayout->addWidget(buttonTable[i][j],i,j);
            connect(buttonTable[i][j],SIGNAL(clicked()),this,SLOT(buttonClicked()));
        }
    }
}
void FourGameWidget::newGame()
{
    player=1;
    scorePlayer1=0;
    scorePlayer2=0;

    Player1Label->setFont(QFont("Times New Roman",30,QFont::Bold));
    Player2Label->setFont(QFont("Times New Roman",30,QFont::Bold));
    Player1Label->setText("Játékos 1: "+QString::number(scorePlayer1));
    Player2Label->setText("Játékos 2: "+QString::number(scorePlayer2));
    generateTable();
}
void FourGameWidget::buttonClicked()
{
    QPushButton* sender_button=dynamic_cast<QPushButton*>(QObject::sender());
    int location=tableLayout->indexOf(sender_button);
    stepGame(location / meret,location % meret);
}
void FourGameWidget::newGameButtonClicked()
{
    clearGrid();
    QPushButton* sender_button=dynamic_cast<QPushButton*>(QObject::sender());
    int location=newGameButtonsGrid->indexOf(sender_button);
    switch(location)
    {
        case 0:meret=3;break;
        case 1:meret=5;break;
        case 2:meret=7;break;
        default:meret=3;break;
    }
    newGame();
}
void FourGameWidget::stepGame(int x, int y)
{
    int points=0;
    QString color;
    if(player==1) color="QPushButton {background-color:rgb(255,0,0)}";
    else color="QPushButton {background-color:rgb(0,0,255)}";
    buttonTable[x][y]->setText(QString::number(++gameTable[x][y]));
    if(gameTable[x][y]==4)
    {
        buttonTable[x][y]->setEnabled(false);
        buttonTable[x][y]->setStyleSheet(color);
        points++;
    }
    if(x-1>=0)
    switch(gameTable[x-1][y])
    {
        case 4:
            break;
        case 3:
            buttonTable[x-1][y]->setText(QString::number(++gameTable[x-1][y]));
            buttonTable[x-1][y]->setEnabled(false);
            buttonTable[x-1][y]->setStyleSheet(color);
            points++;
            break;
        default:
            buttonTable[x-1][y]->setText(QString::number(++gameTable[x-1][y]));
            break;
    }
    if(x+1<meret)
    switch(gameTable[x+1][y])
    {
        case 4:
            break;
        case 3:
            buttonTable[x+1][y]->setText(QString::number(++gameTable[x+1][y]));
            buttonTable[x+1][y]->setEnabled(false);
            buttonTable[x+1][y]->setStyleSheet(color);
            points++;
            break;
        default:
            buttonTable[x+1][y]->setText(QString::number(++gameTable[x+1][y]));
            break;
    }
    if(y+1<meret)
    switch(gameTable[x][y+1])
    {
        case 4:
            break;
        case 3:
            buttonTable[x][y+1]->setText(QString::number(++gameTable[x][y+1]));
            buttonTable[x][y+1]->setEnabled(false);
            buttonTable[x][y+1]->setStyleSheet(color);
            points++;
            break;
        default:
            buttonTable[x][y+1]->setText(QString::number(++gameTable[x][y+1]));
            break;
    }
    if(y-1>=0)
    switch(gameTable[x][y-1])
    {
        case 4:
            break;
        case 3:
            buttonTable[x][y-1]->setText(QString::number(++gameTable[x][y-1]));
            buttonTable[x][y-1]->setEnabled(false);
            buttonTable[x][y-1]->setStyleSheet(color);
            points++;
            break;
        default:
            buttonTable[x][y-1]->setText(QString::number(++gameTable[x][y-1]));
            break;
    }
    if(player==1)
    {
        scorePlayer1+=points;
        Player1Label->setText("Játékos 1: "+QString::number(scorePlayer1));
    }
    else
    {
        scorePlayer2+=points;
        Player2Label->setText("Játékos 2: "+QString::number(scorePlayer2));
    }
    player*=-1;
    checkIfOver();

}
void FourGameWidget::checkIfOver()
{
    bool isOver=scorePlayer1+scorePlayer2==meret*meret;
    int winner;

    if(isOver)
    {
        if(scorePlayer1>scorePlayer2) winner=1;
        else winner=2;
        WinDiag=new WinnerDialog(winner);
        WinDiag->exec();
        clearGrid();
        newGame();
    }
}
void FourGameWidget::clearGrid()
{
    foreach(QVector<QPushButton*> row, buttonTable)
    {
           foreach(QPushButton* button,row)
           {
               tableLayout->removeWidget(button);
               delete button;
           }
    }
    for(int i=0;i<buttonTable.size();i++)
     {
        buttonTable[i].clear();
        delete[] gameTable[i];
     }
    delete[] gameTable;
}
