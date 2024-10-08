#include "MyAlgorithm.h"
#include "enums.h"
#include <random>
#include <memory>
#include <list>
#include <algorithm>
#include <unordered_set>
#include <limits>


MyAlgorithm::MyAlgorithm(){
    //std::shared_ptr<Node> dockingStation = std::make_shared<Node>();
    //house_Graph= std::make_shared<Graph>(dockingStation);
    //bfs_Queue.push(0);
    //curr_Value = 0;
    visited[std::pair<int,int>(0,0)]=0;
    curr_X=0;
    curr_Y=0;
}



void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    this->max_Steps=maxSteps;
    this->curr_Steps=0;
}

void MyAlgorithm::setWallsSensor(const WallsSensor& walls_Sensor ){
    std::cout<<"initializing wallsensor"<<std::endl;
    this->wall_Sensor = &walls_Sensor;
    
}

void MyAlgorithm::setDirtSensor(const DirtSensor& Dirt_Sensor ){
    this->dirt_Sensor = &Dirt_Sensor;
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter& Battery_Meter){
    this->battery_Meter = &Battery_Meter;
    this->maxBattery=Battery_Meter.getBatteryState();
}

Direction MyAlgorithm::getMinDir() {
    int min=std::min({ min_Map[Direction::East], min_Map[Direction::North], min_Map[Direction::West] , min_Map[Direction::South] });
    if (min_Map [Direction::East] == min){
        return Direction::East;
    }else if(min_Map[Direction::North] == min){
        return Direction::North;
    }else if(min_Map[Direction::West] == min){
        return Direction::West;
    }else{
        return Direction::South;
    }
}

Direction MyAlgorithm::changeDir(std::unordered_set<Direction> history){
    std::map<Direction,int> newMap=min_Map;
    for (const Direction& dir: history){
        newMap.erase(dir);
    }
    int min=std::numeric_limits<int>::max();
    Direction res;
    for(const auto& key : directions_Order){
        if (newMap.find(key)!=newMap.end() && newMap[key]<min){
            min=newMap[key];
            res=key;
        }
        
    }
    
    return res;
}

Step MyAlgorithm::convertDirToStep(Direction dir){
    if(dir == Direction::East){
        return Step::East;
    }
    else if(dir == Direction::North){
        return Step::North;
    }
    else if(dir == Direction::South){
        return Step::South;
    }
    else{
        return Step::West;
    }


}

Step  MyAlgorithm::nextStep(){
    std::cout<<"step number :  " << curr_Steps+1 << std::endl;
    Step step_Direction=Step::Stay;
    bool fromBack=false;
    Direction direction;
    std::unordered_set<Direction> history;
    std::cout<<"the battery is @@@@@@@@@@@@@@@@@@@    "<< battery_Meter->getBatteryState() << " ,the path size is@@@@@@@@@@@  "<< Path.size()<<std::endl;

    if (dirt_Sensor->dirtLevel()==0){
        std::cout<<"curr x cur y  ------------------------------------------ :  " << curr_X<< ","<< curr_Y << std::endl;
        visited[std::pair<int,int>(curr_X,curr_Y)]=0;
        std::cout<<"curr x cur y  ------------------------------------------ :  " << curr_X<< ","<< curr_Y << std::endl;

    }
    for (const auto& pair : min_Map) { 
        std::cout << directionToString(pair.first) << ": " << pair.second << ", "; 
    }
    std::cout<<"" << std::endl;
    std::cout<<"current steps !!!!!!!!!!!! :  " << curr_Steps<< ", max steps !!!!!!!!!!!!!!!!!!!!!!!"<< max_Steps << std::endl;

    if(curr_Steps >= max_Steps){
        std::cout<<"finiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiish" << std::endl;

        step_Direction = Step::Finish;
        curr_Steps--;
    }
    else if ((Path.size()==0) && (battery_Meter->getBatteryState() < maxBattery)){
        std::cout<<"charging (3)  " <<std::endl;
        step_Direction = Step::Stay;
    }
    else if(battery_Meter->getBatteryState() <= Path.size() +1 || (max_Steps-curr_Steps) <= (int)Path.size() ){
        std::cout<<"backstep (1) ************************************************************************************** " <<std::endl;
        step_Direction = backStep();
        direction = convertStepToDir(step_Direction);
        fromBack=true;
    }
    else if(wall_Sensor->isWall(Direction::North) && wall_Sensor->isWall(Direction::South) && wall_Sensor->isWall(Direction::West) && wall_Sensor->isWall(Direction::East)){
        std::cout<<"4 walls arround (2) " <<std::endl;
        step_Direction=Step::Stay;
    }
    else if (dirt_Sensor->dirtLevel() > 0){
        std::cout<<"cleaning (4) " <<std::endl;
        step_Direction=  Step::Stay;
    }
    else{
        std::cout<<"Normall sTEP (else) " <<std::endl;
        direction= getMinDir();
        std::cout<<"the min is:  --------"<<directionToString(direction) <<std::endl;

        if((!wall_Sensor->isWall(Direction::North) && !checkVisited(Direction::North)) || (!wall_Sensor->isWall(Direction::South) && !checkVisited(Direction::South)) 
            || (!wall_Sensor->isWall(Direction::West) && !checkVisited(Direction::West)) || (!wall_Sensor->isWall(Direction::East) && !checkVisited(Direction::East))){
            while(wall_Sensor->isWall(direction) || checkVisited(direction)){
                std::cout<<"the direction: ^^^^^^^^^ "<< directionToString(direction)<< " is or wall or visited"<<std::endl;
                history.insert(direction);
                direction=changeDir(history);
                std::cout<<"changed the direction: "<< directionToString(direction)<<std::endl;
            }
            std::cout<<"here (newwwwwwwwwwwww) " <<std::endl;

            min_Map[direction]+=1;
            step_Direction = convertDirToStep(direction);
            std::cout<<"t#############   "<< stepToString(step_Direction)<<std::endl;
        }
        else if (!wall_Sensor->isWall(direction)){
            min_Map[direction]+=1;
            step_Direction = convertDirToStep(direction);
            std::cout<<"the direction: "<< directionToString(direction)<< " is not wall"<<std::endl;
        }else{
            while(wall_Sensor->isWall(direction)){
                std::cout<<"the direction: &&&& "<< directionToString(direction)<< " is wall"<<std::endl;
                history.insert(direction);
                direction=changeDir(history);
                std::cout<<"changed the direction: "<< directionToString(direction)<<std::endl;
            }
            min_Map[direction]+=1;
            step_Direction = convertDirToStep(direction);
            std::cout<<"t#############   "<< stepToString(step_Direction)<<std::endl;

        }
    }
    //vacuum.move(step_Direction);
    
    if (!fromBack && step_Direction!=Step::Stay && step_Direction!=Step::Finish){
        std::cout<<"i am pushing to stack :   " << directionToString(direction)<<std::endl;
        Path.push(direction);
    }
    //bool x = vacuum.wallSensor(step_Direction);
    //std::cout << x << "," << step_Direction << std::endl;
    steps_Performed.push(step_Direction);
    curr_Steps++;
    std::cout<< "----------------------------------------------------------------the step is: " << stepToString(step_Direction)<<"   the direction is: "<<directionToString(direction) <<" the dirt is : " <<dirt_Sensor->dirtLevel() <<std::endl;
    changeCoordinates(step_Direction);
    std::cout<<"###########################################################################################################################################"<<std::endl;
    return step_Direction;
    /*
    std::shared_ptr<Node> frontNode= bfs_Queue;
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
    */
}

