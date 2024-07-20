#include "dirt_sensor.h"
#include <iostream>
#include "House.h"
#include "Vacuum.h"
#include "battery_meter.h"

class MyBatteryMeter : public BatteryMeter {
    const Vacuum& vacuum;
public:
    MyBatteryMeter::MyBatteryMeter(Vacuum& v):vacuum(v) {}

    std::size_t getBatteryState() const override {
        return vacuum.batterySensor();
    }
};




