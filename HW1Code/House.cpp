#include "House.h"
#include <iostream>
#include <fstream>
#include <cassert>

House::House(const std::vector<std::vector<int>>& HouseMatrix, int x, int y): house_Matrix(HouseMatrix), dock_X(x),dock_Y(y) {
    int rows=house_Matrix.size();
    int cols=house_Matrix[0].size();
    total_dirt=0;
    for (int i=0; i<rows ;i++){
        for (int j=0;j<cols ; j++){
            if(house_Matrix[i][j]>0){
                total_dirt+=house_Matrix[i][j];
            }
        }
    }
}

int House::getTotalDirt() const{
    return House::total_dirt;
}
/*
void House::loadHouseFromFile(const std::string& filename) {
    std::ifstream file(filename);
    // Load the house layout from the file
    // Set dockX and dockY based on the file input
}

void House::printHouse() const {
    // Print the house layout for debugging
}
*/

// Return if (x, y) is a wall (-1: is wall, else the value is the dirt)
bool House::isWall(int x, int y) const {
    return (house_Matrix[x][y] == -1);
}

bool House::isOutOfBound(int x, int y) const {
    return (house_Matrix[x][y] == -2);
}


// Return the dirt level at (x, y) - a value between 1-9 or 0 (if the point is clean) or 
//-1 if the point is wall
//-2 if the point is out of bound
int House::getDirtLevel(int x, int y) const {
    assert(house_Matrix[x][y]>=0 & house_Matrix[x][y]<=9 ); // check if the value in point is correct
    return house_Matrix[x][y];
}

// Decrease the dirt level at (x, y)
void House::setDirt(int x, int y) {
    house_Matrix[x][y]-=1;
    House::total_dirt-=1;
}

int House::getDockX() const {
    return dock_X;
}

int House::getDockY() const {
    return dock_Y;
}
