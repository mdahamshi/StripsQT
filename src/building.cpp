#include "building.h"

Building::Building()
{

}
Roam Building::firstRoam = Roam(Point(0,0),Point(6,9),1);
Roam Building::secondRoam = Roam(Point(6,0),Point(14,9),2);
Roam Building::thirdRoam = Roam(Point(0,9),Point(14,22),3);
/*
 **********************************
 *          *                     *
 *   5x8    *                     *
 *          *                     *
 ************                     *
 *          *      13x12          *
 *          *                     *
 *  7x8     *                     *
 *          *                     *
 *          *                     *
 *          *                     *
 **********************************
 */
void Building::initializeBoard()
{
    int i = 0 ,j=0;

    //initializing board to free
    for(i=1 ;i < TOTAL_HEIGHT - 1 ;i++)
        for(j=1 ;j < TOTAL_WIDTH - 1 ;j++)
            board[i][j] = Globals::FREE;

    //building walls
    for(i = 0 ;i < TOTAL_HEIGHT ;i++)
    {
        board[i][0] = Globals::WALL;
        board[i][TOTAL_WIDTH - 1] = Globals::WALL;
        board[i][9] = Globals::WALL;
    }
    for(i = 0 ;i < TOTAL_WIDTH ;i++)
    {
        board[0][i] = Globals::WALL;
        board[TOTAL_HEIGHT - 1][i] = Globals::WALL;
        if(i < 10)
            board[6][i] = Globals::WALL;
    }
    //adding required doors


    addDoor(6 ,3 ,4 ,Globals::HOR);
    addDoor(2 ,9 ,3 ,Globals::VER);
    addDoor(8 ,9 ,5 ,Globals::VER);
    objectsMap.clear();


}

void Building::addObject(int firstX, int firstY, int secX, int secY ,int index)
{
    Point topLeft,downRight;
    int roamId;
    int incX = firstX - secX > 0 ? -1 : 1 ;
    int incY = firstY - secY > 0 ? -1 : 1 ;
    for (int i = firstX ;i != secX + incX ;i+=incX)
        for (int j = firstY ;j != secY + incY ;j+=incY){
            if(board[i][j] == Globals::FREE)
                board[i][j] = index;
            else
                std::cout<<"WARNING ! adding object to nonempty location !"<<std::endl;
        }

    topLeft.x = firstX < secX ? firstX : secX;
    topLeft.y = firstY < secY ? firstY : secY;
    downRight.x = firstX > secX ? firstX : secX;
    downRight.y = firstY > secY ? firstY : secY;
    if(downRight <= firstRoam.getDownRightPoint())
        roamId = FIRST_ROAM;
    else if(downRight <= secondRoam.getDownRightPoint())
        roamId = SECOND_ROAM;
    else
        roamId = THIRD_ROAM;

    objectsMap[index] = Furniture(topLeft ,downRight ,index,roamId);
#ifdef _MYDEB_

//    printBoard();
#endif

}
void Building::updateRoam(Furniture &object)
{
    if(object.getDownRightPoint() <= Building::firstRoam.getDownRightPoint())
        object.setRoam( FIRST_ROAM);
    else if(object.getDownRightPoint() <= Building::secondRoam.getDownRightPoint())
        object.setRoam( SECOND_ROAM);
    else
        object.setRoam(THIRD_ROAM);
}

void Building::printObjects()
{
//    list<Furniture>::iterator iter = objectsList.begin();
//    for(; iter != objectsList.end() ;iter++)
//        (*iter).print();
//    for(int i =0 ;i < objectsMap.size() ;i++)
//        objectsMap[i+3].print();

    for(map<int,Furniture>::iterator itr = objectsMap.begin(); itr != objectsMap.end() ;itr++)
        (*itr).second.print();
}

int Building::getObjectNum()
{
    return objectsMap.size();
}
void Building::setTatus(int i, int j, int index)
{
    board[i][j] = index;
}
Building::Building(const Building &source):objectsMap(source.objectsMap)
{
    int i,j;
    for(i=0 ;i < TOTAL_HEIGHT  ;i++)
        for(j=0 ;j < TOTAL_WIDTH  ;j++)
            board[i][j] = source.getStatus(i,j);

}

void Building::addDoor(int row, int col, int size ,int direction)
{
    if(direction == Globals::HOR)
    {
        if(col + size >= TOTAL_WIDTH || row > TOTAL_HEIGHT)
            return;
        for(int i =0 ;i < size ;i++)
            board[row][col+i] = Globals::FREE;
    }
    if(direction == Globals::VER)
    {
        if(row + size >= TOTAL_HEIGHT || col > TOTAL_WIDTH)
            return;
        for(int i =0 ;i < size ;i++)
            board[row+i][col] = Globals::FREE;
    }


}

void Building::printBoard()
{
    cout<<"   ";
    for (int c = 0; c < TOTAL_WIDTH; c++)
        if(c < 9)
            cout<< c <<"  ";
        else
            cout << c << " ";
    cout<<endl;

    for (int r = 0; r < TOTAL_HEIGHT; r++)
    {
        if(r < 10)
            cout<< r << setw(3);
        else
            cout << r << setw(2);
        for (int c = 0; c < TOTAL_WIDTH; c++)
        {
            cout<<board[r][c]<<"  ";
        }
        cout<< endl;
    }
    cout<<endl;
    printObjects();
}
