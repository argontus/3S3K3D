#version 150

uniform mat4 mvp_matrix;

in vec3 coord;

void main()
{
    gl_Position = mvp_matrix * vec4(coord, 1.0);
}
