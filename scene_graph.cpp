#include "scene_graph.hpp"

SceneGraph::SceneGraph(){

}

void
SceneGraph::addRootNode(Node* node){

    root_nodes.push_back(node);

}
