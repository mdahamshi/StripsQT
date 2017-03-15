#ifndef GLOBALS_H
#define GLOBALS_H

#define BUILD_WIDTH 20
#define BUILD_HEIGHT 12
#define VER_WALLS 3
#define HOR_WALLS 3
#define TOTAL_WIDTH (BUILD_WIDTH + HOR_WALLS)
#define TOTAL_HEIGHT (BUILD_HEIGHT + VER_WALLS)
#define _MYDEB_
typedef struct myPoint {
    int x;
    int y;
    myPoint(){

    }
    myPoint(int a, int b){
        x = a;
        y = b;
    }
}Point;

typedef struct myObject{
    Point first;
    Point second;
    int colorIndex;
    myObject(){

    }
    myObject(Point a ,Point b ,int c){
        first = a;
        second = b;
        colorIndex = c;
    }
}Object;

class Globals
{
public:
    enum{
        WALL,
        FREE,
        FULL
    };
    enum{
        UP,
        DOWN,
        RIGHT,
        LEFT
    };
    enum{
        HOR,
        VER
    };
    enum{
        CURRENT_BOARD,
        DESIRED_BOARD
    };
    Globals();
};

#endif // GLOBALS_H
