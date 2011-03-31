#version 150

uniform mat4 modelViewMatrix;   // model to view transform
uniform mat4 projectionMatrix;  // projection transform

in vec3 coord;                  // vertex coordinate in world space

void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * vec4(coord, 1.0);
}
