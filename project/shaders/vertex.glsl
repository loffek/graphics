#version 150 core

in vec4 vPosition;
in vec4 vColor;

smooth out vec4 theColor;

uniform mat4 perspectiveMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
    gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * vPosition;

    theColor = vColor;
}
