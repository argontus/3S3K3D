#version 150

uniform mat4 viewProjectionMatrix;

in vec3 position;   // vertex position in world space

void main()
{
    gl_Position = viewProjectionMatrix * vec4(position, 1.0);
}
