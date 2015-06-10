#include "MineGame.h"
#include <QPainter>
#include <QMessageBox>
#include <QTime>
void MineGame::initGame(){
    qsrand(QTime().currentTime().msec());
    this->setWindowTitle("win wine");
    gameover=false;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
        Cell ce={false,S_NORMAL};
        mine_map[i][j]=ce;
        }
    }

}
void MineGame::setMines(){
    for(int i=0;i<9;i++){
         mine_map[qrand()%9][qrand()%9].flag=true;
    }
}
MineGame::MineGame(){
    initGame();
    setMines();
    setMinimumSize(9*16,11*16);
    setMaximumSize(9*16, 11*16);

}

void MineGame::paintEvent(QPaintEvent *){

    img=new QImage(":/410.bmp");
    QPainter p(this);
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
        {
                    QPoint cell_topleft = QPoint(16*(j-1), 16*(i-1)+32);
                    QRect img_rect = QRect(QPoint(0, (mine_map[(i-1)][j-1].state)*16), QSize(16, 16));
                   /* p.drawLine(0,0,160,0);
                    p.drawLine(0,0,160,0);
                    p.drawLine(0,i*16,160,i*16);
                    p.drawLine(j*16,48,j*16,160);*/
                    p.drawImage(cell_topleft, *img, img_rect);

                   // p.drawText(cell_topleft,QString::number(i));

        }

}
CState  MineGame::getState(int par){
  /*  S_NORMAL,S_FLAG,S_ASK,S_OVER,S_ERROR,S_MINE,S_NUSE,
            S_EIT,S_SEVEN,S_SIX,S_FIVE,S_FOUR,S_THREE,S_TWO,S_ONE,S_ZERO*/
    switch(par){
    case 15:
        return S_NORMAL;
    case 14:
        return S_FLAG;
    case 13:
        return S_ASK;
    case 12:
        return S_OVER;
    case 11:
        return S_ERROR;
    case 10:
        return S_MINE;
    case 8:
        return  S_EIT;
    case 7:
        return S_SEVEN;
    case 6:
        return S_SIX;
    case 5:
        return S_FIVE;
    case 4:
        return S_FOUR;
    case 3:
        return S_THREE;
    case 2:
        return S_TWO;
    case 1:
        return S_ONE;
    case 0:
        return S_ZERO;
    }

}
void MineGame::mousePressEvent(QMouseEvent *e){
    if(gameover){
    return;
    }
    int x=e->x();
    int y=e->y();
    if(e->button()==Qt::RightButton){
        if(mine_map[(y-32)/16][x/16].state==S_NORMAL){
           mine_map[(y-32)/16][x/16].state=S_FLAG;
        }else if( mine_map[(y-32)/16][x/16].state==S_FLAG){
           qDebug("test flag");
           mine_map[(y-32)/16][x/16].state=S_ASK;
       }else if(mine_map[(y-32)/16][x/16].state==S_ASK){
           mine_map[(y-32)/16][x/16].state=S_NORMAL;
       }
        repaint();
        return ;
    }
    if(mine_map[(y-32)/16][x/16].flag==true){
       mine_map[(y-32)/16][x/16].state=S_OVER;
       for(int row=0;row<9;row++){
           for(int col=0;col<9;col++){
               if(mine_map[row][col].flag==true&& mine_map[row][col].state!=S_OVER){
                   if(mine_map[row][col].state==S_NORMAL){
                   mine_map[row][col].state=S_MINE;
                   }else if(mine_map[row][col].state==S_FLAG){
                   mine_map[row][col].state=S_ERROR;

                   }
               }
           }
       }
       gameover=true;
       repaint();
       return;
    }
    qDebug("%d:%d",(y-32)/16,x/16);
     expandMines((y-32)/16,x/16);
    repaint();
}
void MineGame::expandMines(int row, int col){
    int num = getAroundMineNum(row, col);
    if(num>0&&num<8&&mine_map[row][col].state==S_NORMAL){
    Cell c={false,getState(num)};
    mine_map[row][col]=c;
    qDebug("test");
   }else{
       Cell c={false,getState(num)};
       mine_map[row][col]=c;
    }
    int i,j;
    if(num==0){
        for (i = row-1; i<9&&i <= row+1; i++){
            if (i<0)
                continue;
            for (j = col-1;j<9 &&j <= col+1; j++)
            {
                if (j<0) continue;
                if(mine_map[i][j].state==S_NORMAL&&mine_map[i][j].flag==false){
                expandMines(i, j);
                }
            }
        }
    }
}
int  MineGame::getAroundMineNum(int row, int col){
       int i, j, num;
        num = 0;
        for (i = row-1; i<9&&i <= row+1; i++){
            if (i<0)
                continue;
            for (j = col-1;j<9 &&j <= col+1; j++)
            {
                if (j<0) continue;
                if (mine_map[i][j].flag == true)
                    num++;
            }
        }
        return num;

}
