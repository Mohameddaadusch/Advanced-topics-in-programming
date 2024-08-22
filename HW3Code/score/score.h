
#ifndef SCORE_H
#define SCORE_H
#include <cstddef>

class Score {
public:
    static int calculateScore(bool isDead, bool isFinished, bool inDock, std::size_t maxSteps, std::size_t numSteps, int dirtLeft);
};

#endif