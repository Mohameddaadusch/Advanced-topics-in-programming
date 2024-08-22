#include "vacuum.h"
#include <cassert>

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
