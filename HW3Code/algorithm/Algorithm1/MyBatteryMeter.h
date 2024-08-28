#ifndef MY_BATTERY_METER_H
#define MY_BATTERY_METER_H
class MyBatteryMeter : public BatteryMeter {
    const Vacuum& vacuum;
public:
    MyBatteryMeter(Vacuum& v):vacuum(v) {
        //std::cout<<"in battery sensor constructor"<<std::endl;
    }

    std::size_t getBatteryState() const override {
        return vacuum.batterySensor();
    }
};
#endif
