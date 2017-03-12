#ifndef GLOBALS_H
#define GLOBALS_H

#define BUILD_WIDTH 20
#define BUILD_HEIGHT 12
#define VER_WALLS 3
#define HOR_WALLS 3
#define TOTAL_WIDTH (BUILD_WIDTH + HOR_WALLS)
#define TOTAL_HEIGHT (BUILD_HEIGHT + VER_WALLS)
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
    Globals();
};

#endif // GLOBALS_H
