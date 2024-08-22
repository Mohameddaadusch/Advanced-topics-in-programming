#include <filesystem>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <queue>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <queue>
#include <map>
#include <stdio.h>
#include <unordered_set>
#include <random>
#include <memory>
#include <list>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include <thread>
#include <chrono>


enum class Direction { North, East, South, West };
enum class Step { North, East, South, West, Stay, Finish };

class WallsSensor {
public:
	virtual ~WallsSensor() {}
	virtual bool isWall(Direction d) const = 0;
};

class DirtSensor {
public:
	virtual ~DirtSensor() {}
	virtual int dirtLevel() const = 0;
};

class BatteryMeter {
public:
	virtual ~BatteryMeter() {}
	virtual std::size_t getBatteryState() const = 0;
};

class AbstractAlgorithm {
public:
	virtual ~AbstractAlgorithm() {}
	virtual void setMaxSteps(std::size_t maxSteps) = 0;
	virtual void setWallsSensor(const WallsSensor&) = 0;
	virtual void setDirtSensor(const DirtSensor&) = 0;
	virtual void setBatteryMeter(const BatteryMeter&) = 0;
	virtual Step nextStep() = 0;
};

//-------------------------------
// common/AlgorithmRegistrar.h
//-------------------------------
using AlgorithmFactory = std::function<std::unique_ptr<AbstractAlgorithm>()>;

class AlgorithmRegistrar {
    class AlgorithmFactoryPair {
        std::string name_;
        AlgorithmFactory algorithmFactory_;
    public:
        AlgorithmFactoryPair(const std::string& name, AlgorithmFactory algorithmFactory)
            : name_(name), algorithmFactory_(std::move(algorithmFactory)) {}
        
        // NOTE: API is guaranteed, actual implementation may change
        const std::string& name() const { return name_; }
        std::unique_ptr<AbstractAlgorithm> create() const { return algorithmFactory_(); }
    };

    std::vector<AlgorithmFactoryPair> algorithms;
    static AlgorithmRegistrar registrar;
public:
    // NOTE: API is guaranteed, actual implementation may change
    static AlgorithmRegistrar& getAlgorithmRegistrar();

    void registerAlgorithm(const std::string& name, AlgorithmFactory algorithmFactory) {
        algorithms.emplace_back(name, std::move(algorithmFactory));
    }
    
    auto begin() const { return algorithms.begin(); }
    auto end() const { return algorithms.end(); }
    std::size_t count() const { return algorithms.size(); }
    void clear() { algorithms.clear(); }
};

//-----------------------------------
// simulator/AlgorithmRegistrar.cpp
//-----------------------------------
AlgorithmRegistrar AlgorithmRegistrar::registrar;

AlgorithmRegistrar& AlgorithmRegistrar::getAlgorithmRegistrar() { return registrar; }

//------------------------------------
// algorithm/AlgorithmRegistration.h
//------------------------------------
struct AlgorithmRegistration {
    AlgorithmRegistration(const std::string& name, AlgorithmFactory algorithmFactory) {
        AlgorithmRegistrar::getAlgorithmRegistrar().registerAlgorithm(name, std::move(algorithmFactory));
    }
};

#define REGISTER_ALGORITHM(ALGO) AlgorithmRegistration \
   _##ALGO(#ALGO, []{return std::make_unique<ALGO>();})


//-------------------------------
// algorithm/Algo_123456789.h
//-------------------------------
class Algo_123456789: public AbstractAlgorithm {
public:
	void setMaxSteps(std::size_t maxSteps) override {}
	void setWallsSensor(const WallsSensor&) override {}
	void setDirtSensor(const DirtSensor&) override {}
	void setBatteryMeter(const BatteryMeter&) override {}
	Step nextStep() override {
        return Step::North;	    
	}
};

//-------------------------------
// algorithm/Algo_123456789.cpp
//-------------------------------
REGISTER_ALGORITHM(Algo_123456789);


//-------------------------------
// MYAlgorithm
//-------------------------------


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

