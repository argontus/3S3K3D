#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

in vec3 coord;      // vertex position in model space
in vec3 normal;     // vertex normal in model space
in vec3 tangent;    // vertex tangent in model space
in vec2 texCoord;   // vertex texture coordinate

out vec3 coord_;    // fragment position in view space
out vec3 normal_;   // fragment normal in view space
out vec3 tangent_;  // fragment tangent in view space
out vec3 binormal_; // fragment binormal in view space
out vec2 texCoord_; // fragment texture coordinate

void main()
{
    coord_ = (modelViewMatrix * vec4(coord, 1.0)).xyz;
    normal_ = normalMatrix * normal;
    tangent_ = normalMatrix * tangent;
    binormal_ = cross(normal_, tangent_);
    texCoord_ = texCoord;

    // TODO: some of the lighting calculations done in the fragment shader
    // could be moved here

    gl_Position = projectionMatrix * modelViewMatrix * vec4(coord, 1.0);
}
