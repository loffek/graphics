#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint createShaderProgram();
GLuint loadShader(const char *shaderFile, GLenum type);

#endif
