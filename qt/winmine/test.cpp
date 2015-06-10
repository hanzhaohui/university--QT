
#include <QtGui/QApplication>
#include "MineGame.h"
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MineGame w;


    w.show();
    return  w.exec();

}
