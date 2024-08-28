
#include "House.h"
#include <cassert>

House::House(){}

void House::init(std::string houseName ,const std::vector<std::vector<int>>& HouseM, int x, int y) {
    house_Name=houseName;
    house_Matrix=HouseM;
    dock_X = x;
    dock_Y = y;
    int rows= house_Matrix.size();
    int cols=house_Matrix[0].size();
    if(house_Matrix[x][y] > 0){
        house_Matrix[x][y] = 0;
    }
    if (x < 0 || y < 0 || x >= static_cast<int>(house_Matrix.size()) || y >= static_cast<int>(house_Matrix[0].size()) || house_Matrix[x][y] < 0 ) {
        throw std::invalid_argument("Invalid docking station coordinates/value. please try again:");
    }
    total_dirt=0;
    for (int i=0; i<rows ;i++){
            if(static_cast<int>(house_Matrix[i].size()) != cols){
                throw std::invalid_argument("Invalid matrix , the matrix not (mxn). please change yuour matrix:");
            }
        for (int j=0;j<cols ; j++){
            if(house_Matrix[i][j]>0){
                if(house_Matrix[x][y] > 9 || house_Matrix[x][y] < -1){
                    throw std::invalid_argument("Invalid house block value. please change yuour matrix with values from -1 to 9:");
                }
                total_dirt+=house_Matrix[i][j];
            }
        }
    }
}

int House::getTotalDirt() const{
    return House::total_dirt;
}
/*

void House::printHouse() const {
    // Print the house layout for debugging
}
*/

// Return if (x, y) is a wall (-1: is wall, else the value is the dirt)
bool House::isWall(int x, int y) const {
    return (house_Matrix[x][y] == -1);
}
    


// Return the dirt level at (x, y) - a value between 1-9 or 0 (if the point is clean) or 
//-1 if the point is wall
//-2 if the point is out of bound
int House::getDirtLevel(int x, int y) const {
    //std::cout<<"in house : " << house_Name <<std::endl;
    assert(house_Matrix[x][y]>=0 && house_Matrix[x][y]<=9 ); // check if the value in point is correct
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

void House::printHouse() const {
    for (const auto& row : house_Matrix) {
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