#version 150

// TODO: get rid of this
uniform mat4 view_matrix;

uniform mat4 mv_matrix;
uniform mat4 mvp_matrix;
uniform mat3 normal_matrix;

in vec3 coord;
in vec3 normal;

out vec3 coord_;    // fragment coordinate in view space
out vec3 normal_;   // fragment normal in view space

// quick & dirty
out vec3 lightPosition_; // light position in view space

void main()
{
    coord_ = (mv_matrix * vec4(coord, 1.0)).xyz;
    normal_ = normal_matrix * normal;

    // hard-coded light position
    lightPosition_ = (view_matrix * vec4(-25.0, 25.0, 25.0, 1.0)).xyz;
    //lightPosition_ = vec3(0.0, 0.0, -25.0);

    // TODO: using a separate projection matrix could be faster
    gl_Position = mvp_matrix * vec4(coord, 1.0);
}
