#ifndef SIMULATION_HPP
#define SIMULATION_HPP


// standard headers
#include <fstream>

// third party headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// project headers
#include "world.hpp"
#include "node.hpp"
#include "mesh.hpp"
#include "render_consumer.hpp"

class Simulation
{
private:
    GLFWwindow* window;

    World world;

    RenderConsumer render_consumer;
    //PhysicsConsumer physics_consumer;
    //LogicConsumer logic_consumer;
    //AudioConsumer audio_consumer;

public:
    Simulation();
    int init(GLFWwindow *window);
    int loadModels(const char* folder);

    /* Physics API */
    //void start();
    //void stop();

    /* Graphics API */
    void render();
    void resizeWindow(GLFWwindow* window, int width, int height);
};

#endif
