#ifndef WINNERDIALOG_H
#define WINNERDIALOG_H
#include <QDialog>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
class WinnerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WinnerDialog(int winner,QWidget *parent = 0);

private:
    QLabel *_label;
    QPushButton *_okButton;
};

#endif // WINNERDIALOG_H
