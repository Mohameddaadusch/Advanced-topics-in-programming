#include "MyAlgorithm.h"
#include <iostream>
#include <random>

MyAlgorithm::MyAlgorithm(){
    //std::shared_ptr<Node> dockingStation = std::make_shared<Node>();
    //house_Graph= std::make_shared<Graph>(dockingStation);
    //bfs_Queue.push(0);
    //curr_Value = 0;
    //visited[std::pair<int,int>(0,0)]=0;
    unexplored_Stack.push(std::pair<int,int>(0,0));
    //cleaned_Set.insert(std::pair<int,int>(0,0));
    curr_X=0;
    curr_Y=0;
}

/*
void MyAlgorithm::setFields() {
    // Clear all the containers
    while (!Path.empty()) Path.pop();
    while (!bfs_Queue.empty()) bfs_Queue.pop();
    while (!steps_Performed.empty()) steps_Performed.pop();

    // Reset other fields to default values
    max_Steps = 0;
    curr_Steps = 0;
    visited.clear();
    curr_X = 0;
    curr_Y = 0;
    maxBattery = 0.0f;

    // Reset maps and vectors
    min_Map = {
        {Direction::East, 0},
        {Direction::North, 0},
        {Direction::West, 0},
        {Direction::South, 0}
    };
}
*/

void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    this->max_Steps=maxSteps;
    this->curr_Steps=0;
}

void MyAlgorithm::setWallsSensor(const WallsSensor& walls_Sensor ){
    std::cout<<"initializing wallsensor"<<std::endl;
    this->wall_Sensor = &walls_Sensor;
    
}

void MyAlgorithm::setDirtSensor(const DirtSensor& Dirt_Sensor ){
    this->dirt_Sensor = &Dirt_Sensor;
}

void MyAlgorithm::setBatteryMeter(const BatteryMeter& Battery_Meter){
    this->battery_Meter = &Battery_Meter;
    this->maxBattery=Battery_Meter.getBatteryState();
}

Direction MyAlgorithm::getMinDir() {
    int min = std::min({min_Map[Direction::West], min_Map[Direction::North], min_Map[Direction::East], min_Map[Direction::South]});
    if (min_Map [Direction::West] == min){
        return Direction::West;
    }else if(min_Map[Direction::North] == min){
        return Direction::North;
    }else if(min_Map[Direction::East] == min){
        return Direction::East;
    }else{
        return Direction::South;
    }
}

Direction MyAlgorithm::changeDir(std::unordered_set<Direction> history){
    std::map<Direction,int> newMap=min_Map;
    for (const Direction& dir: history){
        newMap.erase(dir);
    }
    int min=std::numeric_limits<int>::max();
    Direction res;
    for(const auto& key : directions_Order){
        if (newMap.find(key)!=newMap.end() && newMap[key]<min){
            min=newMap[key];
            res=key;
        }
        
    }
    
    return res;
}

Step MyAlgorithm::convertDirToStep(Direction dir){
    if(dir == Direction::East){
        return Step::East;
    }
    else if(dir == Direction::North){
        return Step::North;
    }
    else if(dir == Direction::South){
        return Step::South;
    }
    else{
        return Step::West;
    }


}

Direction MyAlgorithm::intToDirection(int value) {
    switch (value) {
        case 1:
            return Direction::West;
        case 2:
            return Direction::North;
        case 3:
            return Direction::East;
        case 4: 
            return Direction::South;
        default:
            throw std::invalid_argument("Invalid integer value for Direction");
            break;
    }
}

