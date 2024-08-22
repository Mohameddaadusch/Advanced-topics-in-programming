#include "MySimulator.h"

// Constructor
MySimulator::MySimulator() : dockX(-1) ,dockY(-1) , maxBatterySteps(-1) ,maxStepsAllowed(-1), rows(-1), 
                                cols(-1), wall_Sensor(vacuum) , dirt_Sensor(vacuum) , battery_Meter(vacuum) 
                                      ,houseMap(),house(), vacuum(), fileName(""), algo_Name(), Status()  {


    // Print the fields
    std::cout << "MySimulator Constructor" << std::endl;
    std::cout << "houseName: " << houseName << std::endl;
    std::cout << "dockX: " << dockX << std::endl;
    std::cout << "dockY: " << dockY << std::endl;
    std::cout << "maxBatterySteps: " << maxBatterySteps << std::endl;
    std::cout << "maxStepsAllowed: " << maxStepsAllowed << std::endl;
    std::cout << "rows: " << rows << std::endl;
    std::cout << "cols: " << cols << std::endl;
    std::cout << "houseMap: " << (houseMap.empty() ? "empty" : "initialized") << std::endl;
    std::cout << "algorithm: " << (algorithm ? "set" : "null") << std::endl;
    std::cout << "fileName: " << fileName << std::endl;
    std::cout << "Status: " << Status << std::endl;
    std::cout << "algo_Name: " << algo_Name << std::endl;
    std::cout << "steps_Performed size: " << steps_Performed.size() << std::endl;
}

// Destructor to close dynamically loaded libraries
/*
MySimulator::~MySimulator() {
    for (void* handle : algorithmHandles) {
        if (handle) {
            dlclose(handle);
        }
    }
}
*/

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
        writeErrorFile(filename, "Error: Could not open file");
        return false;
    }
    this->fileName = filename;

    std::string line;

    // Read house name / description
    if (std::getline(file, line)) {
        houseName = line;
        std::cout << houseName << std::endl;
    }

    // Read MaxSteps
    if (std::getline(file, line)) {
        line = removeSpaces(line);
        if (line.substr(0, 9).compare("MaxSteps=") == 0) {
            maxStepsAllowed = std::stoi(line.substr(9));
        } else {
            writeErrorFile(filename, "Error: Invalid format for MaxSteps");
            return false;
        }
    }

    // Read MaxBattery
    if (std::getline(file, line)) {
        line = removeSpaces(line);
        if (line.substr(0, 11).compare("MaxBattery=") == 0) {
            maxBatterySteps = std::stoi(line.substr(11));
        } else {
            writeErrorFile(filename, "Error: Invalid format for MaxBattery");
            return false;
        }
    }

    // Read Rows
    if (std::getline(file, line)) {
        line = removeSpaces(line);
        if (line.substr(0, 5).compare("Rows=") == 0) {
            rows = std::stoi(line.substr(5));
        } else {
            writeErrorFile(filename, "Error: Invalid format for Rows");
            return false;
        }
    }

    // Read Cols
    if (std::getline(file, line)) {
        line = removeSpaces(line);
        if (line.substr(0, 5).compare("Cols=") == 0) {
            cols = std::stoi(line.substr(5));
        } else {
            writeErrorFile(filename, "Error: Invalid format for Cols");
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
                            writeErrorFile(filename, "Error: There are more than 2 Docking Station");
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
                        else if (std::isdigit(ch)) {
                            int val = ch - '0';  // Convert the character to an integer
                            std::cerr << "i: " << i << "   j: " << j << "   char: " << ch << "   val is: " << val << std::endl;
                            houseMap[i][j] = val;
                        } else {
                            // If 'ch' is not a digit, throw an error or handle it accordingly
                            writeErrorFile(filename, "Error: Not valid chracter in the house matrix");
                            return false;
                        }
                    }
                }
            }
        }
    }
    if(counter == 0){
            writeErrorFile(filename, "Error: no Docking Statio exists");
            return false;
    }
    printHouse();
    //std::cerr << "E####################" << std::endl;
    //std::cerr << "#####################" << std::endl;
    surroundByWalls();

    file.close();
    printHouse();
    house.init(houseMap,dockX,dockY);

    vacuum.init(house,maxBatterySteps,maxStepsAllowed);

    return true;
}

