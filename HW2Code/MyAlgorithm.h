#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <stack>
#include <queue>
#include "enums.h"
#include <stdio.h>
#include <unordered_set>
#include "Vacuum.h"
#include "abstract_algorithm.h"
#include <map>
#include "MyDirtSensor.cpp"
#include "MyWallSensor.cpp"
#include "MyBatteryMeter.cpp"



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



    std::string stepToString(Step step);
    std::string directionToString(Direction dir);
};

#endif