Step  MyAlgorithm::nextStep(){
    std::cout<<"###################################################################################################################################"<<std::endl;
    std::cout<<"NEWWWW ALGOOOO DFS doing next step" <<std::endl;
    std::cout<<"step number :  " << curr_Steps+1 << std::endl;
    Step step_Direction=Step::West;
    bool fromBack=false;
    Direction direction;
    std::cout<<"the battery is @@@@@@@@@@@@@@@@@@@    "<< battery_Meter->getBatteryState() << " ,the path size is@@@@@@@@@@@  "<< Path.size()<<std::endl;
    std::cout<<"i am in point : curr x cur y  ------------------------------------------ :  " << curr_X<< ","<< curr_Y << std::endl;
    std::cout<<"the dirt is : " <<dirt_Sensor->dirtLevel() <<std::endl;
    std::cout<<"the stack :  " << std::endl;
    printStack(unexplored_Stack);
    std::cout<<"current steps !!!!!!!!!!!! :  " << curr_Steps<< ", max steps !!!!!!!!!!!!!!!!!!!!!!!"<< max_Steps << std::endl;
    //std::cout<<"return to last point: " << returning_To_LastPoint << std::endl;
    if(curr_Steps >= max_Steps && curr_X == 0 && curr_Y == 0){
        std::cout<<"finiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiish" << std::endl;
        step_Direction = Step::Finish;
        curr_Steps--;
    }
    else if ((Path.size()==0) && (battery_Meter->getBatteryState() < maxBattery)){
        std::cout<<"charging (3)  " <<std::endl;
        //unexplored_Set.clear();
        //unexplored_Set.insert(std::pair<int,int>(0,0));
        step_Direction = Step::Stay;
    }
    /*
    else if(battery_Meter->getBatteryState() >= maxBattery && path_To_LastPoint.size()>0){
        std::cout<<"returning to last point" << std::endl;
        step_Direction=returnToLastPoint();
        path_To_LastPoint.pop();
    }*/
    else if(battery_Meter->getBatteryState() <= Path.size() +1 || (max_Steps-curr_Steps -1) <= (int)Path.size() ){
        std::cout<<"backstep (1) ************************************************************************************** " <<std::endl;
        /*
        if(!unexplored_Stack.empty()){
            auto next_Point = unexplored_Stack.top();
            if (dirt_Sensor->dirtLevel() == 0 && curr_X == next_Point.first && curr_Y == next_Point.second){
                visited[next_Point]=0;
                //unexplored_Set.erase(next_Point);
                unexplored_Stack.pop();
            }
        }
        */
        step_Direction = backStep();
        direction = convertStepToDir(step_Direction);
        path_To_LastPoint.push(direction);
        fromBack=true;
    }
    else if(wall_Sensor->isWall(Direction::North) && wall_Sensor->isWall(Direction::South) && wall_Sensor->isWall(Direction::West) && wall_Sensor->isWall(Direction::East)){
        std::cout<<"4 walls arround (2) " <<std::endl;
        step_Direction=Step::Stay;
    }
    else{
        std::cout<<"doing normal step *************************************************************** " <<std::endl;
        if (!unexplored_Stack.empty()) {
            auto next_Point = unexplored_Stack.top();
            while (findPairInSet(cleaned_Set,next_Point)){
                std::cout<<"the next point is already cleaned, change it***************** " <<std::endl;
                unexplored_Stack.pop();
                next_Point=unexplored_Stack.top();
            }
            std::cout<<"123 : "<<(curr_X!=next_Point.first)<< (curr_Y!=next_Point.second) <<(path_To_LastPoint.size()>0 )<< std::endl;
            if((curr_X!=next_Point.first || curr_Y!=next_Point.second) && path_To_LastPoint.size()>0){
                std::cout<<"returning to last point newwww"<< std::endl;
                step_Direction=returnToLastPoint();
            }
            else if (curr_X == next_Point.first && curr_Y == next_Point.second) {
                std::cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQ reached the point in top of the stack" <<std::endl;
                visited[next_Point] = dirt_Sensor->dirtLevel();
                if (dirt_Sensor->dirtLevel() > 0) {
                    std::cout<<"XXXXXXXXXXXXXXXXXXX Cleaning " <<std::endl;
                    step_Direction = Step::Stay;
                    visited[next_Point]--;
                }else{
                    cleaned_Set.insert(next_Point);
                    //unexplored_Set.erase(next_Point);
                    unexplored_Stack.pop();
                    int new_points=discoverUnexploredPoints();
                    if (new_points > 0) {
                        next_Point=unexplored_Stack.top();
                        std::cout<<"XXXXXXXXXXXXXXXXXXX finished discovering " <<std::endl;
                        if (curr_X < next_Point.first && !wall_Sensor->isWall(Direction::South)) {
                            step_Direction = Step::South;
                        } else if (curr_X > next_Point.first && !wall_Sensor->isWall(Direction::North)) {
                            step_Direction = Step::North;
                        } else if (curr_Y < next_Point.second && !wall_Sensor->isWall(Direction::East)) {
                            step_Direction = Step::East;
                        } else if (curr_Y > next_Point.second && !wall_Sensor->isWall(Direction::West)) {
                            step_Direction = Step::West;
                        }
                    }else{
                        std::cout<<"in the second case, every direction is or wall or visited, so we are going to choose randomly" << std::endl;
                        std::random_device rd;
                        std::mt19937 mt(rd()); // Mersenne Twister random number generator seeded with random_device
                        std::uniform_int_distribution<int> dist(1, 4); // Distribution for integers between 1 and 4 (inclusive)
                        int randomNumber = dist(mt);
                        direction= intToDirection(randomNumber);
                        std::cout<<"the first random direction: &&&& "<< directionToString(direction)<<std::endl;
                        while(wall_Sensor->isWall(direction)){
                            std::cout<<"the random direction: &&&& "<< directionToString(direction)<< " is wall"<<std::endl;
                            randomNumber = dist(mt);
                            direction= intToDirection(randomNumber);
                            std::cout<<"changed the direction: "<< directionToString(direction)<<std::endl;
                        }

                        step_Direction = convertDirToStep(direction);

                    }
                    

                }
            } else {
                // didn't reach next_Point yet
                std::cout<<"QQQQQQQQQQQQQQQQQQQQQQQQQQ did not reach the point in top of the stack" <<std::endl;
                if (curr_X < next_Point.first && !wall_Sensor->isWall(Direction::South)) {
                    step_Direction = Step::South;
                } else if (curr_X > next_Point.first && !wall_Sensor->isWall(Direction::North)) {
                    step_Direction = Step::North;
                } else if (curr_Y < next_Point.second && !wall_Sensor->isWall(Direction::East)) {
                    step_Direction = Step::East;
                } else if (curr_Y > next_Point.second && !wall_Sensor->isWall(Direction::West)) {
                    step_Direction = Step::West;
                }
            }
        }else{
            step_Direction = Step::Finish;
            curr_Steps--;
        }
    }

    //vacuum.move(step_Direction);
    if (!fromBack && step_Direction!=Step::Stay && step_Direction!=Step::Finish){
        direction=convertStepToDir(step_Direction);
        std::cout<<"i am pushing to stack :   " << directionToString(direction)<<std::endl;
        Path.push(direction);
    }
    //bool x = vacuum.wallSensor(step_Direction);
    //std::cout << x << "," << step_Direction << std::endl;
    steps_Performed.push(step_Direction);
    curr_Steps++;
    std::cout<< "----------------------------------------------------------------the step is: " << stepToString(step_Direction)<<",,, the direction is: "<<directionToString(direction) <<std::endl;
    changeCoordinates(step_Direction);
    std::cout<<"###################################################################################################################################"<<std::endl;
    return step_Direction;
}

