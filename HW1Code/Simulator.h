#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "House.h"
#include "Vacuum.h"
#include "Algorithm.h"

class Simulator {
public:
    Simulator();
    void writeOutput(const std::string& outputFile, Algorithm alg , Vacuum vacuum,bool res);
    void surroundByWalls();
    void loadFromFile(const std::string& filename);
    int main(int argc, char* argv[]);
    void printHouse() const;
private:
    //House house;
    //Vacuum vacuum;
    //Algorithm algorithm;
    int dockX,dockY,maxBatterySteps,maxStepsAllowed;
    std::vector<std::vector<int>> houseMap;

};

#endif
