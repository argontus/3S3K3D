#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

in vec3 coord;      // vertex position in model space
in vec3 normal;     // vertex normal in model space
in vec3 tangent;    // vertex tangent in model space
in vec2 texCoord;   // vertex texture coordinate

out vec2 texCoord_; // fragment texture coordinate

void main()
{
    texCoord_ = texCoord;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(coord, 1.0);
}
