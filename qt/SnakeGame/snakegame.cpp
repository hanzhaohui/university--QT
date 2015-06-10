#include "snakegame.h"
#include <QTime>
#include <QMessageBox>
#include <QColor>//因为需要设置调色板时有QColor而要包含
#include <iostream>
using namespace std;
SnakeGame::SnakeGame(){
    this->resize(800,700);//调整界面大小,全屏时为1024x768
    qsrand(QTime::currentTime().msec());
    footLen=60;//一个步长（因为footLen在getFood函数中会使用到，所以要在该函数调用前，对该值进行初始化）

    snake.push_back(getFood());//先产生蛇头，再在下面产生食物
    food=getFood();

    dire=D_RIGHT;//初始化方向向右
    maxLen=5;
    /*启动定时器事件*/
    //this->startTimer(200);
    timer=new QTimer();
    /*每隔0.2秒发出timeout()信号*/
    timer->setInterval(200);
    timer->start();
    /*发出信号，蛇进行移动*/
    connect(timer,SIGNAL(timeout()),
            this,SLOT(snakeMove()));
}
SnakeGame::~SnakeGame(){

}
/*提供功能性函数*/
/*控制蛇移动  根据方向向前走一个步长*/
void   SnakeGame::snakeMove(){
    /*蛇头原来的位置*/
    int  x=snake[0]->x();
    int  y=snake[0]->y();
    /*思考如何吃掉食物 ：蛇头和食物坐标重合*/
    if(food->x()==x && food->y()==y){
        snake.push_back(food);
        food=getFood();//吃掉一个食物后，就产生一个食物
    }
    /*加逻辑判断*/
    //当蛇达到最大长度
    if(snake.size()>=maxLen){
         QMessageBox  msg;
         msg.setText("game over!");
         msg.setStandardButtons
        (QMessageBox::Yes|QMessageBox::No);
         if(msg.exec()==QMessageBox::Yes){
              this->close();
         }else{
              maxLen=maxLen*2+1;
         }
    }
         /*撞墙程序结束*/
         if(x<0||y<0||x>this->width()||y>this->height()){
             QMessageBox msg;
             msg.setText("game over!");
             msg.exec();
             this->close();
         }
    /*后面的跟着前面的走（食物跟着蛇头跑）*/
    //规律：蛇头移到新位置，后一个食物移动到前一个元素的位置
    int  count=snake.size();//蛇链表的长度
    for(int i=count-1;i>0;i--){
        snake[i]->move(snake[i-1]->x(),
                       snake[i-1]->y());
    }//snake[i]指后一个元素，snake[i-1]指前一个元素
    switch(dire){
        case  D_UP: y=y-footLen;break;
        case  D_DOWN:y=y+footLen; break;
        case D_LEFT:x=x-footLen;break;
        case D_RIGHT:x=x+footLen;break;
    }
    /*让蛇头走到新坐标*/
    snake[0]->move(x,y);
}
/*定时调用移动函数 使用定时器事件处理函数*/
void   SnakeGame::timerEvent(QTimerEvent *e){
    snakeMove();
}
/*控制方向 使用键盘事件处理函数*/
#include<QKeyEvent>
void    SnakeGame::keyPressEvent
(QKeyEvent *e){
    switch(e->key()){
        case  Qt::Key_Up:
        dire=D_UP;
        break;
        case Qt::Key_Down:
        dire=D_DOWN;
        break;
        case  Qt::Key_Left:
        dire=D_LEFT;
        break;
        case Qt::Key_Right:
        dire=D_RIGHT;
        break;
    }
}
/*得到食物的函数*/
QLabel* SnakeGame::getFood(){
    food=new QLabel(this);//food窗口依赖于父窗口，表明Food子窗口是动态的
    food->resize(footLen,footLen);//建立食物与步长的关系（重合时表示食物被吃掉）
    food->setFrameShape(QFrame::Box);//设置QLabel的边框
    food->setAutoFillBackground(true);//设置自动填充背景色
    /*设置调色板（食物的颜色随机）*/
    food->setPalette(QPalette(
         QColor(qrand()%256,qrand()%256,
                qrand()%256)));
    /*蛇头当前的位置*/
    int  w=this->width()-footLen;//界面大小减去footLen，可以精确控制生成的点不会超出虚线的范围，不会越界
    int  h=this->height()-footLen;
    /*随机  界面范围内
    footLen的整数倍（让食物随机移动）*/
/*位置随机，界面以内，footLen的整数倍*/
    food->move(
    ((qrand()%w)/footLen)*footLen,//除以再乘以footLen,就可以实现界面范围内的footLen的整数倍
                //因为C语言的除法具有取整特性
    ((qrand()%h)/footLen)*footLen);
    food->show();//因为针对静态窗口，父窗口show()了，子窗口就不要show()了，可是在这里的Food窗口是动态的，要自己不断show ,父窗口show一次后不会再show一次
    return  food;
}


