#version 150

uniform mat4 view_matrix;
uniform mat4 mv_matrix;
uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;

in vec3 coord;
in vec3 normal;
in vec4 color;

out vec3 coord_;    // vertex coordinate in view space
out vec3 normal_;   // vertex normal in view space
out vec4 color_;

// quick & dirty
out vec3 lightPosition_; // light position in view space

void main()
{
    coord_ = (mv_matrix * vec4(coord, 1.0)).xyz;
    normal_ = normal_matrix * normal;
    color_ = color;

    // hard-coded light position
    lightPosition_ = (view_matrix * vec4(-25.0, -25.0, 25.0, 1.0)).xyz;

    gl_Position = mvp_matrix * vec4(coord, 1.0);
}
