#ifndef MY_WALL_SENSOR_H
#define MY_WALL_SENSOR_H
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