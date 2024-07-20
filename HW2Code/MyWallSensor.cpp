#include "wall_sensor.h"
#include <unordered_map>
#include <iostream>
#include "House.h"
#include "enums.h"
#include "Vacuum.h"

class MyWallSensor : public WallsSensor {
    House& house;
    Vacuum& vacuum;
    int pos_X;
    int pos_Y;

public:
    MyWallSensor::MyWallSensor(House& h , Vacuum& v): house(h), vacuum(v){
      //  dock_X=house.getDockX();
      //  dock_Y=house.getDockY();
    }
    // Override the pure virtual function from WallSensor
    /*
    void MyWallSensor:: setPosition(int x, int y){
        MyWallSensor::pos_X=x+dock_X;
        MyWallSensor::pos_Y=y+dock_Y;

    }
    */
    bool isWall(Direction direction) const override {
        switch (direction) { 
            case Direction::North:
                if ((house.isWall(pos_X-1,pos_Y)==true)){
                    return true;
                }
                return false;
            case Direction::South:
                if ((house.isWall(pos_X+1,pos_Y)==true)){
                    return true;
                }
                return false;
            case Direction::East:
                if (house.isWall(pos_X,pos_Y+1)==true){
                    return true;
                }
                return false;
            case Direction::West:
                if (house.isWall(pos_X,pos_Y-1)==true){
                    return true;
                }
                return false;
            default:
                //TODO: throw exception
                return false;
        }
    }
};




