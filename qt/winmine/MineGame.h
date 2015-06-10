#ifndef MINEGAME_H
#define MINEGAME_H
#include "MineGame.h"
#include "Cell.h"
#include <QDialog>
#include <QPaintEvent>
#include <QMouseEvent>

class MineGame:public QDialog{
private:
    Cell  mine_map[9][9];
    QImage *img;
    bool  gameover;
public:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
        MineGame();
        void initGame();
        void setMines();                            // ²¼À×
        int  getAroundMineNum(int row, int col);
        void expandMines(int row, int col);
        CState  getState(int par);


};
#endif // MINEGAME_H