MyAlgorithm::MyAlgorithm(){
    //std::shared_ptr<Node> dockingStation = std::make_shared<Node>();
    //house_Graph= std::make_shared<Graph>(dockingStation);
    //bfs_Queue.push(0);
    //curr_Value = 0;
    visited[std::pair<int,int>(0,0)]=0;
    curr_X=0;
    curr_Y=0;
}

/*
void MyAlgorithm::setFields() {
    // Clear all the containers
    while (!Path.empty()) Path.pop();
    while (!bfs_Queue.empty()) bfs_Queue.pop();
    while (!steps_Performed.empty()) steps_Performed.pop();

    // Reset other fields to default values
    max_Steps = 0;
    curr_Steps = 0;
    visited.clear();
    curr_X = 0;
    curr_Y = 0;
    maxBattery = 0.0f;

    // Reset maps and vectors
    min_Map = {
        {Direction::East, 0},
        {Direction::North, 0},
        {Direction::West, 0},
        {Direction::South, 0}
    };
}
*/

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

    if(curr_Steps >= max_Steps && curr_X == 0 && curr_Y == 0){
        std::cout<<"finiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiish" << std::endl;

        step_Direction = Step::Finish;
        curr_Steps--;
    }
    else if ((Path.size()==0) && (battery_Meter->getBatteryState() < maxBattery)){
        std::cout<<"charging (3)  " <<std::endl;
        step_Direction = Step::Stay;
    }
    else if(battery_Meter->getBatteryState() <= Path.size() +1 || (max_Steps-curr_Steps -1) <= (int)Path.size() ){
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

REGISTER_ALGORITHM(MyAlgorithm);





//-------------------------------
// house.h
//-------------------------------

class House {
    std::vector<std::vector<int>> house_Matrix;
    int dock_X, dock_Y;
    int total_dirt;
public:
    House();
    void init(const std::vector<std::vector<int>>& HouseMatrix, int x, int y);
    void printHouse() const;
    bool isWall(int x, int y) const;
    int getDirtLevel(int x, int y) const;
    void setDirt(int x, int y);
    int getDockX() const;
    int getDockY() const;
    int getHouseMap() const;
    int getTotalDirt() const;
    
};

//-------------------------------
// house.cpp
//-------------------------------

House::House(){}

void House::init(const std::vector<std::vector<int>>& HouseM, int x, int y) {
    house_Matrix=HouseM;
    dock_X = x;
    dock_Y = y;
    int rows= house_Matrix.size();
    int cols=house_Matrix[0].size();
    if(house_Matrix[x][y] > 0){
        house_Matrix[x][y] = 0;
    }
    if (x < 0 || y < 0 || x >= static_cast<int>(house_Matrix.size()) || y >= static_cast<int>(house_Matrix[0].size()) || house_Matrix[x][y] < 0 ) {
        throw std::invalid_argument("Invalid docking station coordinates/value. please try again:");
    }
    total_dirt=0;
    for (int i=0; i<rows ;i++){
            if(static_cast<int>(house_Matrix[i].size()) != cols){
                throw std::invalid_argument("Invalid matrix , the matrix not (mxn). please change yuour matrix:");
            }
        for (int j=0;j<cols ; j++){
            if(house_Matrix[i][j]>0){
                if(house_Matrix[x][y] > 9 || house_Matrix[x][y] < -1){
                    throw std::invalid_argument("Invalid house block value. please change yuour matrix with values from -1 to 9:");
                }
                total_dirt+=house_Matrix[i][j];
            }
        }
    }
}

int House::getTotalDirt() const{
    return House::total_dirt;
}
/*

void House::printHouse() const {
    // Print the house layout for debugging
}
*/

// Return if (x, y) is a wall (-1: is wall, else the value is the dirt)
bool House::isWall(int x, int y) const {
    return (house_Matrix[x][y] == -1);
}
    


// Return the dirt level at (x, y) - a value between 1-9 or 0 (if the point is clean) or 
//-1 if the point is wall
//-2 if the point is out of bound
int House::getDirtLevel(int x, int y) const {
    assert(house_Matrix[x][y]>=0 && house_Matrix[x][y]<=9 ); // check if the value in point is correct
    return house_Matrix[x][y];
}

// Decrease the dirt level at (x, y)
void House::setDirt(int x, int y) {
    house_Matrix[x][y]-=1;
    House::total_dirt-=1;
}

int House::getDockX() const {
    return dock_X;
}

int House::getDockY() const {
    return dock_Y;
}

void House::printHouse() const {
    for (const auto& row : house_Matrix) {
        for (int cell : row) {
            if (cell == -1) {
                std::cout << 'W'; // Wall
            } else if (cell == -2) {
                std::cout << ' '; // Out of bound
            } else {
                std::cout << cell; // Dirt level
            }
        }
        std::cout << std::endl;
    }
}

//-------------------------------
// vacuum.h
//-------------------------------

class Vacuum{
    House* house=nullptr;
    int max_Steps;
    int curr_Steps;
    int pos_X;
    int pos_Y;
    float curr_BatterySteps;
    float max_BatterySteps;
    

public:
    Vacuum();
    void init(House& house, float maxBatterySteps, int maxSteps);
    
    void move(Step direction);//move to direction and update battery and step values
    bool clean();
    bool isBatteryExhausted() const;
    bool reachedMaxSteps() const;
    bool isMissionComplete() const;
    int dirtSensor() const;
    bool wallSensor(Direction dir) const;
    float batterySensor() const;
    void update_Battery();
    int getTotalDirt();
    bool atDockingStation() const;
    void charge();
    float getMaxBattery() const;
    void setMaxSteps(std::size_t maxSteps);
};


//-------------------------------
// vacuum.cpp
//-------------------------------

Vacuum::Vacuum(){}

void Vacuum::init(House& house, float maxBatterySteps, int maxSteps){
        this->house=&house;
        this->max_BatterySteps=maxBatterySteps;
        this->max_Steps=maxSteps;
        this->pos_X=house.getDockX();
        this->pos_Y=house.getDockY();
        this->curr_BatterySteps=maxBatterySteps;
        this->curr_Steps=0;
    }

//return true if the move was successful, else return false
void Vacuum::move(Step direction) {
    switch (direction) {
        case Step::Stay:
            if (atDockingStation()==true){
                Vacuum::curr_Steps+=1;
            }
            else {
                Vacuum::update_Battery();
            }
            return;
        case Step::North:
            Vacuum::update_Battery();
            pos_X-=1;
            return;
        case Step::South:
            Vacuum::update_Battery();
            pos_X+=1;
            return;
        case Step::West:
            Vacuum::update_Battery();
            pos_Y+=1;
            return;
        case Step::East:
            Vacuum::update_Battery();
            pos_Y-=1;
            return;
        default:
            //TODO: throw exception
            return;
    }
}

void Vacuum::update_Battery(){
    Vacuum::curr_BatterySteps-=1;   
    //Vacuum::curr_Steps+=1;
}



// Implement cleaning logic , return false if the battery was exhausted or we reached the maximum steps, else return true
bool Vacuum::clean() {
    int dirt=house->getDirtLevel(pos_X,pos_Y);
    assert(dirt>0);
    house->setDirt(pos_X,pos_Y);
    Vacuum::update_Battery();

    if (isBatteryExhausted() || reachedMaxSteps()){
        return false;
    }
    return true;
}

bool Vacuum::isBatteryExhausted() const {
    return (batterySensor()<= 0);
}

float Vacuum::getMaxBattery() const {
    return Vacuum::max_BatterySteps;
}

bool Vacuum::reachedMaxSteps() const{
    
    return (Vacuum::curr_Steps>=Vacuum::max_Steps);
}
// Implement logic to check if mission is complete
bool Vacuum::isMissionComplete() const {
    if((house->getTotalDirt()==0) & ((pos_X == house->getDockX()) && (pos_Y == house->getDockY())==true)){
            return true;
        }
    return false;  
}

bool Vacuum::atDockingStation() const {
    return (pos_X == house->getDockX()) && (pos_Y == house->getDockY());
}

void Vacuum::charge() {
        curr_BatterySteps += (max_BatterySteps / 20);
        if (curr_BatterySteps > max_BatterySteps) {
            curr_BatterySteps = max_BatterySteps;
        }
}    

int Vacuum::dirtSensor() const{
    return house->getDirtLevel(pos_X,pos_Y);
}

bool Vacuum::wallSensor(Direction direction) const{
    switch (direction) { 
        case Direction::North:
            if ((house->isWall(pos_X-1,pos_Y)==true)){
                return true;
            }
            return false;
        case Direction::South:
            if ((house->isWall(pos_X+1,pos_Y)==true)){
                return true;
            }
            return false;
        case Direction::West:
            if (house->isWall(pos_X,pos_Y+1)==true){
                return true;
            }
            return false;
        case Direction::East:
            if (house->isWall(pos_X,pos_Y-1)==true){
                return true;
            }
            return false;
        default:
            //TODO: throw exception
            return false;
    }
}

float Vacuum::batterySensor() const{
    return curr_BatterySteps;
}
int Vacuum::getTotalDirt(){
    return house->getTotalDirt();
}


//-------------------------------
// socre.h
//-------------------------------

// #ifndef SCORE_H
// #define SCORE_H
// #include <cstddef> // for std::size_t
class Score {
public:
    static int calculateScore(bool isDead, bool isFinished, bool inDock, std::size_t maxSteps, std::size_t numSteps, int dirtLeft);
};
//#endif // SCORE_H


//-------------------------------
// socre.cpp
//-------------------------------

//#include "score.h"
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


//-------------------------------
// Sensors
//-------------------------------

class MyBatteryMeter : public BatteryMeter {
    const Vacuum& vacuum;
public:
    MyBatteryMeter(Vacuum& v):vacuum(v) {
        std::cout<<"in battery sensor constructor"<<std::endl;
    }

    std::size_t getBatteryState() const override {
        return vacuum.batterySensor();
    }
};

class MyDirtSensor : public DirtSensor {
    const Vacuum& vacuum;

public:
    MyDirtSensor(Vacuum& v): vacuum(v) {
    }
    // Override the pure virtual function from DirtSensor
    int dirtLevel() const override {
        return vacuum.dirtSensor();
    }

};

class MyWallSensor : public WallsSensor {
    const Vacuum& vacuum;

public:
    MyWallSensor(Vacuum& vac): vacuum(vac){
    }

    bool isWall(Direction d) const override {
        return vacuum.wallSensor(d);
    }
};


//-------------------------------
// simulator.h
//-------------------------------


class MySimulator {
private:
    std::string houseName;
    int dockX,dockY,maxBatterySteps,maxStepsAllowed, rows,cols;
    std::vector<std::vector<int>> houseMap;
    AbstractAlgorithm* algorithm=nullptr;
    House house;
    Vacuum vacuum;
    std::string fileName;

    //Sensors:
    MyWallSensor wall_Sensor ;
    MyDirtSensor dirt_Sensor;
    MyBatteryMeter battery_Meter;
    std::queue<Step> steps_Performed;
    std::string Status;
    std::string algo_Name;


public:
    // Constructor
    MySimulator();

    // Read house layout from file
    bool readHouseFile(const std::string& filename);

    // Set the algorithm for the simulator
    void setAlgorithm(AbstractAlgorithm& algo, const std::string& algo_Name);

    // Run the simulation
    int run();

    void printHouse() const;

    void surroundByWalls();
    void writeOutput(const std::string& outputFile);
    std::string stepToString(Step step);
    std::string removeSpaces(const std::string& input);
    void writeErrorFile(const std::string& houseFilename, const std::string& errorMsg);



};


//-------------------------------
// simulator.cpp
//-------------------------------


// Constructor
MySimulator::MySimulator() : dockX(-1) ,dockY(-1) , maxBatterySteps(-1) ,maxStepsAllowed(-1), rows(-1), 
                                cols(-1), wall_Sensor(vacuum) , dirt_Sensor(vacuum) , battery_Meter(vacuum) 
                                      ,houseMap(),house(), vacuum(), fileName(""), algo_Name(), Status()  {


    // Print the fields
    std::cout << "MySimulator Constructor" << std::endl;
    std::cout << "houseName: " << houseName << std::endl;
    std::cout << "dockX: " << dockX << std::endl;
    std::cout << "dockY: " << dockY << std::endl;
    std::cout << "maxBatterySteps: " << maxBatterySteps << std::endl;
    std::cout << "maxStepsAllowed: " << maxStepsAllowed << std::endl;
    std::cout << "rows: " << rows << std::endl;
    std::cout << "cols: " << cols << std::endl;
    std::cout << "houseMap: " << (houseMap.empty() ? "empty" : "initialized") << std::endl;
    std::cout << "algorithm: " << (algorithm ? "set" : "null") << std::endl;
    std::cout << "fileName: " << fileName << std::endl;
    std::cout << "Status: " << Status << std::endl;
    std::cout << "algo_Name: " << algo_Name << std::endl;
    std::cout << "steps_Performed size: " << steps_Performed.size() << std::endl;
}


std::string MySimulator::removeSpaces(const std::string& input) {
    std::string result;
    result.reserve(input.size()); // Reserve space to avoid multiple reallocations
    for (char c : input) {
        if (!std::isspace(c)) {
            result += c;
        }
    }
    return result;
}


// Read house layout from file
bool MySimulator::readHouseFile(const std::string& filename) {
    int counter = 0;
    std::ifstream file(filename);
    if (!file.is_open()) {
        writeErrorFile(filename, "Error: Could not open file");
        return false;
    }
    this->fileName = filename;

    std::string line;

    // Read house name / description
    if (std::getline(file, line)) {
        houseName = line;
        std::cout << houseName << std::endl;
    }

    // Read MaxSteps
    if (std::getline(file, line)) {
        line = removeSpaces(line);
        if (line.substr(0, 9).compare("MaxSteps=") == 0) {
            maxStepsAllowed = std::stoi(line.substr(9));
        } else {
            writeErrorFile(filename, "Error: Invalid format for MaxSteps");
            return false;
        }
    }

    // Read MaxBattery
    if (std::getline(file, line)) {
        line = removeSpaces(line);
        if (line.substr(0, 11).compare("MaxBattery=") == 0) {
            maxBatterySteps = std::stoi(line.substr(11));
        } else {
            writeErrorFile(filename, "Error: Invalid format for MaxBattery");
            return false;
        }
    }

    // Read Rows
    if (std::getline(file, line)) {
        line = removeSpaces(line);
        if (line.substr(0, 5).compare("Rows=") == 0) {
            rows = std::stoi(line.substr(5));
        } else {
            writeErrorFile(filename, "Error: Invalid format for Rows");
            return false;
        }
    }

    // Read Cols
    if (std::getline(file, line)) {
        line = removeSpaces(line);
        if (line.substr(0, 5).compare("Cols=") == 0) {
            cols = std::stoi(line.substr(5));
        } else {
            writeErrorFile(filename, "Error: Invalid format for Cols");
            return false;
        }
    }

    std::cout << "rows: "<< rows <<"   cols: "<< cols<< std::endl;

    // Initialize the house matrix with the specified dimensions
    houseMap.resize(rows, std::vector<int>(cols, 0));

    // Read the house layout
    for (int i = 0; i < rows; ++i) {
        if (std::getline(file, line)) {
            for (int j = 0; j < cols; ++j) {
                if (j < static_cast<int>(line.length())) {
                    char ch = line[j];
                    if (ch == 'W') {
                        houseMap[i][j] = -1;
                    } else if (ch == ' ') {
                        houseMap[i][j] = 0;
                    }else if(ch == 'D'){
                        counter ++;
                        if(counter >=2){
                            writeErrorFile(filename, "Error: There are more than 2 Docking Station");
                            return false;
                        }
                        dockX=i;
                        dockY=j;
                        houseMap[i][j] = 0;

                    }
                    else{
                        if (ch=='\r'){
                            continue;
                        }
                        else if (std::isdigit(ch)) {
                            int val = ch - '0';  // Convert the character to an integer
                            std::cerr << "i: " << i << "   j: " << j << "   char: " << ch << "   val is: " << val << std::endl;
                            houseMap[i][j] = val;
                        } else {
                            // If 'ch' is not a digit, throw an error or handle it accordingly
                            writeErrorFile(filename, "Error: Not valid chracter in the house matrix");
                            return false;
                        }
                    }
                }
            }
        }
    }
    if(counter == 0){
            writeErrorFile(filename, "Error: no Docking Statio exists");
            return false;
    }
    printHouse();
    //std::cerr << "E####################" << std::endl;
    //std::cerr << "#####################" << std::endl;
    surroundByWalls();

    file.close();
    printHouse();
    house.init(houseMap,dockX,dockY);

    vacuum.init(house,maxBatterySteps,maxStepsAllowed);

    return true;
}

void MySimulator::writeErrorFile(const std::string& houseFilename, const std::string& errorMsg) {
    std::string errorFilename = houseFilename.substr(0, houseFilename.find_last_of(".")) + ".error";
    std::ofstream errorFile(errorFilename);
    if (errorFile.is_open()) {
        errorFile << errorMsg << std::endl;
        errorFile.close();
    } else {
        std::cerr << "Could not open error file: " << errorFilename << std::endl;
    }
}


// Print the house layout
void MySimulator::printHouse() const {
    for (const auto& row : houseMap) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}


// Set the algorithm for the simulator
void MySimulator::setAlgorithm(AbstractAlgorithm& algo ,const std::string& algo_name) {
    algorithm=&algo;
    algo_Name = algo_name;
    /*
        // Check if the algorithm is of type MyAlgorithm
        MyAlgorithm* myAlgo = dynamic_cast<MyAlgorithm*>(algorithm);
        if (myAlgo) {
            // Reset fields specific to MyAlgorithm to their initial states
            myAlgo->setFields(); // Example: a method to reset internal fields
        }
    */
    algorithm->setMaxSteps(maxStepsAllowed);
    algorithm->setWallsSensor(wall_Sensor);
    algorithm->setDirtSensor(dirt_Sensor);
    algorithm->setBatteryMeter(battery_Meter);
}


// Run the simulation
int MySimulator::run() {
    std::cout<<"RUNNING THE PROGRAM"<<std::endl;
    std::string outputName;
    Status = "WORKING";
    
    Step nextStep = algorithm->nextStep();
    std::cout<<stepToString(nextStep)<<std::endl;
    while(nextStep != Step::Finish && steps_Performed.size() < maxStepsAllowed ){
        steps_Performed.push(nextStep);

        if (nextStep==Step::Stay){
            if (vacuum.atDockingStation() ){
                vacuum.charge();
            }
            else{
                vacuum.clean();
            }

        }
        else{
            vacuum.move(nextStep);
        }
        nextStep = algorithm->nextStep();
    }
    steps_Performed.push(nextStep);

    if(battery_Meter.getBatteryState() <= 0){Status = "DEAD";}
    if(nextStep == Step::Finish && vacuum.atDockingStation()){Status = "FINISHED";}
    else{Status = "WORKING";}
    
    outputName = houseName + '-' +algo_Name + ".txt";
    writeOutput(outputName);
    std::cout<<"IN DOCKING STATION? "<<vacuum.atDockingStation()<<"   , THE STATUS IS:   " << Status<<std::endl;
    std::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   FINISHED THE ALGORITHM   $$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;

    int score = Score::calculateScore((Status == "DEAD" ? 1 : -1), (Status == "FINISHED" ? 1 : -1),
                                      vacuum.atDockingStation(), maxStepsAllowed, steps_Performed.size(), vacuum.getTotalDirt());
    return score;

}


void MySimulator::surroundByWalls() {

    bool isSurrounded=true;
    int rows = houseMap.size();
    int cols = houseMap[0].size();
    // Add walls to the top and bottom
    for (int i = 0; i < cols; ++i) {
        if (houseMap[0][i] != -1) {
            isSurrounded=false;
            break;
        }
        if (houseMap[rows - 1][i] != -1) {
            isSurrounded=false;
            break;
        }
    }
    // Add walls to the left and right
    for (int i = 0; i < rows; ++i) {
        if (houseMap[i][0] != -1) {
            isSurrounded=false;
            break;
        }
        if (houseMap[i][cols - 1] != -1) {
            isSurrounded=false;
            break;
        }
    }

    if (isSurrounded==true)
    {
        return;
    }
    // Create a new matrix with additional rows and columns for the walls
    std::vector<std::vector<int>> newHouseMap(rows + 2, std::vector<int>(cols + 2, -1));

    // Copy the original matrix values to the center of the new matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            newHouseMap[i + 1][j + 1] = houseMap[i][j];
        }
    }

    // Update the houseMap to the new matrix with walls
    houseMap = newHouseMap;
    dockX+=1;
    dockY+=1;
    
}


