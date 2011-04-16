#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

in vec3 position;   // vertex position in model space

void main()
{
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
