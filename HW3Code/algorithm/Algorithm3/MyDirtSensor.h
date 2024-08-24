#ifndef MY_DIRT_SENSOR_H
#define MY_DIRT_SENSOR_H
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