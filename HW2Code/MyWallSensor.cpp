#ifndef MYWALLSENSOR_H
#define MYWALLSENSOR_H

#include "wall_sensor.h"
#include <unordered_map>
#include <iostream>
#include "House.h"
#include "enums.h"
#include "Vacuum.h"

class MyWallSensor : public WallsSensor {
    const Vacuum& vacuum;

public:
    MyWallSensor(Vacuum& vac): vacuum(vac){
    }

    bool isWall(Direction d) const override {
        return vacuum.wallSensor(d);
    }
};

#endif

