#ifndef VACUUM_H
#define VACUUM_H

#include "../House/House.h"
#include "../common/enums.h"

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

#endif
