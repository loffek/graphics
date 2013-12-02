#ifndef SHADERS_HPP
#define SHADERS_HPP

// Include third party
#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
//#include <stdexcept>
//#include <cmath>

GLuint createShaderProgram();
GLuint loadShader(const char *shaderFile, GLenum type);

#endif
