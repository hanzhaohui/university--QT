#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include <QDialog>
#include <QLabel>
/*定时器类  这个类中有一个信号 叫timeout()
可以定时的发出这个信号*/
#include <QTimer>
enum DIRECTION{D_UP,D_DOWN,D_LEFT,D_RIGHT};//枚举类型
/*游戏界面类*/
class  SnakeGame:public QDialog{
    Q_OBJECT//如果写了槽函数，就要写与槽函数有关的宏，勿漏
private://（蛇的相关属性）
    /*描述一条蛇(链表实现)*/
    QList<QLabel*>  snake;
    /*描述一个食物*/
    QLabel   *food;
    /*描述蛇运动的方向*/
    DIRECTION  dire;
    /*步长*/
    int        footLen;
    /*最大长度*/
    int        maxLen;
    /*定时器(控制蛇移动)*/
    QTimer     *timer;
public:
    SnakeGame();
    ~SnakeGame();
/*提供功能性函数*/
/*控制蛇移动  根据方向向前走一个步长*/
public slots://槽函数
    void   snakeMove();
/*定时调用移动函数 使用定时器事件处理函数*/
public://覆盖了QDialog类 中的该Protected型的函数，覆盖成public型
    void   timerEvent(QTimerEvent *e);
/*控制方向 使用键盘事件处理函数*/
public:
    void    keyPressEvent(QKeyEvent *e);
/*得到食物的函数*/
    QLabel* getFood();//因为食物也为QLabel*类型
};
#endif // SNAKEGAME_H
