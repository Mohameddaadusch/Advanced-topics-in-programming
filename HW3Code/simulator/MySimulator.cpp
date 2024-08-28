#include "MySimulator.h"

std::mutex consoleMutex;

// Constructor
MySimulator::MySimulator() : dockX(-1) ,dockY(-1) , maxBatterySteps(-1) ,maxStepsAllowed(-1), rows(-1), 
                                cols(-1) ,houseMap(),house(), vacuum(), fileName(""), algo_Name(), Status() , summaryOnly(false) 
                                , wall_Sensor(std::make_unique<MyWallSensor>(vacuum)), dirt_Sensor(std::make_unique<MyDirtSensor>(vacuum)),battery_Meter(std::make_unique<MyBatteryMeter>(vacuum)) {
    /*
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
    */
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

void MySimulator::setSummaryOnly(bool summary) {
    summaryOnly = summary;
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
        //std::cout << houseName << std::endl;
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

    //std::cout << "rows: "<< rows <<"   cols: "<< cols<< std::endl;

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
                            //std::cerr << "i: " << i << "   j: " << j << "   char: " << ch << "   val is: " << val << std::endl;
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
    house.init(houseName,houseMap,dockX,dockY);

    vacuum.init(house,maxBatterySteps,maxStepsAllowed);

    return true;
}

void MySimulator::writeErrorFile(const std::string& houseFilename, const std::string& errorMsg) {
    // Extract the base name of the house file (without the directory path)
    std::string baseFilename = std::filesystem::path(houseFilename).stem().string();
    
    // Create the error filename in the current directory
    std::string errorFilename = baseFilename + ".error";
    
    // Write the error message to the file in the current directory
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
            //std::cout << cell << " ";
        }
        //std::cout << std::endl;
    }
}


// Set the algorithm for the simulator
void MySimulator::setAlgorithm(std::unique_ptr<AbstractAlgorithm> algo ,const std::string& algo_name) {
    algorithm = std::move(algo);
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
    algorithm->setWallsSensor(*wall_Sensor);    // Dereference unique_ptr to pass raw pointer/reference
    algorithm->setDirtSensor(*dirt_Sensor);     
    algorithm->setBatteryMeter(*battery_Meter);
}


