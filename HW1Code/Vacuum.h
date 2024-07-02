#ifndef Vacuum_H
#define Vacuum_H

#include "House.h"
#include "Direction.h"

class Vacuum{
    House& house;
    const float max_BatterySteps;
    const int max_Steps;
    int pos_X;
    int pos_Y;
    float curr_BatterySteps;
    int curr_Steps;

public:
    Vacuum(House& house, float maxBatterySteps, int maxSteps);
    
    void move(Direction direction);//move to direction and update battery and step values
    bool clean();
    bool isBatteryExhausted() const;
    bool reachedMaxSteps() const;
    bool isMissionComplete() const;
    int dirtSensor() const;
    bool wallSensor(Direction dir) const;
    float batterySensor() const;
    void update_StepsAndBattery();
    int getTotalDirt();
    bool atDockingStation() const;
    void charge();
    float getMaxBattery() const;
};

#endif
