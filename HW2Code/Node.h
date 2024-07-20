#ifndef NODE_H
#define NODE_H
#include <memory>

class Node {
public:
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> first_Son;
    std::shared_ptr<Node> second_Son;
    std::shared_ptr<Node> third_Son;
    std::shared_ptr<Node> fourth_Son;
    int d;
    int value;
    int x,y;

    // Constructor
    Node(int x, int y ,int d = 0, int value = 0,std::shared_ptr<Node> parent = nullptr, std::shared_ptr<Node> first_Son = nullptr, std::shared_ptr<Node> second_Son = nullptr,
                                                std::shared_ptr<Node> third_Son = nullptr , std::shared_ptr<Node> fourth_Son = nullptr);

    // Destructor
    ~Node();
};

#endif // NODE_H



