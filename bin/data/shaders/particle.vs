#version 150

uniform mat4 viewProjectionMatrix;

in vec3 position;
in vec4 color;
in vec2 texCoord;

out vec4 color_;
out vec2 texCoord_;

void main()
{
    color_ = color;
    texCoord_ = texCoord;

    gl_Position = viewProjectionMatrix * vec4(position, 1.0);
}
