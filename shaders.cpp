// Include third party
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
//#include <stdexcept>
//#include <cmath>

#include "shaders.hpp"

/* A simple function that will read a file into an allocated char pointer buffer */
char* filetobuf(char *file)
{
    FILE *fptr;
    long length;
    char *buf;
 
    fptr = fopen(file, "rb"); /* Open file for reading */
    if (!fptr) /* Return NULL on failure */
        return NULL;
    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
    fclose(fptr); /* Close the file */
    buf[length] = 0; /* Null terminator */
 
    return buf; /* Return the buffer */
}

GLuint loadShader(const char *shaderFile, GLenum type)
{
    std::ifstream in(shaderFile);
    std::string src= "";
    std::string line="";
    while(std::getline(in,line))
    src += line + "\n";
    //std::cout << src;
    GLuint shader;
    GLint compiled;
    shader = glCreateShader(type);

    const char* source = src.c_str();
    glShaderSource(shader,1,&source,NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char *strShaderType = NULL;
        switch(type)
        {
        case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
        case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
        case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }

        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
    }

    return shader;
}

// TODO: allow for Attributes to be put as function params
GLuint createShaderProgram()
{
    GLuint programId;
    GLuint vertexShader,fragmentShader;

    const char *vertex_shader = "vertex.glsl";
    const char *fragment_shader = "fragment.glsl";

    vertexShader = loadShader(vertex_shader, GL_VERTEX_SHADER);
    fragmentShader = loadShader(fragment_shader, GL_FRAGMENT_SHADER);
    if(!vertexShader || !fragmentShader) return 0;

    programId=glCreateProgram();
    if(!programId)
    {
        fprintf( stderr, "could not create the shader program\n");
        return 0;

    }
    glAttachShader(programId,vertexShader);
    glAttachShader(programId,fragmentShader);

    glBindAttribLocation(programId,0,"vPosition");
    glBindAttribLocation(programId,1,"vColor");

    glLinkProgram(programId);

    GLint status;
    glGetProgramiv (programId, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(programId, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure:\n%s\n", strInfoLog);
        delete[] strInfoLog;
        return 0;
    }

    glDetachShader(programId, vertexShader);
    glDetachShader(programId, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

 return programId;
}