bool MyAlgorithm::findPairInSet(const std::set<std::pair<int, int>>& mySet, const std::pair<int, int>& target) {
    std::cout << "in findpairinset "<< std::endl;
    auto it = mySet.find(target); // Search for the pair in the set
    return it != mySet.end();     // Return true if found, false otherwise
}

// Function to print the contents of a stack of pairs
void MyAlgorithm::printStack(const std::stack<std::pair<int, int>>& s) {
    // Create a temporary stack to hold the elements in the correct order
    std::stack<std::pair<int, int>> tempStack = s;
    std::vector<std::pair<int, int>> elements;

    // Pop elements from the temporary stack and store them in a vector
    while (!tempStack.empty()) {
        elements.push_back(tempStack.top());
        tempStack.pop();
    }

    // Print the elements in the vector in reverse order (bottom of the stack first)
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        std::cout << "(" << it->first << ", " << it->second << ") ";
    }

    std::cout << std::endl;
}

int MyAlgorithm::discoverUnexploredPoints() {
    // Check all directions around the current position
    //std::cout << "in discover "<< std::endl;
    int res=0;
    for (const auto& dir : {Direction::South, Direction::East, Direction::North, Direction::West}) {
        if (!wall_Sensor->isWall(dir) && !checkVisited(dir) ) {
            auto next_Point = getCoordinatesInDirection(dir);
            //std::cout << "point.x:  " << next_Point.first << "  point.y: "<< next_Point.second << std::endl;
            unexplored_Stack.push(next_Point);
            //unexplored_Set.insert(next_Point);
            res++;
        }
    }
    //std::cout << "returning from discover "<< std::endl;
    return res;
}

