#include "world.hpp"

void
World::addNode(Node *node){
    // should really traverse children and flat out
    nodes.push_back(node);

    // add to scene of visible nodes
    scene.addRootNode(node);
}

std::vector<Node *>
World::getNodes(){
    return nodes;
}
