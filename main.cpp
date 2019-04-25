#include "fourgamewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FourGameWidget w;
    w.show();

    return a.exec();
}
