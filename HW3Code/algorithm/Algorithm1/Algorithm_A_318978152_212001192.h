#ifndef ALGORITHM_A
#define ALGORITHM_A

#include "../../common/AlgorithmRegistrar.h"
#include "../../common/AbstractAlgorithm.h"
#include "../../common/BatteryMeter.h"
#include "../../common/DirtSensor.h"
#include "../../common/WallSensor.h"
#include "../../common/enums.h"
#include "../algorithm/AlgorithmRegistration.h"



#include <stack>
#include <queue>
#include <map>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>




class Algorithm_A_318978152_212001192 : public AbstractAlgorithm {
    std::stack<Direction> Path;
    std::stack<std::pair<Direction, std::pair<int,int> >> path_From_Dock;
    std::set<std::pair<int,int>> path_Set;
    std::queue<int> bfs_Queue;
    std::queue<Step> steps_Performed;
    int max_Steps;
    int curr_Steps;
    std::map<std::pair<int,int> , int > visited;
    const WallsSensor* wall_Sensor = nullptr;
    const DirtSensor* dirt_Sensor = nullptr;
    const BatteryMeter* battery_Meter = nullptr;
    int curr_X;
    int curr_Y;
    float maxBattery;
    std::stack<std::pair<int,int>> unexplored_Stack;
    std::set<std::pair<int,int>> cleaned_Set;
    std::stack<Direction> path_To_LastPoint;
    bool returning_To_LastPoint=true;
    std::map<std::pair<int,int> , int > distance;
    std::map<std::pair<int,int> , std::pair<int,int> > parent;
    std::vector<Direction> tmp_Steps;
    std::vector<Direction> old_tmp_Steps;



public:

    Algorithm_A_318978152_212001192();
    void setMaxSteps(std::size_t maxSteps) override;
	void setWallsSensor(const WallsSensor&) override;
	void setDirtSensor(const DirtSensor&) override;
	void setBatteryMeter(const BatteryMeter&) override;
	Step nextStep() override;
    bool alreadyVisited(const std::pair<int, int> keyToFind);
    Step convertDirToStep(Direction dir);
    Step backStep();
    void changeCoordinates(Step step_Direction);
    bool checkVisited(Direction direction);
    Direction convertStepToDir(Step step);
    int discoverUnexploredPoints();
    std::pair<int, int> getCoordinatesInDirection(Direction dir);
    bool findPairInSet(const std::set<std::pair<int, int>>& mySet, const std::pair<int, int>& target);
    Step returnToLastPoint();
    Direction reverseDirection(Direction direction);

    
    
    
};
#endif