// Run the simulation
int MySimulator::run() {
    Status = "WORKING";
    Step nextStep = algorithm->nextStep();

    while (nextStep != Step::Finish && steps_Performed.size() < maxStepsAllowed) {
        steps_Performed.push(nextStep);

        if (nextStep == Step::Stay) {
            if (vacuum.atDockingStation()) {
                vacuum.charge();
            } else {
                vacuum.clean();
            }
        } else {
            vacuum.move(nextStep);
        }
        nextStep = algorithm->nextStep();
    }
    steps_Performed.push(nextStep);

    if (nextStep == Step::Finish && vacuum.atDockingStation()) {
        Status = "FINISHED";
    } else if (battery_Meter->getBatteryState() <= 0) {
        Status = "DEAD";
    } else {
        Status = "WORKING";
    }

    if (!summaryOnly) {
        std::string outputName = houseName + '-' + algo_Name + ".txt";
        writeOutput(outputName);
    }

    int score = this->getScore();
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
    out << "Score = " << this->getScore() << "\n";

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

int MySimulator::getScore(){
    std::queue<Step> queue = steps_Performed;
    int qSize = queue.size();
    int score=Score::calculateScore((Status == "DEAD"? true:false) , (Status == "FINISHED"? true:false), 
                                                vacuum.atDockingStation(),maxStepsAllowed,qSize,vacuum.getTotalDirt());
    if (Status == "FINISHED"){
        return score-1;   //excluding the Finish step
    }else{
        return score;
    }

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


// Load the algorithms using dlopen

void register_libs(const char* algo_path, std::vector<void*>& algo_libs) {
    for (const auto& entry : std::filesystem::directory_iterator(algo_path)) {
        if (entry.path().extension() == ".so") {
            try {
                // Load the shared library and store its handle in algo_libs
                void* libHandle = dlopen(entry.path().c_str(), RTLD_LAZY);
                if (!libHandle) {
                    throw std::runtime_error(dlerror());
                }
                algo_libs.push_back(libHandle);
            } catch (const std::exception& e) {
                std::string algoName = entry.path().stem().string(); // Extract algorithm name
                std::string errorFilename = algoName + ".error";
                std::ofstream errorFile(errorFilename);
                if (errorFile.is_open()) {
                    errorFile << "Error loading algorithm " << algoName << ": " << e.what() << std::endl;
                    errorFile.close();
                } else {
                    std::cerr << "Could not open error file: " << errorFilename << std::endl;
                }
            }
        }
    }
}

// Close all dynamically loaded libraries
void clear_libs(std::vector<void*>& libs) {
    for (void* lib : libs) {
        if (lib) {
            //std::cout << "Closing library: " << lib << std::endl;
            if (dlclose(lib) != 0) {
                std::cerr << "Error closing library: " << dlerror() << std::endl;
            }
        }
    }
    //std::cout << "Finished clearing libraries." << std::endl;
}


int MySimulator::calculateTimeout() const {
    return maxStepsAllowed * 1; 
}


void run_simulation_with_timeout(const std::string& house, const std::string& algo_name, 
                                 std::unique_ptr<AbstractAlgorithm> algorithm, int& score, bool summaryOnly) {
    MySimulator simulator;
    
    if (!simulator.readHouseFile(house)) {
        std::lock_guard<std::mutex> lock(consoleMutex);
        return;
    }
    
    simulator.setSummaryOnly(summaryOnly);
    simulator.setAlgorithm(std::move(algorithm), algo_name);
    
    try {
        int timeout = simulator.calculateTimeout();
        auto future = std::async(std::launch::async, [&simulator]() {
            return simulator.run();
        });
        
        if (future.wait_for(std::chrono::milliseconds(timeout)) == std::future_status::timeout) {
            int initialDirt = simulator.getVacuum().getTotalDirt();
            score = simulator.getMaxStepsAllowed() * 2 + initialDirt * 300 + 2000;
            std::cerr << "Timeout reached for house: " << house << " and algorithm: " << algo_name << std::endl;
        } else {
            std::lock_guard<std::mutex> lock(consoleMutex);
            score = future.get();
        }
    } catch (const std::exception& e) {
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::string errorFilename = algo_name + ".error";
        std::ofstream errorFile(errorFilename);
        if (errorFile.is_open()) {
            errorFile << "Error: " << e.what() << std::endl;
            errorFile.close();
        } else {
            std::cerr << "Could not open error file: " << errorFilename << std::endl;
        }
        score = -1;
    } catch (...) {
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::string errorFilename = algo_name + ".error";
        std::ofstream errorFile(errorFilename);
        if (errorFile.is_open()) {
            errorFile << "Unknown error occurred while running algorithm " << algo_name << std::endl;
            errorFile.close();
        } else {
            std::cerr << "Could not open error file: " << errorFilename << std::endl;
        }
        score = -1;
    }
}




int main(int argc, char** argv) {
    if (argc < 1 ) {
        std::cerr << "Error : no executable file given" << std::endl;
        return 1;
    }

    int numThreads = 10;
    bool summaryOnly = false;

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("-num_threads=") == 0) {
            numThreads = std::stoi(arg.substr(13));
        } else if (arg == "-summary_only") {
            summaryOnly = true;
        }
    }

    std::vector<std::string> houseFiles;
    std::vector<std::string> algorithmNames;
    std::vector<std::vector<int>> scores;
    std::vector<void*> algo_libs;

    std::string housePath = "."; // Default to current working directory
    std::string algoPath = ".";  // Default to current working directory

    for (int i = 1; i < argc; ++i) {
        std::string argument = argv[i];

        if (argument.find("-house_path=") == 0) {
            housePath = argument.substr(std::string("-house_path=").length());
        } else if (argument.find("-algo_path=") == 0) {
            algoPath = argument.substr(std::string("-algo_path=").length());
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(housePath)) {
        if (entry.path().extension() == ".house") {
            houseFiles.push_back(entry.path().string());
            //std::cout << entry.path().string() << std::endl;
        }
    }

    register_libs(algoPath.c_str(), algo_libs);

    scores.resize(AlgorithmRegistrar::getAlgorithmRegistrar().count(), std::vector<int>(houseFiles.size(), -1));

    int algorithmIndex = 0;
    for (const auto& algo : AlgorithmRegistrar::getAlgorithmRegistrar()) {
        algorithmNames.push_back(algo.name());

        int houseIndex = 0;
        std::vector<std::thread> threadPool;

        while (houseIndex < houseFiles.size()) {
            threadPool.clear();

            for (int t = 0; t < numThreads && houseIndex < houseFiles.size(); ++t, ++houseIndex) {
                auto algorithmClone = algo.create();
                threadPool.emplace_back(run_simulation_with_timeout, houseFiles[houseIndex], algo.name(), std::move(algorithmClone), std::ref(scores[algorithmIndex][houseIndex]), summaryOnly);
            }

            for (auto& thread : threadPool) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
        }

        ++algorithmIndex;
    }

    std::ofstream csvFile("summary.csv");
    if (!csvFile.is_open()) {
        std::cerr << "Error: Could not create summary.csv" << std::endl;
        return 1;
    }

    std::vector<std::string> validHouseFiles;
    for (int i = 0; i < houseFiles.size(); ++i) {
        bool valid = false;
        for (int j = 0; j < algorithmNames.size(); ++j) {
            if (scores[j][i] != -1) {
                valid = true;
                break;
            }
        }
        if (valid) {
            validHouseFiles.push_back(houseFiles[i]);
        }
    }

    // Writing to the summary.csv file
    csvFile << "Algorithm/House";
    for (const auto& house : validHouseFiles) {
        std::string baseHouseName = std::filesystem::path(house).stem().string();
        csvFile << "," << baseHouseName;
    }
    csvFile << "\n";

    for (int i = 0; i < algorithmNames.size(); ++i) {
        csvFile << algorithmNames[i];
        for (int j = 0; j < validHouseFiles.size(); ++j) {
            int houseIndex = std::distance(houseFiles.begin(), std::find(houseFiles.begin(), houseFiles.end(), validHouseFiles[j]));
            csvFile << "," << (scores[i][houseIndex] != -1 ? std::to_string(scores[i][houseIndex]) : "");
        }
        csvFile << "\n";
    }

    csvFile.close();
    //std::cout << "Summary written to summary.csv" << std::endl;

    AlgorithmRegistrar::getAlgorithmRegistrar().clear();
    clear_libs(algo_libs);
    std::cout << "The Algorithm Finished Running" << std::endl;

    return 0;
}



