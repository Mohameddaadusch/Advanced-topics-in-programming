#include "score.h"
#include "ostream"
#include "iostream"

int Score::calculateScore(bool isDead, bool isFinished, bool inDock, std::size_t maxSteps, std::size_t numSteps, int dirtLeft) {
    const int DEAD_PENALTY = 2000;
    const int NOT_IN_DOCK_PENALTY = 1000;
    const int FINISHED_NOT_IN_DOCK_PENALTY = 3000;
    const int DIRT_PENALTY_MULTIPLIER = 300;

    int score = 0;

    if (isDead) {
        std::cout<<"the score is case 1" << std::endl;
        score = maxSteps + dirtLeft * DIRT_PENALTY_MULTIPLIER + DEAD_PENALTY;
    } else if (isFinished && !inDock) {
        std::cout<<"the score is case 2" << std::endl;
        score = maxSteps + dirtLeft * DIRT_PENALTY_MULTIPLIER + FINISHED_NOT_IN_DOCK_PENALTY;
    } else {
        std::cout<<"the score is case 3" << std::endl;
        score = numSteps + dirtLeft * DIRT_PENALTY_MULTIPLIER + (inDock ? 0 : NOT_IN_DOCK_PENALTY);
    }

    return score;
}
