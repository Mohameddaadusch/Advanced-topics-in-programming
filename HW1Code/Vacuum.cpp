#include "Vacuum.h"
#include "Direction.h"
#include <exception>
#include <cassert>
Vacuum::Vacuum(House& house, int maxBatterySteps, int maxSteps)
    : house(house), max_BatterySteps(maxBatterySteps), max_Steps(maxSteps), pos_X(house.getDockX())
    , pos_Y(house.getDockY()), curr_BatterySteps(maxBatterySteps), curr_Steps(0) {}

//return true if the move was successful, else return false
void Vacuum::move(Direction direction) {
    switch (direction) {
        case Direction::STAY:
            if (atDockingStation()==true){
                Vacuum::curr_Steps+=1;
            }
            else {
                Vacuum::update_StepsAndBattery();
            }
            return;
        case Direction::UP:
            Vacuum::update_StepsAndBattery();
            pos_X-=1;
            return;
        case Direction::DOWN:
            Vacuum::update_StepsAndBattery();
            pos_X+=1;
            return;
        case Direction::RIGHT:
            Vacuum::update_StepsAndBattery();
            pos_Y+=1;
            return;
        case Direction::LEFT:
            Vacuum::update_StepsAndBattery();
            pos_Y-=1;
            return;
        default:
            //TODO: throw exception
            return;
    }
}

void Vacuum::update_StepsAndBattery(){
    Vacuum::curr_BatterySteps-=1;   
    Vacuum::curr_Steps+=1;
}


// Implement cleaning logic , return false if the battery was exhausted or we reached the maximum steps, else return true
bool Vacuum::clean() {
    int dirt=house.getDirtLevel(pos_X,pos_Y);
    assert(dirt>0);
    house.setDirt(pos_X,pos_Y);
    //Vacuum::update_StepsAndBattery();
    if (isBatteryExhausted() || reachedMaxSteps()){
        return false;
    }
    return true;
}

bool Vacuum::isBatteryExhausted() const {
    return (batterySensor()<= 0);
}

int Vacuum::getMaxBattery() const {
    return Vacuum::max_BatterySteps;
}

bool Vacuum::reachedMaxSteps() const{
    
    return (Vacuum::curr_Steps>=Vacuum::max_Steps);
}
// Implement logic to check if mission is complete
bool Vacuum::isMissionComplete() const {
    if((house.getTotalDirt()==0) & ((pos_X == house.getDockX()) && (pos_Y == house.getDockY())==true)){
            return true;
        }
    return false;  
}

bool Vacuum::atDockingStation() const {
    return (pos_X == house.getDockX()) && (pos_Y == house.getDockY());
}

void Vacuum::charge() {
    if (atDockingStation()) {
        curr_BatterySteps += (max_BatterySteps / 20);
        if (curr_BatterySteps > max_BatterySteps) {
            curr_BatterySteps = max_BatterySteps;
        }
    }
}    

int Vacuum::dirtSensor() const{
    return house.getDirtLevel(pos_X,pos_Y);
}

bool Vacuum::wallSensor(Direction direction) const{
    std::cout<< "Direction is :"<< direction<<"(" <<pos_X<<","<<pos_Y<<")"<<std::endl;
    switch (direction) { 
        case Direction::UP:
            if ((house.isWall(pos_X-1,pos_Y)==true) || (house.isOutOfBound(pos_X-1,pos_Y)==true)){
                return true;
            }
            return false;
        case Direction::DOWN:
            if ((house.isWall(pos_X+1,pos_Y)==true) || (house.isOutOfBound(pos_X+1,pos_Y)==true)){
                return true;
            }
            return false;
        case Direction::RIGHT:
            if ((house.isWall(pos_X,pos_Y+1)==true) || (house.isOutOfBound(pos_X,pos_Y+1)==true)){
                return true;
            }
            return false;
        case Direction::LEFT:
            if ((house.isWall(pos_X,pos_Y-1)==true) || (house.isOutOfBound(pos_X,pos_Y-1)==true)){
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
    return house.getTotalDirt();
}

