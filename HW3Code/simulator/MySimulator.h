#ifndef MY_SIMULATOR_H
#define MY_SIMULATOR_H

#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <dlfcn.h>  // Include for dynamic loading

#include "../House/House.h"
#include "../vacuum/vacuum.h"
#include "../common/AbstractAlgorithm.h"
#include "../common/AlgorithmRegistrar.h"
#include "../score/score.h"
#include "../common/BatteryMeter.h"
#include "../common/DirtSensor.h"
#include "../common/WallSensor.h"
#include "../algorithm/Algorithm1/MyWallSensor.h"   // Include your custom sensor headers
#include "../algorithm/Algorithm1/MyDirtSensor.h"
#include "../algorithm/Algorithm1/MyBatteryMeter.h"


class MySimulator {
private:
    std::string houseName;
    int dockX,dockY,maxBatterySteps,maxStepsAllowed, rows,cols;
    std::vector<std::vector<int>> houseMap;
    AbstractAlgorithm* algorithm=nullptr;
    House house;
    Vacuum vacuum;
    std::string fileName;
    std::vector<void*> algorithmHandles;  // Store handles to the loaded libraries

    //Sensors:
    MyWallSensor wall_Sensor ;
    MyDirtSensor dirt_Sensor;
    MyBatteryMeter battery_Meter;
    std::queue<Step> steps_Performed;
    std::string Status;
    std::string algo_Name;

public:

    // Constructor
    MySimulator();

    // Destructor to close libraries
    //~MySimulator();

    // Read house layout from file
    bool readHouseFile(const std::string& filename);

    // Set the algorithm for the simulator
    void setAlgorithm(AbstractAlgorithm* algo, const std::string& algo_Name);

    // Run the simulation
    int run();

    void printHouse() const;
    void surroundByWalls();
    void writeOutput(const std::string& outputFile);
    std::string stepToString(Step step);
    std::string removeSpaces(const std::string& input);
    void writeErrorFile(const std::string& houseFilename, const std::string& errorMsg);



};

#endif