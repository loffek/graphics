// TODO: add projection matrix and all that stuff
// TODO: make som smart modularisation of the loadModel and render function
// TODO: change to stream_draw

// third party libraries
// For window, context?
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Include standard headers
//#include <iostream>
#include <fstream>
//#include <stdexcept>
//#include <cmath>

// Include project headers
#include "simulation.hpp"


const glm::vec2 SCREEN_SIZE(640, 480);
const float ASPECT_RATIO = SCREEN_SIZE.x/SCREEN_SIZE.y;

GLFWwindow* window = NULL;
Simulation* simulation = NULL;

GLFWwindow* initGLFWwindow();
int initGlew();

void windowResizeCallback(GLFWwindow *window, int width, int height);

int main(){

    window = initGLFWwindow();
    if (!window){
        return -1;
    }
    if (-1 == initGlew()){
        glfwTerminate();
        return -1;
    }

    simulation = new Simulation();

    if (-1 == simulation->init(window)){
        glfwTerminate();
        return -1;
    }
    if (-1 == simulation->loadModels("data/")){
        glfwTerminate();
        return -1;
    }

    //simulation->start();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // render!!
        simulation->render();

        /* Poll for and process events */
        glfwPollEvents();
    }

    //simulation->stop();
    delete simulation;

    glfwTerminate();
    return 0;
}

void windowResizeCallback(GLFWwindow *window, int width, int height){
    if (simulation)
        simulation->resizeWindow(window, width, height);
}

GLFWwindow*
initGLFWwindow(){
    GLFWwindow* window;

    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return NULL;
    }

    //glfwWindowHint( GLFW_SAMPLES, 4 ); // 4x antialiasing
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( SCREEN_SIZE.x, SCREEN_SIZE.y, "Tutorial 01", NULL, NULL);
    if( !window )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        return NULL;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // bind callbacks
    glfwSetWindowSizeCallback(window, windowResizeCallback);

    return window;
}

int
initGlew(){

    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    // initialise GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2) {
        fprintf( stderr, "OpenGL 3.2 API is not available.\n");
        return -1;
    }

    // print out some info about the graphics drivers
    fprintf( stdout, "OpenGL version: %s\n", glGetString(GL_VERSION));
    fprintf( stdout, "GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    fprintf( stdout, "Vendor: %s\n", glGetString(GL_VENDOR));
    fprintf( stdout, "Renderer: %s\n", glGetString(GL_RENDERER));
    return 0;
}
