#version 150

uniform vec3 ambientLightColor; // ambient lighting color
uniform vec3 ambientColor;      // material ambient reflectance color
uniform vec3 glowColor;         // material self illumination color

in vec2 texCoord_;              // fragment texture coordinate

out vec4 fragColor;             // fragment color

void main()
{
    fragColor = vec4(ambientLightColor * ambientColor + glowColor, 1.0);
    gl_FragDepth = gl_FragCoord.z;
}
