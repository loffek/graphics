#include "mesh.hpp"

Mesh::Mesh(const char* vertex_file, const char* index_file){
    fprintf( stdout, "%s\n", vertex_file);
    fprintf( stdout, "%s\n", index_file);

    BufferContainer vertex_buf = getBufferFromFloatFile(vertex_file);
    BufferContainer index_buf= getBufferFromIntFile(index_file);
    vertex_data = (GLfloat*)vertex_buf.buffer;
    index_data = (GLshort*)index_buf.buffer;
    vertex_len = vertex_buf.length;
    index_len = index_buf.length;

    // this should not be hardcoded, but read from file
    vertex_size = sizeof(GLfloat);
    index_size = sizeof(GLshort);
    vertex_dim = 4;
    color_dim = 4;
    stride = vertex_size * (vertex_dim + color_dim);
    vertex_offset = (void *)0;
    color_offset = (void *) (vertex_dim * vertex_size);

    fprintf( stdout, "vertices: \n");
    for (int i=0; i<vertex_len; i += 8){
        fprintf( stdout, "v: ");
        for (int v=0; v<vertex_dim; v++)
            fprintf(stdout, "%f, ", vertex_data[i+v]);
        fprintf( stdout, "c: ");
        for (int c=0; c<color_dim; c++)
            fprintf(stdout, "%f, ", vertex_data[i+vertex_dim+c]);
        fprintf( stdout, "\n");
    }

    fprintf( stdout, "indices: ");
    for (int i=0; i<index_len; i++)
        fprintf(stdout, "%d, ", index_data[i]);
    fprintf( stdout, "\n");

    fprintf( stdout, "stride: %d\n", stride);
    fprintf( stdout, "color offset: %d\n", color_offset);
    fprintf( stdout, "index len: %d\n", index_len);
}

GLfloat *
Mesh::getVertexData(){
    return vertex_data;
}

GLshort *
Mesh::getIndexData(){
    return index_data;
}

GLsizei
Mesh::getStride(){
    return stride;
}

GLvoid *
Mesh::getVertexOffset(){
    return vertex_offset;
}

GLvoid *
Mesh::getColorOffset(){
    return color_offset;
}

int
Mesh::getVertexLen() {
    return vertex_len;
}
int
Mesh::getIndexLen() {
    return index_len;
}

size_t
Mesh::getVertexSize() {
    return vertex_size;
}
size_t
Mesh::getIndexSize() {
    return index_size;
}

int
Mesh::getVertexDimension() {
    return vertex_dim;
}

int
Mesh::getColorDimension() {
    return color_dim;
}

// TODO: make suer only render_consumer can use these :)
void
Mesh::setBuffers(GLuint VAO_, GLuint VBO_, GLuint IBO_){
    VAO = VAO_;
    VBO = VBO_;
    IBO = IBO_;
}

void
Mesh::getBuffers(GLuint *VAO_, GLuint *VBO_, GLuint *IBO_){
    *VAO_ = VAO;
    *VBO_ = VBO;
    *IBO_ = IBO;
}