Direction MyAlgorithm::convertStepToDir(Step step_Direction){
    switch (step_Direction)
    {
    case Step::North:
        return Direction::North;
    case Step::West:
        return Direction::West;
    case Step::East:
        return Direction::East;
    case Step::South:
        return Direction::South;
    default:
        return Direction::South;
    }


}


void MyAlgorithm::changeCoordinates(Step step_Direction){
    switch (step_Direction)
    {
    case Step::North:
        curr_X--;
        break;
    case Step::West:
        curr_Y++;
        break;
    case Step::East:
        curr_Y--;
        break;
    case Step::South:
        curr_X++;
        break;
    default:
        break;
    }

}

std::string  MyAlgorithm::directionToString(Direction dir) { 
    switch (dir) { 
        case Direction::North: return "North"; 
        case Direction::East: return "East"; 
        case Direction::South: return "South"; 
        case Direction::West: return "West"; 
        default: return "Unknown";
    }
}

Step MyAlgorithm::backStep(){
    Direction direction=Path.top();
    std::cout<<directionToString(direction)<<std::endl;
    Path.pop();
    switch (direction) {
    case Direction::North:
        steps_Performed.push(Step::South);
        return Step::South;
    case Direction::South:
        steps_Performed.push(Step::North);
        return Step::North;
    case Direction::West:
        steps_Performed.push(Step::East);
        return Step::East;
    case Direction::East:
        steps_Performed.push(Step::West);
        return Step::West;
    default:
        //TODO: throw exception
        return Step::Finish;
    }
}

bool MyAlgorithm::checkVisited(Direction direction){
    switch (direction) {
    case Direction::North:
        return alreadyVisited(std::pair<int,int>(curr_X-1,curr_Y));
    case Direction::South:
        return alreadyVisited(std::pair<int,int>(curr_X+1,curr_Y));
    case Direction::West:
        return alreadyVisited(std::pair<int,int>(curr_X,curr_Y+1));
    case Direction::East:
        return alreadyVisited(std::pair<int,int>(curr_X,curr_Y-1));
    default:
        //TODO: throw exception
        return false;
    }

}

bool MyAlgorithm::alreadyVisited( const std::pair<int, int> keyToFind){ 
    auto it = visited.find(keyToFind);
    return it != visited.end(); 
}





std::string MyAlgorithm::stepToString(Step step){
    switch (step){
        case Step::Stay: return "s";
        case Step::North: return "N";
        case Step::East : return "E";
        case Step::South: return "S";
        case Step::West: return "W";
        case Step::Finish: return "F";
        default: return "Unknown";
    }
}
