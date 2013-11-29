#ifndef MESH_HPP
#define MESH_HPP

#include <GLFW/glfw3.h> /* GLfloat */

#include <cstddef> /* size_t */

#include "file_helpers.hpp" /* BufferContainer, getBufferFromFLoatFile */

class Mesh
{

private:
    // TODO: protection against trying to render uninitialized meshes, some kind of dirty flag as well?

    GLuint VAO;
    GLuint VBO;
    GLuint IBO;

    GLfloat* vertex_data;
    GLshort* index_data;

    GLsizei stride;

    GLvoid* vertex_offset;
    GLvoid* color_offset;

    int vertex_len;
    int index_len;

    size_t vertex_size;
    size_t index_size;

    int vertex_dim;
    int color_dim;

    Mesh() {}; // default constructor

public:
    Mesh(const char* vertex_file, const char* index_file);
    GLfloat *getVertexData();
    GLshort *getIndexData();

    GLsizei getStride();

    GLvoid* getVertexOffset();
    GLvoid* getColorOffset();

    int getVertexLen();
    int getIndexLen();
    size_t getVertexSize();
    size_t getIndexSize();
    int getVertexDimension();
    int getColorDimension();

    void setBuffers(const GLuint VAO_, const GLuint VBO_, const GLuint IBO_);
    void getBuffers(GLuint* VAO_, GLuint* VBO_, GLuint* IBO_);

};


#endif
