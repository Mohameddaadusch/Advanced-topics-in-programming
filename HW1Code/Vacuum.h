#ifndef Vacuum_H
#define Vacuum_H

#include "House.h"
#include "Direction.h"

class Vacuum{
    
    float curr_BatterySteps;
    const float max_BatterySteps;
    int curr_Steps;
    const int max_Steps;
public:
House& house;
int pos_X, pos_Y;
    Vacuum(House& house, int maxBatterySteps, int maxSteps);
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
    int getMaxBattery() const;

};

#endif
