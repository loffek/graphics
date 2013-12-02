#include "simulation.hpp"

Simulation::Simulation()
    :   window(NULL){
}

int
Simulation::init(GLFWwindow *window_){
    // set window
    window = window_;

/*    if (-1 == render_consumer.init(window)){
        fprintf( stderr, "Simulation: Could not initialize render consumer \n");
        return -1;
    }
*/
    return 0;

}

void
Simulation::start(){
}

void
Simulation::stop(){
}

/*
int
Simulation::loadModels(const char* folder){
    // load the wedge mesh
    Mesh *wedge_mesh = new Mesh((std::string(folder) + "wedge_vertex.csv").c_str(), (std::string(folder) + "wedge_index.csv").c_str());

    // register to render class to init buffers
    render_consumer.registerMesh(wedge_mesh);

    // create 2 Nodes
    Node* wedge1 = new Node();
    Node* wedge2 = new Node();

    // make the node look like the mesh (a wedge)
    wedge1->setMesh(wedge_mesh);
    wedge2->setMesh(wedge_mesh);

    //rotate and move back
    wedge2->rotate(90.0f, glm::vec3(0,0,1));
    wedge2->translate(glm::vec3(0.0f,0.0,0.0f));

    // add the nodes to the world of nodes!
    world.addNode(wedge1);
    world.addNode(wedge2);

    // and make the render_consumer consumer from the world
    render_consumer.setWorld(&world);
    return 0;
}
*/

void
Simulation::render(){
//    render_consumer.render();
}

void
Simulation::resizeWindow(GLFWwindow* window, int width, int height){
//    render_consumer.resizeWindow(window, width, height);
}
