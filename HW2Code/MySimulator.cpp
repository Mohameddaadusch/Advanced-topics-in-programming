#include "MySimulator.h"
#include <fstream>
#include <sstream>
#include <iostream>


#include "MySimulator.h"
#include "MyWallSensor.cpp"
#include "MyBatteryMeter.cpp"
#include "MyDirtSensor.cpp"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
MySimulator::MySimulator() : maxStepsAllowed(-1), maxBatterySteps(-1), rows(-1), cols(-1),dockX(-1) , dockY(-1) {}

// Read house layout from file
bool MySimulator::readHouseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;

    // Read house name / description
    if (std::getline(file, line)) {
        houseName = line;
    }

    // Read MaxSteps
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string dummy;
        if (!(iss >> dummy >> dummy >> maxStepsAllowed)) {
            std::cerr << "Error: Invalid format for MaxSteps" << std::endl;
            return false;
        }
    }

    // Read MaxBattery
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string dummy;
        if (!(iss >> dummy >> dummy >> maxBatterySteps)) {
            std::cerr << "Error: Invalid format for MaxBattery" << std::endl;
            return false;
        }
    }

    // Read Rows
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string dummy;
        if (!(iss >> dummy >> dummy >> rows)) {
            std::cerr << "Error: Invalid format for Rows" << std::endl;
            return false;
        }
    }

    // Read Cols
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string dummy;
        if (!(iss >> dummy >> dummy >> cols)) {
            std::cerr << "Error: Invalid format for Cols" << std::endl;
            return false;
        }
    }

    // Initialize the house matrix with the specified dimensions
    houseMap.resize(rows, std::vector<int>(cols, 0));

    // Read the house layout
    for (int i = 0; i < rows; ++i) {
        if (std::getline(file, line)) {
            for (int j = 0; j < cols; ++j) {
                if (j < static_cast<int>(line.length())) {
                    char ch = line[j];
                    if (ch == 'W') {
                        houseMap[i][j] = -1;
                    } else if (ch == ' ') {
                        houseMap[i][j] = 0;
                    }else if(ch == 'D'){
                        dockX=i;
                        dockY=j;
                        houseMap[i][j] = 0;

                    }
                }
            }
        }
    }
    surroundByWalls();

    file.close();
    return true;
}

// Print the house layout
void MySimulator::printHouse() const {
    std::cout << "House Name: " << houseName << std::endl;
    std::cout << "MaxSteps: " << maxStepsAllowed << std::endl;
    std::cout << "MaxBattery: " << maxBatterySteps << std::endl;
    std::cout << "Rows: " << rows << std::endl;
    std::cout << "Cols: " << cols << std::endl;
    std::cout << "House Layout:" << std::endl;

    for (const auto& row : houseMap) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}



// Set the algorithm for the simulator
void MySimulator::setAlgorithm(std::unique_ptr<AbstractAlgorithm> algo) {
    algorithm = std::move(algo);
    algo->setMaxSteps(maxStepsAllowed);
    MyWallSensor=
    algo->setWallsSensor()
}

// Run the simulation
void MySimulator::run() {
    if (!algorithm || !house) {
        std::cerr << "Error: Algorithm or house not set" << std::endl;
        return;
    }

    // Example run logic; you'll need to adjust based on your algorithm and requirements
    Node* root = house->getRoot();
    if (!root) {
        std::cerr << "Error: House root not found" << std::endl;
        return;
    }

    // Assuming your algorithm has an interface to start the simulation
    algorithm->setInitialNode(root);

    while (algorithm->hasNextStep()) {
        algorithm->nextStep();
    }
}



void MySimulator::surroundByWalls() {

    bool isSurrounded=true;
    int rows = houseMap.size();
    int cols = houseMap[0].size();
    // Add walls to the top and bottom
    for (int i = 0; i < cols; ++i) {
        if (houseMap[0][i] != -1) {
            isSurrounded=false;
            break;
        }
        if (houseMap[rows - 1][i] != -1) {
            isSurrounded=false;
            break;
        }
    }
    // Add walls to the left and right
    for (int i = 0; i < rows; ++i) {
        if (houseMap[i][0] != -1) {
            isSurrounded=false;
            break;
        }
        if (houseMap[i][cols - 1] != -1) {
            isSurrounded=false;
            break;
        }
    }

    if (isSurrounded==true)
    {
        return;
    }
    // Create a new matrix with additional rows and columns for the walls
    std::vector<std::vector<int>> newHouseMap(rows + 2, std::vector<int>(cols + 2, -1));

    // Copy the original matrix values to the center of the new matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            newHouseMap[i + 1][j + 1] = houseMap[i][j];
        }
    }

    // Update the houseMap to the new matrix with walls
    houseMap = newHouseMap;
    dockX+=1;
    dockY+=1;
    
}






