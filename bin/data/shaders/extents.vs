#version 150

uniform mat4 mvpMatrix;

in vec3 coord;

void main()
{
    gl_Position = mvpMatrix * vec4(coord, 1.0);
}
