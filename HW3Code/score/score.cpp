#include "score.h"

int Score::calculateScore(bool isDead, bool isFinished, bool inDock, std::size_t maxSteps, std::size_t numSteps, int dirtLeft) {
    const int DEAD_PENALTY = 2000;
    const int NOT_IN_DOCK_PENALTY = 1000;
    const int FINISHED_NOT_IN_DOCK_PENALTY = 3000;
    const int DIRT_PENALTY_MULTIPLIER = 300;

    int score = 0;

    if (isDead) {
        score = maxSteps + dirtLeft * DIRT_PENALTY_MULTIPLIER + DEAD_PENALTY;
    } else if (isFinished && !inDock) {
        score = maxSteps + dirtLeft * DIRT_PENALTY_MULTIPLIER + FINISHED_NOT_IN_DOCK_PENALTY;
    } else {
        score = numSteps + dirtLeft * DIRT_PENALTY_MULTIPLIER + (inDock ? 0 : NOT_IN_DOCK_PENALTY);
    }

    return score;
}
