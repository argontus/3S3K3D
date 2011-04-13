#version 150

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 position;   // vertex position in world space

void main()
{
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
}
