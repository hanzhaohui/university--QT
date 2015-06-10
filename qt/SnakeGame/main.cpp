#include  "snakegame.h"
#include <QApplication>

int main(int argc,char **argv){
    QApplication  app(argc,argv);
    SnakeGame   sg;//创造一个贪吃蛇
    sg.show();
    return app.exec();
}

