#version 150

uniform sampler2D texture0; // particle texture

in vec4 color_;             // particle color

out vec4 fragColor;         // fragment color

void main()
{
    fragColor = color_ * texture(texture0, gl_PointCoord);
    //fragColor = max(color_ * texture(texture0, gl_PointCoord), 1.0);
}
