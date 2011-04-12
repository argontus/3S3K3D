#version 150

// requires:
// glEnable(GL_POINT_SPRITE)
// glEnable(GL_PROGRAM_POINT_SIZE)
// glDepthMask(GL_FALSE)

uniform mat4 modelViewMatrix;   // model to view transform
uniform mat4 projectionMatrix;  // projection transform

in vec3 coord;                  // particle center point in world space
in vec4 color;                  // particle color
in float pointSize;             // particle size in world space

out vec4 color_;                // particle color

void main()
{
    color_ = color;

    vec4 viewCoord = modelViewMatrix *  vec4(coord, 1.0);

    // distance from camera to particle center point along z-axis
    float d = -viewCoord.z;

    const float windowHeight = 800.0;

    // gl_PointSize is this in pixels
    gl_PointSize = (pointSize * windowHeight) / d;

    gl_Position = projectionMatrix * viewCoord;
}
