#include "dirt_sensor.h"
#include <iostream>
#include "House.h"
#include "Vacuum.h"

class MyDirtSensor : public DirtSensor {
    House& house;
    int pos_X;
    int pos_Y;
    int dock_X,dock_Y;

public:
    MyDirtSensor::MyDirtSensor(House& house): house(house) {
        dock_X=house.getDockX();
        dock_Y=house.getDockY();
    }
    // Override the pure virtual function from DirtSensor
    int dirtLevel() const override {
        return house.getDirtLevel(pos_X,pos_Y);
    }

    void setPosition(int x , int y){
        pos_X=dock_X+x;
        pos_Y=dock_Y+y;
    }
};




