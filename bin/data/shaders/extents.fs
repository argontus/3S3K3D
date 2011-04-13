#version 150

out vec4 fragColor; // fragment color

void main()
{
    fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_FragDepth = gl_FragCoord.z;
}
