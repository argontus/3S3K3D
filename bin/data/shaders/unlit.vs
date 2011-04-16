#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

in vec3 position;   // vertex position in model space
in vec2 texCoord;   // vertex texture coordinate

out vec2 texCoord_; // fragment texture coordinate

void main()
{
    texCoord_ = texCoord;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
