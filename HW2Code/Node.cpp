#include "Node.h"

// Constructor implementation
Node::Node(int x , int y ,int d, int value, std::shared_ptr<Node> p, std::shared_ptr<Node> fs, std::shared_ptr<Node> ss, std::shared_ptr<Node> ts, std::shared_ptr<Node> frs) 
    : d(d),value(value), parent(p), first_Son(fs), second_Son(ss), third_Son(ts) , fourth_Son(frs){}

// Destructor implementation
Node::~Node() {
    // Optionally, you could handle cleanup here if needed
}


