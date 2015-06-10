#ifndef  YAOJANG_H
#define YAOJANG_H

#include <QDialog>
#include <QImage>
#include <QTimer>
namespace Ui {
class YaoJang;
}

class YaoJang : public QDialog
{
    Q_OBJECT
    
public:
    explicit YaoJang(QWidget *parent = 0);
    ~YaoJang();
    
private:
    Ui::YaoJang *ui;
    /*参与摇奖的人*/
    QString names[5];
    /*定时器指针*/
    QTimer *timer;
    /*绘制标志*/
    bool pflag;
    /*要绘制的图片*/
    QImage img;
    int imgindex;//图片的编号
    /*槽函数，控制标志*/
    public slots:
        void changFlag();
    /*绘制事件处理函数*/
    public:
    void paintEvent(QPaintEvent *);
    /*定时器事件处理函数 */
    void timerEvent(QTimerEvent*);
};

#endif // YAOJANG_H
