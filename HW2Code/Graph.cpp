#include "Graph.h"
#include <iostream>

// Constructor implementation
Graph::Graph(Node* root): root(root) {}
    /*
    // Destructor implementation
    Graph::~Graph() {
        deleteNode(root);
    }

    // Helper function to recursively delete nodes
    void Graph::deleteNode(Node* node) {
        if (node != nullptr) {
            deleteNode(node->first_Son);
            deleteNode(node->second_Son);
            deleteNode(node->third_Son);
            deleteNode(node->forth_Son);
            delete node;
        }
    }
    */
    // Get the root node
    Node* Graph::getRoot() {
        return root;
    }

    // Print the graph
    void Graph::printGraph(Node* node, int level) {
        if (node == nullptr) return;

        for (int i = 0; i < level; ++i) {
            std::cout << "  ";
        }
        std::cout << "Node Value: " << node->value << ", D: " << node->d << std::endl;

        printGraph(node->first_Son, level + 1);
        printGraph(node->second_Son, level + 1);
        printGraph(node->third_Son, level + 1);
        printGraph(node->forth_Son, level + 1);
}



