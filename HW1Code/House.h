#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include <string>

class House {
    std::vector<std::vector<int>> houseMap;
    int dockX, dockY;
    //void loadHouseFromFile(const std::string& filename);
public:
    House(const std::vector<std::vector<int>>& HouseMatrix, std::vector<int>);
    //void printHouse() const;
    bool isWall(int a, int b) const;
    int getDirtLevel(int a, int b) const;
    void cleanDirt(int a, int b);
    std::vector<int> getDock() const;
    
};

#endif
