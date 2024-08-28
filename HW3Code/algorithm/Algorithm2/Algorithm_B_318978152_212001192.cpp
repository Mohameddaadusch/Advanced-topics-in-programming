#include "Algorithm_B_318978152_212001192.h"
#include <iostream>

Algorithm_B_318978152_212001192::Algorithm_B_318978152_212001192(){
    curr_X=0;
    curr_Y=0;
}



void Algorithm_B_318978152_212001192::setMaxSteps(std::size_t maxSteps) {
    this->max_Steps=maxSteps;
    this->curr_Steps=0;
}

void Algorithm_B_318978152_212001192::setWallsSensor(const WallsSensor& walls_Sensor ){
    this->wall_Sensor = &walls_Sensor;
    
}

void Algorithm_B_318978152_212001192::setDirtSensor(const DirtSensor& Dirt_Sensor ){
    this->dirt_Sensor = &Dirt_Sensor;
}

void Algorithm_B_318978152_212001192::setBatteryMeter(const BatteryMeter& Battery_Meter){
    this->battery_Meter = &Battery_Meter;
    this->maxBattery=Battery_Meter.getBatteryState();
}

Direction Algorithm_B_318978152_212001192::getMinDir() {
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

Direction Algorithm_B_318978152_212001192::changeDir(std::unordered_set<Direction> history){
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

Step Algorithm_B_318978152_212001192::convertDirToStep(Direction dir){
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

Step  Algorithm_B_318978152_212001192::nextStep(){
    Step step_Direction=Step::Stay;
    bool fromBack=false;
    Direction direction;
    std::unordered_set<Direction> history;
    
    visited[std::pair<int,int>(curr_X,curr_Y)]=dirt_Sensor->dirtLevel();
    if (dirt_Sensor->dirtLevel()==0){
        cleaned_Set.insert(std::pair<int,int>(curr_X,curr_Y));

    }
   
    if((curr_Steps >= max_Steps-1 && curr_X == 0 && curr_Y == 0) || (maxBattery<=1)){

        step_Direction = Step::Finish;
        curr_Steps--;
    }
    else if (((curr_X==0 && curr_Y==0) || path_From_Dock.size()==0) && (battery_Meter->getBatteryState() < maxBattery)){
        step_Direction = Step::Stay;
        while(path_From_Dock.size()>0){
            path_From_Dock.pop();
        }
        path_Set.clear();
    }
    else if(battery_Meter->getBatteryState() <= path_From_Dock.size() +1 || ( (max_Steps-curr_Steps -1) <= (int)path_From_Dock.size() && path_From_Dock.size()!=0 ) ){
        step_Direction = backStep();
        direction = convertStepToDir(step_Direction);
        fromBack=true;
    }
    else if(wall_Sensor->isWall(Direction::North) && wall_Sensor->isWall(Direction::South) && wall_Sensor->isWall(Direction::West) && wall_Sensor->isWall(Direction::East)){
        step_Direction=Step::Stay;
    }
    else if (dirt_Sensor->dirtLevel() > 0){
        step_Direction=  Step::Stay;
    }
    else{
        direction= getMinDir();

        if((!wall_Sensor->isWall(Direction::North) && !checkVisited(Direction::North)) || (!wall_Sensor->isWall(Direction::South) && !checkVisited(Direction::South)) 
            || (!wall_Sensor->isWall(Direction::West) && !checkVisited(Direction::West)) || (!wall_Sensor->isWall(Direction::East) && !checkVisited(Direction::East))){
            //in this "if" there is a direction which is not wall and not visited, so search for it and find it
            while(wall_Sensor->isWall(direction) || checkVisited(direction)){
                history.insert(direction);
                direction=changeDir(history);
            }

            min_Map[direction]+=1;
            step_Direction = convertDirToStep(direction);
        }
        else{
            //in this "else" every direction is or wall or visited, so take a random direction
            std::random_device rd;
            std::mt19937 mt(rd()); // Mersenne Twister random number generator seeded with random_device
            std::uniform_int_distribution<int> dist(1, 4); // Distribution for integers between 1 and 4 (inclusive)
            int randomNumber = dist(mt);
            direction= intToDirection(randomNumber);
            while(wall_Sensor->isWall(direction)){
                randomNumber = dist(mt);
                direction= intToDirection(randomNumber);
            }

            min_Map[direction]+=1;
            step_Direction = convertDirToStep(direction);
        }
    }
    //vacuum.move(step_Direction);
    
    if (!fromBack && step_Direction!=Step::Stay && step_Direction!=Step::Finish){
        direction=convertStepToDir(step_Direction);
        //Path.push(direction);
        
        std::pair<int,int> dir_cords=getCoordinatesInDirection(direction);
        if(findPairInSet(path_Set, dir_cords)){
            std::pair<Direction, std::pair<int,int>> path_Top=path_From_Dock.top();
            while (!(path_Top.second.first==dir_cords.first && path_Top.second.second==dir_cords.second)){
                path_Set.erase(std::pair<int,int>(path_Top.second.first,path_Top.second.second));
                path_From_Dock.pop();
                path_Top=path_From_Dock.top();
            }
        }else{
            path_From_Dock.push(std::pair<Direction, std::pair<int,int>>(direction, dir_cords));
            path_Set.insert(dir_cords);
        }
        
    }
    steps_Performed.push(step_Direction);
    curr_Steps++;
    changeCoordinates(step_Direction);
    return step_Direction;
}

Direction Algorithm_B_318978152_212001192::convertStepToDir(Step step_Direction){
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

Direction Algorithm_B_318978152_212001192::intToDirection(int value) {
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

std::pair<int, int> Algorithm_B_318978152_212001192::getCoordinatesInDirection(Direction dir) {
    switch (dir) {
        case Direction::North: return {curr_X - 1, curr_Y};
        case Direction::South: return {curr_X + 1, curr_Y};
        case Direction::East: return {curr_X, curr_Y + 1};
        case Direction::West: return {curr_X, curr_Y - 1};
        default: return {curr_X, curr_Y};
    }
}



void Algorithm_B_318978152_212001192::changeCoordinates(Step step_Direction){
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

bool Algorithm_B_318978152_212001192::findPairInSet(const std::set<std::pair<int, int>>& mySet, const std::pair<int, int>& target) {
    auto it = mySet.find(target); // Search for the pair in the set
    return it != mySet.end();     // Return true if found, false otherwise
}


Step Algorithm_B_318978152_212001192::backStep(){
    std::pair<Direction, std::pair<int,int>> path_Top=path_From_Dock.top();
    Direction direction=path_Top.first;
    path_Set.erase(std::pair<int,int>(path_Top.second.first,path_Top.second.second));
    path_From_Dock.pop();
    switch (direction) {
    case Direction::North:
        return Step::South;
    case Direction::South:
        return Step::North;
    case Direction::West:
        return Step::East;
    case Direction::East:
        return Step::West;
    default:
        //TODO: throw exception
        return Step::Finish;
    }
}

bool Algorithm_B_318978152_212001192::checkVisited(Direction direction){
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

bool Algorithm_B_318978152_212001192::alreadyVisited( const std::pair<int, int> keyToFind){ 
    auto it = visited.find(keyToFind);
    return it != visited.end(); 
}






extern "C"{
    REGISTER_ALGORITHM(Algorithm_B_318978152_212001192);
}