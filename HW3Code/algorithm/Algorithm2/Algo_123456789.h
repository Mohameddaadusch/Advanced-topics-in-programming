#ifndef ALGO_123456789_H
#define ALGO_123456789_H

#include "AbstractAlgorithm.h"

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

#endif // ALGO_123456789_H
