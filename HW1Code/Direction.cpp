#include "Direction.h"

Direction intToDirection(int value) {
    switch (value) {
        case 0:
            return Direction::STAY;
        case 1:
            return Direction::LEFT;
        case 2:
            return Direction::RIGHT;
        case 3:
            return Direction::UP;
        case 4: 
            return Direction::DOWN;
        default:
            throw std::invalid_argument("Invalid integer value for Direction");
    }
}
