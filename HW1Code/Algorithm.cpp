#include "Algorithm.h"
#include "Direction.h"
#include <random>


Algorithm::Algorithm(Vacuum& vacuum) : vacuum(vacuum) {
    vacuum.house.printHouse();
}

void Algorithm::decideNextMove() {
    Direction step_Direction=Direction::STAY;
    if ((Path.size()==0) && (vacuum.batterySensor() < vacuum.getMaxBattery())){
            vacuum.move(step_Direction);
    }
    else if (vacuum.dirtSensor()>0){
        vacuum.move(step_Direction);
        vacuum.clean();

    }
    else{
        // Create a random device and use it to seed the random number generator
        std::random_device rd;
        std::mt19937 mt(rd()); // Mersenne Twister random number generator seeded with random_device
        std::uniform_int_distribution<int> dist(1, 4); // Distribution for integers between 1 and 4 (inclusive)
        int randomNumber = dist(mt);
        step_Direction= intToDirection(randomNumber);
        while (vacuum.wallSensor(step_Direction)==true){
            int randomNumber = dist(mt);
            step_Direction= intToDirection(randomNumber);
        }
        vacuum.move(step_Direction);
    }
    if (step_Direction!=Direction::STAY){
        Path.push(step_Direction);
    }
    steps_Performed.push(step_Direction);
    
    
}

void Algorithm::backStep(){
    Direction direction=Path.top();
    switch (direction) {
    case Direction::UP:
        vacuum.move(Direction::DOWN);
        steps_Performed.push(Direction::DOWN);
        break;
    case Direction::DOWN:
        vacuum.move(Direction::UP);
        steps_Performed.push(Direction::UP);
        break;
    case Direction::RIGHT:
        vacuum.move(Direction::LEFT);
        steps_Performed.push(Direction::LEFT);
        break;
    case Direction::LEFT:
        vacuum.move(Direction::RIGHT);
        steps_Performed.push(Direction::RIGHT);
        break;
    default:
        //TODO: throw exception
        break;
    }
    Path.pop();
}

bool Algorithm::cleanAlgorithm() {
    if(vacuum.reachedMaxSteps() || vacuum.isMissionComplete()){
        return vacuum.isMissionComplete();
    }
    Direction dir;
    std::cout << "outside the while : reached max steps :" <<  vacuum.reachedMaxSteps() << ", path size : " <<  Path.size() << " battery left is : " << vacuum.batterySensor() <<std::endl;
    while((!vacuum.reachedMaxSteps()) && (vacuum.batterySensor() >= Path.size()+1)){
        printf( "################################################################3 \n");
        std::cout << "insside the while : reached max steps :" <<  vacuum.reachedMaxSteps() << ", path size : " <<  Path.size() << " battery left is : " << vacuum.batterySensor() <<std::endl;
        Algorithm::decideNextMove();
        std::cout << "after decideNextMove : battery left is: " << vacuum.batterySensor() <<std::endl;
        vacuum.house.printHouse();
        std::cout << vacuum.pos_X << "," << vacuum.pos_Y << std::endl;

    }
    if(vacuum.reachedMaxSteps()){
        return vacuum.isMissionComplete();
    }
    else{
        if(vacuum.batterySensor() <= Path.size()){
            while(Path.size()!=0){
                std::cout << "i am emptying the stack " << std::endl ; 
                backStep();
                if(vacuum.reachedMaxSteps()){
                    return vacuum.isMissionComplete();
                }
                std::cout << vacuum.pos_X << "," << vacuum.pos_Y << std::endl;
            }
            
            while(vacuum.batterySensor() < vacuum.getMaxBattery()){
                if(vacuum.isMissionComplete()){
                    return true;
                }
                if(vacuum.reachedMaxSteps()){
                    return vacuum.isMissionComplete();
                }
                std::cout << "the battery before charge ******* : " << vacuum.batterySensor() << std::endl;
                Algorithm::decideNextMove();
                std::cout << "the battery before charge : " << vacuum.batterySensor() << std::endl;
                vacuum.charge();
                std::cout << "the battery after charge : " << vacuum.batterySensor() << std::endl;
                
            }

            
        }
    }
    return Algorithm::cleanAlgorithm();
}
