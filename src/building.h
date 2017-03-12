#ifndef BUILDING_H
#define BUILDING_H
#include "globals.h"
#include <iomanip>
#include <iostream>
using namespace std;
class Building
{

public:
    int board[TOTAL_HEIGHT][TOTAL_WIDTH];
    void initializeBoard();
    void printBoard();
    void addDoor(int row ,int col ,int size ,int direction);
    int getStatus(int i, int j){return board[i][j];}
    int getBoardSize(){return TOTAL_HEIGHT * TOTAL_WIDTH;}
    Building();
};

#endif // BUILDING_H
