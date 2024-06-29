#ifndef DIRECTION_H
#define DIRECTION_H

#include <iostream>

enum class Direction {
    STAY = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4
};

Direction intToDirection(int value);

#endif // DIRECTION_H
