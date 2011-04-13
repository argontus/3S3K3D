#version 150

// requires:
// glEnable(GL_POINT_SPRITE) (deprecated)
// glEnable(GL_VERTEX_PROGRAM_POINT_SIZE)
// glDepthMask(GL_FALSE)

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 position;   // particle center point in world space
in vec4 color;      // particle color
in float pointSize; // particle size in world space

out vec4 color_;    // particle color

void main()
{
    vec4 viewCoord = viewMatrix *  vec4(position, 1.0);

    // distance from camera to particle center point along z-axis
    float d = -viewCoord.z;

    // TODO: no hard-coding
    const float windowHeight = 800.0;

    // gl_PointSize is in pixels

    color_ = color;
    gl_PointSize = (pointSize * windowHeight) / d;
    gl_Position = projectionMatrix * viewCoord;
}
