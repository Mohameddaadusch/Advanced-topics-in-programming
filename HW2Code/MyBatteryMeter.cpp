#ifndef MYBATTERYMETER_H
#define MYBATTERYMETER_H

#include "dirt_sensor.h"
#include <iostream>
#include "House.h"
#include "Vacuum.h"
#include "battery_meter.h"

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

#endif




