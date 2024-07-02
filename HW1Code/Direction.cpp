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
            break;
    }
}

std::ostream& operator<<(std::ostream& os, Direction dir) {
    switch (dir) {
        case Direction::STAY:
            os << "STAY";
            break;
        case Direction::LEFT:
            os << "LEFT";
            break;
        case Direction::RIGHT:
            os << "RIGHT";
            break;
        case Direction::UP:
            os << "UP";
            break;
        case Direction::DOWN:
            os << "DOWN";
            break;
        default:
            os << "Unknown direction";
            break;
    }
    return os;
}