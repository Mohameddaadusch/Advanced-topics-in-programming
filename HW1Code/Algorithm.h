#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <stack>
#include <queue>
#include "Direction.h"

#include "Vacuum.h"

class Algorithm {
    Vacuum& vacuum;
    std::stack<Direction> Path;
    std::queue<Direction> steps_Performed;
public:
    Algorithm(Vacuum& vacuum);
    void decideNextMove(); //give me way to continue cleaning
    void backStep(); //return to dockStation
    bool cleanAlgorithm();
    
};

#endif
