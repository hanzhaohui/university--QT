#include "yaojang.h"
#include "ui_yaojang.h"
#include <QImage>
#include <QTime>
#include <iostream>
using namespace std;
YaoJang::YaoJang(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YaoJang)
{
     qsrand(QTime::currentTime().msec());
    ui->setupUi(this);
    /*初始化数组*/
    names[0]="xiaoli";
    names[1]="xiaobei";
    names[2]="xiaomei";
    names[3]="bingbing";
    names[4]="beibei";
    pflag=false;//为false时不重画
    /*制造定时器事件*/
    this->startTimer(100);
    /*构建定时器*/
   /* timer=new QTimer();
    timer->setInterval(200);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));*/
    connect(ui->bstart,SIGNAL(clicked()),this,SLOT(changFlag()));
    connect(ui->bstop,SIGNAL(clicked()),this,SLOT(changFlag()));
}

YaoJang::~YaoJang()
{
    delete ui;
}
void  YaoJang::timerEvent(QTimerEvent*){
    repaint();

}

#include <QPainter>
 void YaoJang::paintEvent(QPaintEvent *){
    QPainter qp(this);//创建一个画画类型的对象
    /*画一条对角线*/
   // qp.drawLine(0,0,400,600);
	 if(pflag){
    imgindex=(qrand()%5)+1;
    QString imgstr=":/images/";
    imgstr+=QString::number(imgindex);
    imgstr+=".jpg";
    img.load(imgstr);

    img=img.scaled(320,480);
    qp.drawImage(40,40,img,0,0,220,380);
	 ui->personName->setText(names[imgindex-1]);
	 }
	 qp.drawImage(40, 40, img, 0, 0, 320, 480);

 }

 //点击start,pflag=true;点击stop,pflag=false
 void YaoJang::changFlag(){
    if(((QPushButton*)sender())->objectName()=="bstart")
         pflag=true;
    if(((QPushButton*)sender())->objectName()=="bstop")
         pflag=false;
 }
