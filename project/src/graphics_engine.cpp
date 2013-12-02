#include "graphics_engine.hpp"

GraphicsEngine::GraphicsEngine(){
//    world = NULL;
}

int
GraphicsEngine::init(GLFWwindow* window_){
    window = window_;
    // get screen size and aspect ratio
    int x,y;
    glfwGetWindowSize(window, &x, &y);
    SCREEN_SIZE.x = x;
    SCREEN_SIZE.y = y;
    ASPECT_RATIO = SCREEN_SIZE.x/SCREEN_SIZE.y;

    // load vertex and fragment shaders into opengl
    // move to materials class? or graphics object in render consumer?
    defaultShaderProgram = createShaderProgram();
    if (!defaultShaderProgram)
    {
        fprintf( stderr, "Could not create the shaders\n");
        return -1;
    }
    fprintf( stdout, "use program...");
    glUseProgram(defaultShaderProgram);
    fprintf( stdout, "done\n");

    fprintf( stdout, "get the uniforms...");
    perspectiveMatrixUnif = glGetUniformLocation(defaultShaderProgram, "perspectiveMatrix");
    viewMatrixUnif = glGetUniformLocation(defaultShaderProgram, "viewMatrix");
    modelMatrixUnif = glGetUniformLocation(defaultShaderProgram, "modelMatrix");
    fprintf( stdout, "done\n");

    perspectiveMatrix = glm::perspective(
        60.0f,            // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (zoomed in)
        ASPECT_RATIO,   // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f,           // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        100.0f          // Far clipping plane. Keep as little as possible.
    );

    cameraPosition = glm::vec3(0.0f,0.0f,1.0f);
    cameraTarget = glm::vec3(0.0f,0.0f,0.0f);
    upVector = glm::vec3(0.0f,1.0f,0.0f);

    viewMatrix = glm::lookAt( cameraPosition, cameraTarget, upVector );

    glUniformMatrix4fv(perspectiveMatrixUnif, 1, GL_FALSE, (GLfloat*)&(perspectiveMatrix[0][0]));

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    // set clear color
    glClearColor(0, 0, 0, 1); // black
    glClearDepth(1.0f);

    return 0;
}
/*
void
GraphicsEngine::setWorld(World* world_){
    world = world_;
}
*/
void
GraphicsEngine::render(){
/*
    GLuint VAO, VBO, IBO;
    std::vector<Node *> nodes = world->getNodes();

    // set view matrix
    glUniformMatrix4fv(viewMatrixUnif, 1, GL_FALSE, &viewMatrix[0][0]);
    // clear everything
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (std::vector<Node *>::iterator it = nodes.begin(); it != nodes.end(); it++){
        // set the modelMatrix for this mesh
        //fprintf( stderr, "beginning to render");
        glUniformMatrix4fv(modelMatrixUnif, 1, GL_FALSE, (GLfloat*)&((*it)->getTransformation()[0][0]));

        (*it)->getMesh()->getBuffers(&VAO, &VBO, &IBO);
        // bind the VAO
        //fprintf( stderr, "binding VAO");
        glBindVertexArray(VAO);

        //fprintf( stderr, "binding IBO");
        // bind indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        //fprintf( stderr, "drawing");
        // draw the VAO
        glDrawElements(GL_TRIANGLES, (*it)->getMesh()->getIndexLen(), GL_UNSIGNED_SHORT,(void*)0);
    }

    // unbind indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // unbind the VAO
    glBindVertexArray(0);

    // display
    glfwSwapBuffers(window);
*/
}

void
GraphicsEngine::resizeWindow(GLFWwindow* window_, int window_width, int window_height){
    // keeps apect ratio by filling symmetrical margins as needed

    if (window_ != window)
        return;

    int margin_left;
    int margin_top;

    if(float(window_width)/window_height > ASPECT_RATIO){
        // SCREEN_SIZE is wider than it should
        SCREEN_SIZE.x = int(window_height * ASPECT_RATIO);
        SCREEN_SIZE.y = window_height;
        margin_left = (window_width - SCREEN_SIZE.x)/2;
        margin_top = 0;
    }
    else{
        // SCREEN_SIZE is higher than it should
        SCREEN_SIZE.x = window_width;
        SCREEN_SIZE.y = int(window_width / ASPECT_RATIO);
        margin_left = 0;
        margin_top = (window_height - SCREEN_SIZE.y)/2;
    }
    glViewport(margin_left, margin_top, (GLsizei) SCREEN_SIZE.x, (GLsizei) SCREEN_SIZE.y);
}
/*
int
GraphicsEngine::registerMesh(Mesh* mesh){

    // make sure we have a context, maybe get one in constructor...

    GLuint VAO, VBO, IBO;

    // make and bind the VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // make and bind the VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // load the vertex buffer to OpenGL
    glBufferData(GL_ARRAY_BUFFER, mesh->getVertexSize() * mesh->getVertexLen(), mesh->getVertexData(), GL_STATIC_DRAW);

    // enable attribute index 0 and 1 in vertex shader
    glEnableVertexAttribArray(0); // postion data
    glEnableVertexAttribArray(1); // color data

    glVertexAttribPointer(
        0,                      // position data, attrib index 0
        mesh->getVertexDimension(),   // dimension
        GL_FLOAT,               // float point precision positions
        GL_FALSE,               // ??
        mesh->getStride(), // stride
        mesh->getVertexOffset()  // offset from start of buffer to position data
    );
    glVertexAttribPointer(
        1,                      // color data, attrib index 1
        mesh->getColorDimension(),   // color dimension
        GL_FLOAT,               // float point precision colors
        GL_FALSE,               // ??
        mesh->getStride(),      // no spacing between vectors
        mesh->getColorOffset()  // offset to color buffer
    );

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexSize()*mesh->getIndexLen(), mesh->getIndexData(), GL_STATIC_DRAW);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // unbind the VBO IBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mesh->setBuffers(VAO,VBO,IBO);
    meshes.push_back(mesh);

    // all ok!
    return 0;
}*/