void MySimulator::writeOutput(const std::string& outputFile) {

    // Create the "OUTPUT" directory if it doesn't exist
    std::string outputDir = "OutPut";
    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directory(outputDir);
    }

    // Prepend the "OUTPUT/" path to the output file name
    std::string fullOutputPath = outputDir + "/" + outputFile;
    
    std::ofstream out(fullOutputPath);
    if (!out.is_open()) {
        std::cerr << "Error: Cannot open file " << outputFile << std::endl;
        return;
    }

    std::queue<Step> queue = steps_Performed;
    int qSize = queue.size();


    // Write total number of steps performed
    out << "NumSteps = " << qSize -1 << "\n";
    Step step;
    
    // Write amount of dirt left in the house
    out << "DirtLeft = " << vacuum.getTotalDirt() << "\n";

    // Status
    out << "Status = " << Status << "\n";

    // IN DOCK? 
    out << "InDock = " << (vacuum.atDockingStation()? "TRUE":"FALSE") << "\n";

    // Status
    out << "Score = " << Score::calculateScore((Status == "DEAD"? 1:-1) , (Status == "FINISHED"? 1:-1), 
                                                vacuum.atDockingStation(),maxStepsAllowed,qSize,vacuum.getTotalDirt()) << "\n";

    // Write steps performed by the vacuum cleaner
    out << "Steps:\n";
    while (!queue.empty()) {
        step = queue.front();
        queue.pop();
        out << stepToString(step);
    }
    out << "\n";

    out.close();
}


