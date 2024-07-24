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
MySimulator::MySimulator() : dockX(-1) ,dockY(-1) , maxBatterySteps(-1) ,maxStepsAllowed(-1), rows(-1), cols(-1), wall_Sensor(vacuum) , dirt_Sensor(vacuum) , battery_Meter(vacuum)  {}


std::string MySimulator::removeSpaces(const std::string& input) {
    std::string result;
    result.reserve(input.size()); // Reserve space to avoid multiple reallocations
    for (char c : input) {
        if (!std::isspace(c)) {
            result += c;
        }
    }
    return result;
}


// Read house layout from file
bool MySimulator::readHouseFile(const std::string& filename) {
    int counter = 0;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    this->fileName = filename;

    std::string line;

    // Read house name / description
    if (std::getline(file, line)) {
        houseName = line;
    }

    // Read MaxSteps
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        
        line = removeSpaces(line);
        if(line.substr(0,9).compare("MaxSteps=") == 0){
            maxStepsAllowed = std::stoi(line.substr(9));
        }
        else{
            std::cerr << "Error: Invalid format for MaxSteps newwwwwww" << std::endl;
            return false;
        }
    }

    // Read MaxBattery
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        line = removeSpaces(line);
        if(line.substr(0,11).compare("MaxBattery=") == 0){
            maxBatterySteps = std::stoi(line.substr(11));
        }
        else{
            std::cerr << "Error: Invalid format for MaxBattery newwwwwww" << std::endl;
            return false;
        }
    }

    // Read Rows
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        
        line = removeSpaces(line);
        if(line.substr(0,5).compare("Rows=") == 0){
            rows = std::stoi(line.substr(5));
        }
        else{
            std::cerr << "Error: Invalid format for rows newwwwwww" << std::endl;
            return false;
        }
    }

    // Read Cols
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        line = removeSpaces(line);
        if(line.substr(0,5).compare("Cols=") == 0){
            cols = std::stoi(line.substr(5));
        }
        else{
            std::cerr << "Error: Invalid format for cols newwwwwww" << std::endl;
            return false;
        }
    }

    std::cout << "rows: "<< rows <<"   cols: "<< cols<< std::endl;

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
                        counter ++;
                        if(counter >=2){
                            std::cerr << "Error: there are more than one Docking Station" << std::endl;
                            return false;
                        }
                        dockX=i;
                        dockY=j;
                        houseMap[i][j] = 0;

                    }
                    else{
                        if (ch=='\r'){
                            continue;
                        }
                        int val=ch-'0';
                        std::cerr << "i: "<< i <<"   j: "<< j<< "   char : "<< ch<< " val is :" <<val << std::endl;
                        houseMap[i][j] = val;
                    }
                }
            }
        }
    }
    if(counter == 0){
        std::cerr << "Error: put a Docking Station in valid position" << std::endl;


        return false;
    }
    printHouse();
                    std::cerr << "E####################" << std::endl;
        std::cerr << "#####################" << std::endl;
    surroundByWalls();

    file.close();
    printHouse();
    house.init(houseMap,dockX,dockY);

    vacuum.init(house,maxBatterySteps,maxStepsAllowed);

    return true;
}


// Print the house layout
void MySimulator::printHouse() const {
    for (const auto& row : houseMap) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}


// Set the algorithm for the simulator
void MySimulator::setAlgorithm(AbstractAlgorithm& algo) {
    algorithm=&algo;
    algorithm->setMaxSteps(maxStepsAllowed);
    algorithm->setWallsSensor(wall_Sensor);
    algorithm->setDirtSensor(dirt_Sensor);
    algorithm->setBatteryMeter(battery_Meter);
}


// Run the simulation
void MySimulator::run() {
    std::string outputName;
    Status = "WORKING";
    
    Step nextStep = algorithm->nextStep();
    std::cout<<stepToString(nextStep)<<std::endl;
    while(nextStep != Step::Finish){
        steps_Performed.push(nextStep);

        if (nextStep==Step::Stay){
            if (vacuum.atDockingStation() ){
                vacuum.charge();
            }
            else{
                vacuum.clean();
            }

        }
        else{
            vacuum.move(nextStep);
        }
        nextStep = algorithm->nextStep();
    }
    steps_Performed.push(nextStep);

    if(battery_Meter.getBatteryState() <= 0){Status = "DEAD";}
    if(nextStep == Step::Finish && vacuum.atDockingStation()){Status = "FINISHED";}
    else{Status = "WORKING";}
    
    outputName = "output_" + this->fileName;
    writeOutput(outputName);

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


void MySimulator::writeOutput(const std::string& outputFile) {
    
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "Error: Cannot open file " << outputFile << std::endl;
        return;
    }

    std::queue<Step> queue = steps_Performed;
    int qSize = queue.size();


    // Write total number of steps performed
    out << "NumSteps = " << qSize -1 << "\n";
    Step step;
    
    // Write amount of dirt left in the house
    out << "DirtLeft = " << vacuum.getTotalDirt() << "\n";

    // Status
    out << "Status = " << Status << "\n";

    // Write steps performed by the vacuum cleaner
    out << "Steps:\n";
    while (!queue.empty()) {
        step = queue.front();
        queue.pop();
        out << stepToString(step);
    }
    out << "\n";

    out.close();
}


std::string MySimulator::stepToString(Step step){
    switch (step){
        case Step::Stay: return "s";
        case Step::North: return "N";
        case Step::East : return "E";
        case Step::South: return "S";
        case Step::West: return "W";
        case Step::Finish: return "F";
        default: return "Unknown";
    }
}


// getting command line arguments for the house file
int main(int argc, char** argv) {

    MySimulator simulator;

    std::string outputName;
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <house_input_file>" << std::endl;
        return 1;
    }
    std::string houseFilePath = argv[1];
    // TODO: get houseFilePath from command line
    if (simulator.readHouseFile(houseFilePath)==false){
        std::cout << "Error reading the file" << std::endl;
        return 1;
    }
    MyAlgorithm algo;
    simulator.setAlgorithm(algo);
    simulator.run();
}





