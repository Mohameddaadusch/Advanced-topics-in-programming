#ifndef MYSDIRTSENSOR_H
#define MYSDIRTSENSOR_H

#include "dirt_sensor.h"
#include <iostream>
#include "House.h"
#include "Vacuum.h"

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

#endif




