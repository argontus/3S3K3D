#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

in vec3 position;   // vertex position in model space
in vec3 normal;     // vertex normal in model space
in vec2 texCoord;   // vertex texture coordinate

out vec3 position_; // fragment position in view space
out vec3 normal_;   // fragment normal in view space
out vec2 texCoord_; // fragment texture coordinate

void main()
{
    position_ = (modelViewMatrix * vec4(position, 1.0)).xyz;
    normal_ = normalMatrix * normal;
    texCoord_ = texCoord;

    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