std::string MySimulator::stepToString(Step step){
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


/*

//-------------------------------
// main.cpp
//-------------------------------
int main(int argc, char** argv) {
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <house_input_file>" << std::endl;
        return 1;
    }
    std::vector<std::string> houseFiles;
    std::string housePath = argv[1];
    //insert all files with suffix .house to houseFiles vector
    for (const auto& entry : std::filesystem::directory_iterator(housePath)) {
        if (entry.path().extension() == ".house") {
            houseFiles.push_back(entry.path().string());
            std::cout<<entry.path().string()<<std::endl;
        }
    }

    // dlopen
    for(const auto& algo: AlgorithmRegistrar::getAlgorithmRegistrar()) {
        std::cout << "BEFORE CREATING THE PROGRAM" << std::endl;
        auto algorithm = algo.create();
        std::cout << "SUCCEDED TO CREATING THE PROGRAM" << std::endl;
        //  std::cout << algo.name() << ": " << static_cast<int>(algorithm->nextStep()) << std::endl;
        //set up the simulator
        MySimulator simulator;

        //std::string outputName;

        for (const auto& house : houseFiles) {
            // TODO: get houseFilePath from command line
            if (simulator.readHouseFile(house)==false){
                std::cout << "Error reading the file" << std::endl;
                return 1;
            }
            simulator.setAlgorithm(*algorithm, algo.name());
            simulator.run();
            // Wait for 10 seconds before moving to the next algorithm
            std::cout << "Waiting for 10 seconds before the next algorithm..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }

    }
    AlgorithmRegistrar::getAlgorithmRegistrar().clear();
    // dlclose
}
*/
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <house_input_file>" << std::endl;
        return 1;
    }
    
    int score = 0;
    std::vector<std::string> houseFiles;
    std::vector<std::string> algorithmNames;
    std::vector<std::vector<int>> scores; // To store scores for all algorithms

    std::string housePath = argv[1];
    // Insert all files with suffix .house to houseFiles vector
    for (const auto& entry : std::filesystem::directory_iterator(housePath)) {
        if (entry.path().extension() == ".house") {
            houseFiles.push_back(entry.path().string());
            std::cout << entry.path().string() << std::endl;
        }
    }

    // dlopen
    for (const auto& algo : AlgorithmRegistrar::getAlgorithmRegistrar()) {
        std::cout << "BEFORE CREATING THE PROGRAM" << std::endl;

        //auto algorithm = algo.create();
        std::cout << "SUCCEEDED IN CREATING THE PROGRAM" << std::endl;

        std::vector<int> currentScores; // Store scores for the current algorithm
        algorithmNames.push_back(algo.name());

        // Loop through each house file
        for (auto it = houseFiles.begin(); it != houseFiles.end(); ) {
            auto algorithm = algo.create();
            MySimulator simulator;

            if (!simulator.readHouseFile(*it)) {
                std::cout << "Error reading the file " << *it << ". The file will be ignored." << std::endl;
                // Remove invalid house file from the list
                it = houseFiles.erase(it);
            } else {
                simulator.setAlgorithm(*algorithm, algo.name());
                score = simulator.run();
                std::cout << "The score is: " << score << std::endl;
                currentScores.push_back(score);

                // Wait for 5 seconds before moving to the next algorithm
                std::cout << "Waiting for 5 seconds before the next algorithm..." << std::endl;
                //std::this_thread::sleep_for(std::chrono::seconds(5));

                ++it;
            }
        }
        
        // Store the scores for the current algorithm in the main scores vector
        scores.push_back(currentScores);
    }
    AlgorithmRegistrar::getAlgorithmRegistrar().clear();
    // dlclose

    // Write the results to a CSV file
    std::ofstream csvFile("summary.csv");
    if (!csvFile.is_open()) {
        std::cerr << "Error: Could not create summary.csv" << std::endl;
        return 1;
    }
    
    // Write the header
    std::cout << "Writing header..." << std::endl;
    csvFile << "Algorithm/House";
    for (const auto& house : houseFiles) {
        std::string baseHouseName = std::filesystem::path(house).stem().string();
        csvFile << "," << baseHouseName;
        std::cout << "House: " << house << std::endl;  // Debug print for each house
    }
    csvFile << "\n";

    // Write the scores
    std::cout << "Writing scores..." << "  ,  Scores size: " << scores.size() << "  ,  algorithm size: " << algorithmNames.size() << "  ,  house size: " << houseFiles.size() << std::endl;
    for (int i = 0; i < algorithmNames.size(); ++i) {
        // Debug print for algorithm name
        std::cout << "Algorithm: " << algorithmNames[i] << std::endl;
        csvFile << algorithmNames[i];
        
        if (i >= scores.size()) {
            std::cerr << "Error: Index " << i << " is out of bounds for scores vector (size: " << scores.size() << ")" << std::endl;
            continue;
        }

        std::cout << "Scores size for algorithm " << algorithmNames[i] << ": " << scores[i].size() << std::endl;
        
        for (const auto& score : scores[i]) {
            csvFile << "," << score;
            std::cout << "Score: " << score << std::endl;  // Debug print for each score
        }
        
        csvFile << "\n";
    }

    csvFile.close();
    std::cout << "Summary written to summary.csv" << std::endl;

    return 0;
}



