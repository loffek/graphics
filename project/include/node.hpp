#ifndef NODE_HPP
#define NODE_HPP


// standard headers

// third party headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> /* translate, rotate */

// project headers

// forward declarations
class Material;
class Mesh;

class Node
{
private:
    Material*   material;
    Mesh*       mesh;

    // transformation matrix (or position vector + quaternion (orientation) and scale vector)
    glm::mat4   trans_mat;

public:
    Node();

    void setMesh(Mesh* mesh);
    Mesh * getMesh();
    glm::mat4 getTransformation();

    void translate(glm::vec3 translation);
    void rotate(float angle, glm::vec3 axis);
};


#endif
