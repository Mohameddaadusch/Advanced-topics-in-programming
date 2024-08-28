#include "Algorithm_A_318978152_212001192.h"
#include <iostream>
#include <random>
#include <cstdlib>

Algorithm_A_318978152_212001192::Algorithm_A_318978152_212001192(){
    unexplored_Stack.push(std::pair<int,int>(0,0));
    curr_X=0;
    curr_Y=0;
}



void Algorithm_A_318978152_212001192::setMaxSteps(std::size_t maxSteps) {
    this->max_Steps=maxSteps;
    this->curr_Steps=0;
}

void Algorithm_A_318978152_212001192::setWallsSensor(const WallsSensor& walls_Sensor ){
    this->wall_Sensor = &walls_Sensor;
    
}

void Algorithm_A_318978152_212001192::setDirtSensor(const DirtSensor& Dirt_Sensor ){
    this->dirt_Sensor = &Dirt_Sensor;
}

void Algorithm_A_318978152_212001192::setBatteryMeter(const BatteryMeter& Battery_Meter){
    this->battery_Meter = &Battery_Meter;
    this->maxBattery=Battery_Meter.getBatteryState();
}



Step Algorithm_A_318978152_212001192::convertDirToStep(Direction dir){
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


Step  Algorithm_A_318978152_212001192::nextStep(){
    Step step_Direction=Step::West;
    bool fromBack=false;
    Direction direction;
    if((curr_Steps >= max_Steps-1 && curr_X == 0 && curr_Y == 0) || (unexplored_Stack.empty() && curr_X==0 && curr_Y==0) || (maxBattery<=1)){
        step_Direction = Step::Finish;
        curr_Steps--;
    }
    else if ((path_From_Dock.size()==0) && (battery_Meter->getBatteryState() < maxBattery)){
        step_Direction = Step::Stay;
        
    }
    else if(battery_Meter->getBatteryState() >= maxBattery && path_To_LastPoint.size()>0){
        step_Direction=returnToLastPoint();
    }
    else if(battery_Meter->getBatteryState() <= path_From_Dock.size() +1 || (max_Steps-curr_Steps -1) <= (int)path_From_Dock.size() ){
        if(!unexplored_Stack.empty()){
            auto next_Point = unexplored_Stack.top();
            if (dirt_Sensor->dirtLevel() == 0 && curr_X == next_Point.first && curr_Y == next_Point.second){
                visited[next_Point]=0;
                unexplored_Stack.pop();
            }
        }
        step_Direction = backStep();
        direction = convertStepToDir(step_Direction);
        path_To_LastPoint.push(reverseDirection(direction));
        fromBack=true;
    }
    else if(wall_Sensor->isWall(Direction::North) && wall_Sensor->isWall(Direction::South) && wall_Sensor->isWall(Direction::West) && wall_Sensor->isWall(Direction::East)){
        step_Direction=Step::Stay;
    }
    else{
        if (!unexplored_Stack.empty()) {
            auto next_Point = unexplored_Stack.top();
            while (findPairInSet(cleaned_Set,next_Point)){
                unexplored_Stack.pop();
                if (unexplored_Stack.empty()){
                    //in this case the stack is empty, no new unexplored i can go to, so go back to docking station
                    if(!unexplored_Stack.empty()){
                        auto next_Point = unexplored_Stack.top();
                        if (dirt_Sensor->dirtLevel() == 0 && curr_X == next_Point.first && curr_Y == next_Point.second){
                            visited[next_Point]=0;
                            //unexplored_Set.erase(next_Point);
                            unexplored_Stack.pop();
                        }
                    }
                    step_Direction = backStep();
                    direction = convertStepToDir(step_Direction);
                    path_To_LastPoint.push(reverseDirection(direction));
                    fromBack=true;
                    break;
                }else{
                    next_Point=unexplored_Stack.top();

                }
            }
            if((curr_X!=next_Point.first || curr_Y!=next_Point.second) && path_To_LastPoint.size()>0){
                step_Direction=returnToLastPoint();
            }
            else if (curr_X == next_Point.first && curr_Y == next_Point.second) {
                visited[next_Point] = dirt_Sensor->dirtLevel();
                if (dirt_Sensor->dirtLevel() > 0) {
                    step_Direction = Step::Stay;
                    visited[next_Point]--;
                }else{
                    cleaned_Set.insert(next_Point);
                    //unexplored_Set.erase(next_Point);
                    unexplored_Stack.pop();
                    int new_points=discoverUnexploredPoints();
                    if (new_points > 0) {
                        //i reached the point on the top of the stack, and finished cleaning it
                        //i have an unexplored neighbor, so i go to him 
                        next_Point=unexplored_Stack.top();
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
                        //all my neighbors are walls or visited, so the next point(top of the stack) is no a neighbor
                        //i want to get to the top of the stack and it is not one of my neighbors
                        if (!unexplored_Stack.empty()) {
                            next_Point=unexplored_Stack.top();
                            while (findPairInSet(cleaned_Set,next_Point)){
                                unexplored_Stack.pop();
                                if (unexplored_Stack.empty()){
                                    //in this case the stack is empty, no new unexplored i can go to, so go back to docking station
                                    if(!unexplored_Stack.empty()){
                                        auto next_Point = unexplored_Stack.top();
                                        if (dirt_Sensor->dirtLevel() == 0 && curr_X == next_Point.first && curr_Y == next_Point.second){
                                            visited[next_Point]=0;
                                            //unexplored_Set.erase(next_Point);
                                            unexplored_Stack.pop();
                                        }
                                    }
                                    step_Direction = backStep();
                                    direction = convertStepToDir(step_Direction);
                                    path_To_LastPoint.push(reverseDirection(direction));
                                    fromBack=true;
                                    break;
                                }else{
                                    next_Point=unexplored_Stack.top();

                                }
                            }
                            if (curr_X < next_Point.first && !wall_Sensor->isWall(Direction::South)
                                && checkVisited(Direction::South)) {
                                step_Direction = Step::South;
                            } else if (curr_X > next_Point.first && !wall_Sensor->isWall(Direction::North)
                                        && checkVisited(Direction::North)) {
                                step_Direction = Step::North;
                            } else if (curr_Y < next_Point.second && !wall_Sensor->isWall(Direction::East)
                                        && checkVisited(Direction::East)) {
                                step_Direction = Step::East;
                            } else if (curr_Y > next_Point.second && !wall_Sensor->isWall(Direction::West)
                                        && checkVisited(Direction::West)) {
                                step_Direction = Step::West;
                            }

                        }else{
                            //in this case the stack is empty, no new unexplored i can go to, so go back to docking station

                            if(!unexplored_Stack.empty()){
                                auto next_Point = unexplored_Stack.top();
                                if (dirt_Sensor->dirtLevel() == 0 && curr_X == next_Point.first && curr_Y == next_Point.second){
                                    visited[next_Point]=0;
                                    //unexplored_Set.erase(next_Point);
                                    unexplored_Stack.pop();
                                }
                            }
                            
                            step_Direction = backStep();
                            direction = convertStepToDir(step_Direction);
                            path_To_LastPoint.push(reverseDirection(direction));
                            fromBack=true;
                        }

                    }
                }
            } else {
                // didn't reach next_Point yet
                if (abs(curr_X-next_Point.first) + abs(curr_Y-next_Point.second) == 1 ){
                    // didn't reach next_Point yet and the next_point is a neighbor
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
                    if (curr_X < next_Point.first && !wall_Sensor->isWall(Direction::South)
                        && checkVisited(Direction::South)) {
                        step_Direction = Step::South;
                    } else if (curr_X > next_Point.first && !wall_Sensor->isWall(Direction::North)
                        && checkVisited(Direction::North)) {
                        step_Direction = Step::North;
                    } else if (curr_Y < next_Point.second && !wall_Sensor->isWall(Direction::East)
                        && checkVisited(Direction::East)) {
                        step_Direction = Step::East;
                    } else if (curr_Y > next_Point.second && !wall_Sensor->isWall(Direction::West)
                        && checkVisited(Direction::West)) {
                        step_Direction = Step::West;
                    }
                }
                
            }
        }else{
            if ((curr_X==0 && curr_Y==0)||(curr_Steps>=max_Steps)){
                step_Direction = Step::Finish;
                curr_Steps--;
            }else{
                
                if(!unexplored_Stack.empty()){
                    auto next_Point = unexplored_Stack.top();
                    if (dirt_Sensor->dirtLevel() == 0 && curr_X == next_Point.first && curr_Y == next_Point.second){
                        visited[next_Point]=0;
                        unexplored_Stack.pop();
                    }
                }
                
                step_Direction = backStep();
                direction = convertStepToDir(step_Direction);
                path_To_LastPoint.push(reverseDirection(direction));
                fromBack=true;

            }
            
        }
    }

    //vacuum.move(step_Direction);
    if (!fromBack && step_Direction!=Step::Stay && step_Direction!=Step::Finish){
        direction=convertStepToDir(step_Direction);
        Path.push(direction);
        
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




bool Algorithm_A_318978152_212001192::findPairInSet(const std::set<std::pair<int, int>>& mySet, const std::pair<int, int>& target) {
    auto it = mySet.find(target); // Search for the pair in the set
    return it != mySet.end();     // Return true if found, false otherwise
}


int Algorithm_A_318978152_212001192::discoverUnexploredPoints() {
    // Check all directions around the current position
    int res=0;
    for (const auto& dir : {Direction::South, Direction::East, Direction::North, Direction::West}) {
        if (!wall_Sensor->isWall(dir) && !checkVisited(dir) ) {
            auto next_Point = getCoordinatesInDirection(dir);
            unexplored_Stack.push(next_Point);
            res++;
        }
    }
    return res;
}

std::pair<int, int> Algorithm_A_318978152_212001192::getCoordinatesInDirection(Direction dir) {
    switch (dir) {
        case Direction::North: return {curr_X - 1, curr_Y};
        case Direction::South: return {curr_X + 1, curr_Y};
        case Direction::East: return {curr_X, curr_Y + 1};
        case Direction::West: return {curr_X, curr_Y - 1};
        default: return {curr_X, curr_Y};
    }
}


Direction Algorithm_A_318978152_212001192::convertStepToDir(Step step_Direction){
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


void Algorithm_A_318978152_212001192::changeCoordinates(Step step_Direction){
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


Step Algorithm_A_318978152_212001192::backStep(){
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

Step Algorithm_A_318978152_212001192::returnToLastPoint(){
    Direction direction=path_To_LastPoint.top();
    path_To_LastPoint.pop();
    switch (direction) {
    case Direction::North:

        return Step::North;

    case Direction::South:

        return Step::South;

    case Direction::West:

        return Step::West;
        
    case Direction::East:

        return Step::East;
    default:
        //TODO: throw exception
        return Step::Finish;
    }
}

Direction Algorithm_A_318978152_212001192::reverseDirection(Direction direction){
    switch (direction) {
    case Direction::North:
        return Direction::South;
    case Direction::South:
        return Direction::North;
    case Direction::West:
        return Direction::East;
    case Direction::East:
        return Direction::West;
    default:
        //TODO: throw exception
        return Direction::West;
    }
}

bool Algorithm_A_318978152_212001192::checkVisited(Direction direction){
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

bool Algorithm_A_318978152_212001192::alreadyVisited( const std::pair<int, int> keyToFind){ 
    auto it = visited.find(keyToFind);
    return it != visited.end(); 
}






extern "C"{
    REGISTER_ALGORITHM(Algorithm_A_318978152_212001192);
}