std::pair<int, int> MyAlgorithm::getCoordinatesInDirection(Direction dir) {
    switch (dir) {
        case Direction::North: return {curr_X - 1, curr_Y};
        case Direction::South: return {curr_X + 1, curr_Y};
        case Direction::East: return {curr_X, curr_Y + 1};
        case Direction::West: return {curr_X, curr_Y - 1};
        default: return {curr_X, curr_Y};
    }
}


Direction MyAlgorithm::convertStepToDir(Step step_Direction){
    switch (step_Direction)
    {
    case Step::North:
        return Direction::North;
    case Step::West:
        return Direction::West;
    case Step::East:
        return Direction::East;
    case Step::South:
        return Direction::South;
    default:
        return Direction::South;
    }


}


void MyAlgorithm::changeCoordinates(Step step_Direction){
    switch (step_Direction)
    {
    case Step::North:
        curr_X--;
        break;
    case Step::East:
        curr_Y++;
        break;
    case Step::West:
        curr_Y--;
        break;
    case Step::South:
        curr_X++;
        break;
    default:
        break;
    }

}

std::string  MyAlgorithm::directionToString(Direction dir) { 
    switch (dir) { 
        case Direction::North: return "North"; 
        case Direction::East: return "East"; 
        case Direction::South: return "South"; 
        case Direction::West: return "West"; 
        default: return "Unknown";
    }
}

Step MyAlgorithm::backStep(){
    Direction direction=Path.top();
    std::cout<<directionToString(direction)<<std::endl;
    Path.pop();
    switch (direction) {
    case Direction::North:
        steps_Performed.push(Step::South);
        return Step::South;
    case Direction::South:
        steps_Performed.push(Step::North);
        return Step::North;
    case Direction::West:
        steps_Performed.push(Step::East);
        return Step::East;
    case Direction::East:
        steps_Performed.push(Step::West);
        return Step::West;
    default:
        //TODO: throw exception
        return Step::Finish;
    }
}

Step MyAlgorithm::returnToLastPoint(){
    Direction direction=path_To_LastPoint.top();
    std::cout<<"in returnToLastPoint, and the direction is : "<<directionToString(direction)<<std::endl;
    path_To_LastPoint.pop();
    switch (direction) {
    case Direction::North:
        steps_Performed.push(Step::South);
        return Step::South;
    case Direction::South:
        steps_Performed.push(Step::North);
        return Step::North;
    case Direction::West:
        steps_Performed.push(Step::East);
        return Step::East;
    case Direction::East:
        steps_Performed.push(Step::West);
        return Step::West;
    default:
        //TODO: throw exception
        return Step::Finish;
    }
}

bool MyAlgorithm::checkVisited(Direction direction){
    switch (direction) {
    case Direction::North:
        return alreadyVisited(std::pair<int,int>(curr_X-1,curr_Y));
    case Direction::South:
        return alreadyVisited(std::pair<int,int>(curr_X+1,curr_Y));
    case Direction::East:
        return alreadyVisited(std::pair<int,int>(curr_X,curr_Y+1));
    case Direction::West:
        return alreadyVisited(std::pair<int,int>(curr_X,curr_Y-1));
    default:
        //TODO: throw exception
        return false;
    }

}

bool MyAlgorithm::alreadyVisited( const std::pair<int, int> keyToFind){ 
    auto it = visited.find(keyToFind);
    return it != visited.end(); 
}





std::string MyAlgorithm::stepToString(Step step){
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
void MyAlgorithm::doneWorking(){
    done_Working=true;
}
*/


extern "C"{
    REGISTER_ALGORITHM(MyAlgorithm);
}