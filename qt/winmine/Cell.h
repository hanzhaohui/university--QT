#ifndef CELL_H
#define CELL_H
enum CState{S_NORMAL,S_FLAG,S_ASK,S_OVER,S_ERROR,S_MINE,S_NUSE,
        S_EIT,S_SEVEN,S_SIX,S_FIVE,S_FOUR,S_THREE,S_TWO,S_ONE,S_ZERO};
struct Cell{
    //ÓÐÎÞÀ×
    bool  flag;
    //×´Ì¬
    CState state;
};

#endif // CELL_H
