#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include "Node.h"
#include "House.h"
#include "Graph.h"
#include "Vacuum.h"
#include "MyAlgorithm.h" 
#include "abstract_algorithm.h" 
#include "MyWallSensor.cpp"
#include "MyDirtSensor.cpp"
#include "MyBatteryMeter.cpp"


class MySimulator {
private:
    std::string houseName;
    int dockX,dockY,maxBatterySteps,maxStepsAllowed, rows,cols;
    std::vector<std::vector<int>> houseMap;
    AbstractAlgorithm* algorithm=nullptr;
    House house;
    Vacuum vacuum;
    std::string fileName;

    //Sensors:
    MyWallSensor wall_Sensor ;
    MyDirtSensor dirt_Sensor;
    MyBatteryMeter battery_Meter;
    std::queue<Step> steps_Performed;
    std::string Status;


public:
    // Constructor
    MySimulator();

    // Read house layout from file
    bool readHouseFile(const std::string& filename);

    // Set the algorithm for the simulator
    void setAlgorithm(AbstractAlgorithm& algo);

    // Run the simulation
    void run();

    void printHouse() const;

    void surroundByWalls();
    void writeOutput(const std::string& outputFile);
    std::string stepToString(Step step);
    std::string removeSpaces(const std::string& input);


};

#endif // MYSIMULATOR_H



