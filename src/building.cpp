#include "building.h"

Building::Building()
{

}
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
//    cout<<endl;
}
