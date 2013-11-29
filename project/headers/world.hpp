#ifndef WORLD_HPP
#define WORLD_HPP

// standard headers
#include <vector>
#include <string>

// third party headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// project headers
#include "scene_graph.hpp"
#include "node.hpp"

class World
{
private:
    std::vector<Node *> nodes;
    SceneGraph scene;

public:
    World(){};
    void addNode(Node *node);
    std::vector<Node *> getNodes();
};

#endif
