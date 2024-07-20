#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"

class Graph {
private:
    Node* root; // The root node of the graph

public:
    // Constructor
    Graph(Node* root);

    // Destructor
    //~Graph();

    // Get the root node
    Node* getRoot();

    // Print the graph
    void printGraph(Node* node, int level = 0);

//private:
    // Helper function to recursively delete nodes
    //void deleteNode(Node* node);
};

#endif // GRAPH_H



