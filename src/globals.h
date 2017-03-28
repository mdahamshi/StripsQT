#ifndef GLOBALS_H
#define GLOBALS_H

#include <strings.h>
#include <iostream>
#define BUILD_WIDTH (20)
#define BUILD_HEIGHT (12)
#define VER_WALLS (3)
#define HOR_WALLS (3)
#define TOTAL_WIDTH (BUILD_WIDTH + HOR_WALLS)
#define TOTAL_HEIGHT (BUILD_HEIGHT + VER_WALLS)
#define COLOR_NUM (12)
#define ofROOM (1)
#define ofOBJECT (2)
#define STARTID (3)

//action types
#define MOVE_RIGHT 1
#define MOVE_LEFT 6
#define MOVE_UP 5
#define MOVE_DOWN 2
#define ROTATE_RIGHT 4
#define ROTATE_LEFT 3
// StackNode types
#define SINGLE_PREDICATE 1
#define CONJUNCTION 2
#define ACTION 3
#define GENERAL_PREDICATE 4
#define GENERAL_PREDICATE_CONJUNCTION 5
extern bool disablFir ;
/*
 **********************************
 *          *                     *
 *   5x8                          *
 *  first   *                     *
 *          *                     *
 ***     ****                     *
 *          *      13x12          *
 *                                *
 * second          third          *
 *  7x8     *                     *
 *          *                     *
 **********************************
 */
//roams
#define FIRST_ROAM (1)
#define SECOND_ROAM (2)
#define THIRD_ROAM (3)
/*
 **********************************
 *          *                     *
 *   5x8   sec                    *
 *          *                     *
 ****first***                     *
 *          *      13x12          *
 *          *                     *
 *  7x8     *                     *
 *        third                   *
 *          *                     *
 *          *                     *
 **********************************
 */
//doors
#define FIRST_DOOR (1)
#define SECOND_DOOR (2)
#define THIRD_DOOR (3)

#define _MYDEB_

extern bool resetRequest; //global variable to cancel work in case reset button pressed
extern bool pause;



class Globals
{
public:
    enum{
        NOSOL,
        SOLVED,
        RESET
    };
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
