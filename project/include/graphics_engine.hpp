#ifndef GRAPHICS_ENGINE_HPP
#define GRAPHICS_ENGINE_HPP

// standard headers
#include <cstring> /* memset */
#include <fstream>
#include <vector>

// third party headers
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// project headers
#include "shaders.hpp"
//#include "node.hpp"
//#include "mesh.hpp"
//#include "world.hpp"

// forward declarations
//class SceneGraph;

class GraphicsEngine
{
private:
    glm::vec2 SCREEN_SIZE;
    float ASPECT_RATIO;
    GLuint defaultShaderProgram;
    GLuint perspectiveMatrixUnif;
    GLuint viewMatrixUnif;
    GLuint modelMatrixUnif;

    glm::mat4 perspectiveMatrix;
    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 upVector;
    glm::mat4 viewMatrix;

//    World* world;
    GLFWwindow* window;

//    std::vector<Mesh *> meshes;

public:
    GraphicsEngine();
    int init(GLFWwindow* window_);
//    int registerMesh(Mesh* mesh);
//    int unregisterMesh(Mesh* mesh);

//    void setWorld(World* world_);

    void resizeWindow(GLFWwindow* window_, int window_width, int window_height);
    void render();
};

#endif
