#version 150

// fragment color for debug output
//out vec4 fragColor;

void main()
{
    //fragColor = vec4(1.0, 1.0, 1.0, 1.0);
    gl_FragDepth = gl_FragCoord.z;
}
