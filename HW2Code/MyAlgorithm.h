#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <stack>
#include <queue>
#include "enums.h"

#include "Vacuum.h"
#include "abstract_algorithm.h"
#include "Graph.h"
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
    std::map<std::pair<int,int>, int> house_Map;
    const WallsSensor* wall_Sensor = nullptr;
    const DirtSensor* dirt_Sensor = nullptr;
    const BatteryMeter* battery_Meter = nullptr;
    int curr_X;
    int curr_Y;

    std::shared_ptr<Graph> house_Graph;
    static int MyAlgorithm::curr_Value;
public:
    MyAlgorithm();
    void setMaxSteps(std::size_t maxSteps) override;
	void setWallsSensor(const WallsSensor&) override;
	void setDirtSensor(const DirtSensor&) override;
	void setBatteryMeter(const BatteryMeter&) override;
	Step nextStep() override;
    bool findKeyInMap(const std::pair<int, int> keyToFind);
    
};

#endif