void MySimulator::writeErrorFile(const std::string& houseFilename, const std::string& errorMsg) {
    std::string errorFilename = houseFilename.substr(0, houseFilename.find_last_of(".")) + ".error";
    std::ofstream errorFile(errorFilename);
    if (errorFile.is_open()) {
        errorFile << errorMsg << std::endl;
        errorFile.close();
    } else {
        std::cerr << "Could not open error file: " << errorFilename << std::endl;
    }
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
void MySimulator::setAlgorithm(AbstractAlgorithm* algo ,const std::string& algo_name) {
    algorithm= algo;
    algo_Name = algo_name;
    /*
        // Check if the algorithm is of type MyAlgorithm
        MyAlgorithm* myAlgo = dynamic_cast<MyAlgorithm*>(algorithm);
        if (myAlgo) {
            // Reset fields specific to MyAlgorithm to their initial states
            myAlgo->setFields(); // Example: a method to reset internal fields
        }
    */
    algorithm->setMaxSteps(maxStepsAllowed);
    algorithm->setWallsSensor(wall_Sensor);
    algorithm->setDirtSensor(dirt_Sensor);
    algorithm->setBatteryMeter(battery_Meter);
}


// Run the simulation
int MySimulator::run() {
    std::cout<<"RUNNING THE PROGRAM"<<std::endl;
    std::string outputName;
    Status = "WORKING";
    
    Step nextStep = algorithm->nextStep();
    std::cout<<stepToString(nextStep)<<std::endl;
    while(nextStep != Step::Finish && steps_Performed.size() < maxStepsAllowed ){
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
    
    outputName = houseName + '-' +algo_Name + ".txt";
    writeOutput(outputName);
    std::cout<<"IN DOCKING STATION? "<<vacuum.atDockingStation()<<"   , THE STATUS IS:   " << Status<<std::endl;
    std::cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   FINISHED THE ALGORITHM   $$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;

    int score = Score::calculateScore((Status == "DEAD" ? 1 : -1), (Status == "FINISHED" ? 1 : -1),
                                      vacuum.atDockingStation(), maxStepsAllowed, steps_Performed.size(), vacuum.getTotalDirt());
    return score;

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

    // Create the "OUTPUT" directory if it doesn't exist
    std::string outputDir = "OutPut";
    if (!std::filesystem::exists(outputDir)) {
        std::filesystem::create_directory(outputDir);
    }

    // Prepend the "OUTPUT/" path to the output file name
    std::string fullOutputPath = outputDir + "/" + outputFile;
    
    std::ofstream out(fullOutputPath);
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

    // IN DOCK? 
    out << "InDock = " << (vacuum.atDockingStation()? "TRUE":"FALSE") << "\n";

    // Status
    out << "Score = " << Score::calculateScore((Status == "DEAD"? 1:-1) , (Status == "FINISHED"? 1:-1), 
                                                vacuum.atDockingStation(),maxStepsAllowed,qSize,vacuum.getTotalDirt()) << "\n";

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


/*

//-------------------------------
// main.cpp
//-------------------------------
int main(int argc, char** argv) {
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <house_input_file>" << std::endl;
        return 1;
    }
    std::vector<std::string> houseFiles;
    std::string housePath = argv[1];
    //insert all files with suffix .house to houseFiles vector
    for (const auto& entry : std::filesystem::directory_iterator(housePath)) {
        if (entry.path().extension() == ".house") {
            houseFiles.push_back(entry.path().string());
            std::cout<<entry.path().string()<<std::endl;
        }
    }

    // dlopen
    for(const auto& algo: AlgorithmRegistrar::getAlgorithmRegistrar()) {
        std::cout << "BEFORE CREATING THE PROGRAM" << std::endl;
        auto algorithm = algo.create();
        std::cout << "SUCCEDED TO CREATING THE PROGRAM" << std::endl;
        //  std::cout << algo.name() << ": " << static_cast<int>(algorithm->nextStep()) << std::endl;
        //set up the simulator
        MySimulator simulator;

        //std::string outputName;

        for (const auto& house : houseFiles) {
            // TODO: get houseFilePath from command line
            if (simulator.readHouseFile(house)==false){
                std::cout << "Error reading the file" << std::endl;
                return 1;
            }
            simulator.setAlgorithm(*algorithm, algo.name());
            simulator.run();
            // Wait for 10 seconds before moving to the next algorithm
            std::cout << "Waiting for 10 seconds before the next algorithm..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }

    }
    AlgorithmRegistrar::getAlgorithmRegistrar().clear();
    // dlclose
}
*/
// Load the algorithms using dlopen
void register_libs(const char* libs_dir, std::vector<void*>& libs){     

    for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::path(libs_dir))) {

        if (entry.path().extension() == ".so") {
            void* lib_ptr = dlopen(entry.path().c_str(), RTLD_LAZY);
            if (!lib_ptr) {
                std::cerr << "Error loading algorithm: " << dlerror() << std::endl;
                continue;
            }
            libs.push_back(lib_ptr);
        }
    }
}

// Close all dynamically loaded libraries
void clear_libs(std::vector<void*>& libs) {
    for (void* lib : libs) {
        if (lib) {
            std::cout << "Closing library: " << lib << std::endl;
            if (dlclose(lib) != 0) {
                std::cerr << "Error closing library: " << dlerror() << std::endl;
            }
        }
    }
    std::cout << "Finished clearing libraries." << std::endl;
}



int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <house_input_directory> <algorithm_directory>" << std::endl;
        return 1;
    }

    int score = 0;
    std::vector<std::string> houseFiles;
    std::vector<std::string> algorithmNames;
    std::vector<std::vector<int>> scores; // To store scores for all algorithms
    std::vector<void*> algo_libs; // To store handles to the loaded libraries

    std::string housePath = argv[1];
    std::string algoPath = argv[2];

    // Insert all files with suffix .house to houseFiles vector
    for (const auto& entry : std::filesystem::directory_iterator(housePath)) {
        if (entry.path().extension() == ".house") {
            houseFiles.push_back(entry.path().string());
            std::cout << entry.path().string() << std::endl;
        }
    }

    register_libs(algoPath.c_str(), algo_libs);
    std::cout << "RUNNING ON : " << AlgorithmRegistrar::getAlgorithmRegistrar().count() << " algorithms. "<<std::endl;
    /*
    for(const auto& algo: AlgorithmRegistrar::getAlgorithmRegistrar()){
        auto algorithm = algo.create();
        //std::cout<<algo.name()<<": " << static_cast<int>(algorithm->nextStep())<<std::endl;
        std::cout<<algo.name()<<std::endl;

    }
    // Load the algorithms using dlopen
   
    for (const auto& entry : std::filesystem::directory_iterator(algoPath)) {
        if (entry.path().extension() == ".so") {
            void* handle = dlopen(entry.path().c_str(), RTLD_LAZY);
            if (!handle) {
                std::cerr << "Error loading algorithm: " << dlerror() << std::endl;
                continue;
            }
            algo_libs.push_back(handle);

            typedef AbstractAlgorithm* (*CreateAlgoFunc)();
            CreateAlgoFunc createAlgo = (CreateAlgoFunc) dlsym(handle, "create_algorithm");
            const char* dlsym_error = dlerror();
            if (dlsym_error) {
                std::cerr << "Error locating create_algorithm: " << dlsym_error << std::endl;
                dlclose(handle);
                algo_libs.pop_back();
                continue;
            }

            AlgorithmRegistrar::getAlgorithmRegistrar().registerAlgorithm(entry.path().stem().string(), [createAlgo]() {
                return std::unique_ptr<AbstractAlgorithm>(createAlgo());
            });
        }
    }
    */

    // Iterate through each registered algorithm
    for (const auto& algo : AlgorithmRegistrar::getAlgorithmRegistrar()) {
        std::cout << "BEFORE CREATING THE PROGRAM" << std::endl;

        std::vector<int> currentScores; // Store scores for the current algorithm
        algorithmNames.push_back(algo.name());

        // Loop through each house file
        for (auto it = houseFiles.begin(); it != houseFiles.end(); ) {
            MySimulator simulator;

            if (!simulator.readHouseFile(*it)) {
                std::cout << "Error reading the file " << *it << ". The file will be ignored." << std::endl;
                // Remove invalid house file from the list
                it = houseFiles.erase(it);
            } else {
                auto algorithm = algo.create();
                simulator.setAlgorithm(algorithm.release(), algo.name());
                score = simulator.run();
                std::cout << "The score is: " << score << std::endl;
                currentScores.push_back(score);

                ++it;
            }
        }
        
        // Store the scores for the current algorithm in the main scores vector
        scores.push_back(currentScores);
    }

    // Write the results to a CSV file
    std::ofstream csvFile("summary.csv");
    if (!csvFile.is_open()) {
        std::cerr << "Error: Could not create summary.csv" << std::endl;
        return 1;
    }
    
    // Write the header
    csvFile << "Algorithm/House";
    for (const auto& house : houseFiles) {
        std::string baseHouseName = std::filesystem::path(house).stem().string();
        csvFile << "," << baseHouseName;
    }
    csvFile << "\n";

    // Write the scores
    for (int i = 0; i < algorithmNames.size(); ++i) {
        csvFile << algorithmNames[i];
        for (const auto& score : scores[i]) {
            csvFile << "," << score;
        }
        csvFile << "\n";
    }

    csvFile.close();
    std::cout << "Summary written to summary.csv" << std::endl;

    // Close all dynamically loaded libraries
    std::cout<<"ENDING AND CLEARIRNG ALGORITHMS"<<std::endl;
    clear_libs(algo_libs);
    return 0;
}


