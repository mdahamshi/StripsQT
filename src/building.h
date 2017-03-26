#ifndef BUILDING_H
#define BUILDING_H
#include "globals.h"
#include "roam.h"
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
using namespace std;




class Building
{

public:
    int board[TOTAL_HEIGHT][TOTAL_WIDTH];
    static Roam firstRoam,secondRoam,thirdRoam;

    std::map <int,Furniture> objectsMap;

    void initializeBoard();
    Building(const Building &source);
    void printBoard();
    void updateRoam(Furniture &object);
    int getObjectNum();
    void addDoor(int row ,int col ,int size ,int direction);
    int getStatus(int i, int j) const{return board[i][j];}
    void setTatus(int i ,int j ,int index);
    int getBoardSize(){return TOTAL_HEIGHT * TOTAL_WIDTH;}
    void addObject(int firstX ,int firstY ,int secX ,int secY ,int index );
    void printObjects();
    Building();
};

#endif // BUILDING_H
