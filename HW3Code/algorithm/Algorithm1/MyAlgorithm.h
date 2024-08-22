#ifndef MY_ALGORITHM_H
#define MY_ALGORITHM_H

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




class MyAlgorithm : public AbstractAlgorithm {
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


    
    std::map<Direction,int> min_Map={
        {Direction::East , 0},
        {Direction::North , 0},
        {Direction::West , 0},
        {Direction::South , 0}
    };
    
    std::vector<Direction> directions_Order = {Direction::East , Direction:: North , Direction:: West , Direction::South};


    //std::shared_ptr<Graph> house_Graph;
public:

    MyAlgorithm();
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



    std::string stepToString(Step step);
    std::string directionToString(Direction dir);
};
#endif