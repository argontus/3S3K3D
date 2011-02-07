#version 150

out vec4 frag_color;

void main()
{
    frag_color = vec4(1.0, 1.0, 1.0, 1.0);
    gl_FragDepth = gl_FragCoord.z;
}
