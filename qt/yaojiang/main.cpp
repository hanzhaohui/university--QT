#include "yaojang.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YaoJang w;
    w.show();
    
    return a.exec();
}
