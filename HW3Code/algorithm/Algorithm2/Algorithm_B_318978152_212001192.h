#ifndef ALGORITHM_B
#define ALGORITHM_B

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
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <iostream>
#include <set>
#include <random>





class Algorithm_B_318978152_212001192 : public AbstractAlgorithm {
    std::stack<Direction> Path;
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
    std::stack<std::pair<Direction, std::pair<int,int>>> path_From_Dock;
    std::set<std::pair<int,int>> cleaned_Set;


    
    std::map<Direction,int> min_Map={
        {Direction::West , 0},
        {Direction::North , 0},
        {Direction::East , 0},
        {Direction::South , 0}
    };
    
    std::vector<Direction> directions_Order = {Direction::West , Direction:: North , Direction:: East , Direction::South};


    //std::shared_ptr<Graph> house_Graph;
public:

    Algorithm_B_318978152_212001192();
    void setMaxSteps(std::size_t maxSteps) override;
	void setWallsSensor(const WallsSensor&) override;
	void setDirtSensor(const DirtSensor&) override;
	void setBatteryMeter(const BatteryMeter&) override;
	Step nextStep() override;
    bool alreadyVisited(const std::pair<int, int> keyToFind);
    Direction getMinDir() ;
    Direction changeDir(std::unordered_set<Direction> history);
    Step convertDirToStep(Direction dir);
    Step backStep();
    void changeCoordinates(Step step_Direction);
    bool checkVisited(Direction direction);
    Direction convertStepToDir(Step step);
    //void setFields();
    bool findPairInSet(const std::set<std::pair<int, int>>& mySet, const std::pair<int, int>& target);
    std::pair<int, int> getCoordinatesInDirection(Direction dir);
    std::set<std::pair<int,int>> path_Set;
    void printPathSet(const std::set<std::pair<int, int>>& path_Set);
    void printPathStack(const std::stack<std::pair<Direction, std::pair<int, int>>>& path_From_Dock);
    std::string stepToString(Step step);
    std::string directionToString(Direction dir);

    Direction intToDirection(int value);
    

};
#endif