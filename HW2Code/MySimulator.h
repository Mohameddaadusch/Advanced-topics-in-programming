#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H

#include <string>
#include <memory>
#include <vector>
#include "Node.h"
#include "House.h"
#include "Graph.h"
#include "abstract_algorithm.h" 

class MySimulator {
private:
    std::string houseName;
    int dockX,dockY,maxBatterySteps,maxStepsAllowed, rows,cols;
    std::vector<std::vector<int>> houseMap;
    std::unique_ptr<AbstractAlgorithm> algorithm;

public:
    // Constructor
    MySimulator();

    // Read house layout from file
    bool readHouseFile(const std::string& filename);

    // Set the algorithm for the simulator
    void setAlgorithm(std::unique_ptr<AbstractAlgorithm> algo);

    // Run the simulation
    void run();

    void printHouse() const;

    void surroundByWalls();
};

#endif // MYSIMULATOR_H



