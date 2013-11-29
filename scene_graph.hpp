#ifndef SCENE_GRAPH_HPP
#define SCENE_GRAPH_HPP

#include <vector>

// project headers
#include "node.hpp"

class SceneGraph
{

private:
    std::vector<Node *> root_nodes;

public:
    SceneGraph();
    void addRootNode(Node* node);
};


#endif
