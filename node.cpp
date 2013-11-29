#include "node.hpp"

Node::Node(){
    trans_mat = glm::mat4(1.0f);
}

void
Node::setMesh(Mesh * mesh_){
    mesh = mesh_;
}

Mesh *
Node::getMesh(){
    return mesh;
}

glm::mat4
Node::getTransformation(){
    return trans_mat;
}

void
Node::translate(glm::vec3 translation){
    trans_mat = glm::translate(trans_mat, translation);
}

void
Node::rotate(float angle, glm::vec3 axis){
    trans_mat = glm::rotate(trans_mat, angle, axis);
}
