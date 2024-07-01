#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <sstream>


Simulator::Simulator(){}

void Simulator::writeOutput(const std::string& outputFile, Algorithm algorithm, Vacuum vacuum, bool res) {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "Error: Cannot open file " << outputFile << std::endl;
        return;
        // Write steps performed by the vacuum cleaner
        out << "Steps performed by the vacuum cleaner:\n";
        // You need to replace this with your actual stepsPerformed data
    }
    
    std::queue<Direction> queue = algorithm.getStepsQueue();
    Direction direction;
    int qSize = queue.size();
    while (queue.size()>0)
    {
        direction = queue.front();
        queue.pop();
        if(queue.size()==0){
            out <<  direction <<"\n" ;
        }
        else{
            out << direction << ", ";
        }
        
    }
  
    // Write total number of steps performed
    out << "Total number of steps performed: " << qSize << "\n";

    // Write amount of dirt left in the house
    out << "Amount of dirt left in the house: " << vacuum.getTotalDirt() << "\n";

    // Write indication of whether the vacuum cleaner is dead
    out << "Is the vacuum cleaner dead (battery exhausted): " << vacuum.isBatteryExhausted() << "\n";

    // Write indication of whether the mission is succeeded
    out << "Is the mission succeeded: " << res << "\n";

    out.close();
}

void Simulator::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        exit(1); // Handle this more gracefully in production code
    }

    std::string line;
    int currentLine = 0;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        if (currentLine == 0) {
            char comma;
            // Read docking station coordinates from the first line
            ss >> dockX >> comma >> dockY;
        } else if (currentLine == 1) {
            // Read max battery steps from the second line
            ss >> maxBatterySteps;
        } else if (currentLine == 2) {
            // Read max steps allowed from the third line
            ss >> maxStepsAllowed;
        } else {
            // Read the house matrix from the fourth line onwards
            std::vector<int> row;
            int value;
            while (ss >> value) {
                row.push_back(value);
            }
            houseMap.push_back(row);
        }
        ++currentLine;
    }

    // Ensure the house is surrounded by walls
    surroundByWalls();

    file.close();
}

void Simulator::surroundByWalls() {

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

int Simulator::main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <house_input_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    Simulator::loadFromFile(filename);
    std::cout << dockX << std::endl;
    std::cout << dockY << std::endl;
    printHouse();

    House house(houseMap,dockX,dockY);

    // Create a Vacuum and Algorithm object and run the cleaning process
    std::cout << maxBatterySteps << std::endl;
    std::cout << maxStepsAllowed << std::endl;
    Vacuum vacuum(house,maxBatterySteps,maxStepsAllowed);
    Algorithm algorithm(vacuum);
    /* Implement the cleaning process using your algorithm
    while (!vacuum.isMissionComplete() && !vacuum.isBatteryDead()) {
        algorithm.decideNextMove();
    }

    // Output results
    vacuum.printResults();
    */
   printf( "################################################################3 \n");
   printf( "STARTING THE ALGORITHM \n");
   printf( "################################################################3 \n");
    bool res = algorithm.cleanAlgorithm();
    std::cout <<  res << std::endl;
    writeOutput("output.txt",algorithm,vacuum ,res);

    return res == true ? 1 : 0;
}


void Simulator::printHouse() const {
    for (const auto& row : houseMap) {
        for (int cell : row) {
            if (cell == -1) {
                std::cout << 'W'; // Wall
            } else if (cell == -2) {
                std::cout << ' '; // Out of bound
            } else {
                std::cout << cell; // Dirt level
            }
        }
        std::cout << std::endl;
    }
}


int main(int argc,char* argv[]){
    Simulator simulator;
    printf ("%d" ,simulator.main(argc,argv));
    return 1;
}