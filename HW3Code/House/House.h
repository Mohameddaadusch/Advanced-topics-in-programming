#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>

class House {
    std::vector<std::vector<int>> house_Matrix;
    int dock_X, dock_Y;
    int total_dirt;
    std::string house_Name;
public:
    House();
    void init(std::string house_Name, const std::vector<std::vector<int>>& HouseMatrix, int x, int y);
    void printHouse() const;
    bool isWall(int x, int y) const;
    int getDirtLevel(int x, int y) const;
    void setDirt(int x, int y);
    int getDockX() const;
    int getDockY() const;
    int getHouseMap() const;
    int getTotalDirt() const;
    
};

#endif

