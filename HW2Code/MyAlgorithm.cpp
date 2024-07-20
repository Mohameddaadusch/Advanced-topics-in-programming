#include "MyAlgorithm.h"
#include "Direction.h"
#include <random>
#include <memory>
#include <list>


MyAlgorithm::MyAlgorithm(){
    std::shared_ptr<Node> dockingStation = std::make_shared<Node>();
    house_Graph= std::make_shared<Graph>(dockingStation);
    bfs_Queue.push(0);
    curr_Value = 0;
    house_Map[std::pair<int,int>(0,0)]=0;
    curr_X=0;
    curr_Y=0;
}

void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    this->max_Steps=maxSteps;
    this->curr_Steps=max_Steps;
}

void MyAlgorithm::setWallsSensor(const WallsSensor& walls_Sensor ){
    this->wall_Sensor = &walls_Sensor;
    
}

void MyAlgorithm::setDirtSensor(const DirtSensor& Dirt_Sensor ){
    this->dirt_Sensor = &Dirt_Sensor;
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter& Battery_Meter){
    this->battery_Meter = &Battery_Meter;
}

Step  MyAlgorithm::nextStep(){
    std::shared_ptr<Node> frontNode= bfs_Queue;
    const_cast<MyDirtSensor*>(dirt_Sensor)->setPosition(curr_X,curr_Y);
    if(dirt_Sensor->dirtLevel() > 0){
        return Step::Stay;
    }
    if (!wall_Sensor->isWall(Direction::West)  && !findKeyInMap(std::pair<int, int>(curr_X,curr_Y-1))){
        house_Map[std::pair<int,int>(curr_X,curr_Y-1)] = 0;
        return Step::West;
    }
    else if (!wall_Sensor->isWall(Direction::North)  && !findKeyInMap(std::pair<int, int>(curr_X-1,curr_Y))){
        house_Map[std::pair<int,int>(curr_X-1,curr_Y)]=0;
        return Step::North;

    }
    else if (!wall_Sensor->isWall(Direction::East)  && !findKeyInMap(std::pair<int, int>(curr_X,curr_Y+1))){
        house_Map[std::pair<int,int>(curr_X,curr_Y+1)]=0;
        return Step::East;

    }
    else if (!wall_Sensor->isWall(Direction::South)  && !findKeyInMap(std::pair<int, int>(curr_X+1,curr_Y))){
        house_Map[std::pair<int,int>(curr_X+1,curr_Y)]=0;
        return Step::South;
    }
    //exit from Queue
    bfs_Queue.pop();
}


bool MyAlgorithm::findKeyInMap( const std::pair<int, int>& keyToFind){ 
    auto it = house_Map.find(keyToFind);
    return it != house_Map.end(); 
}





