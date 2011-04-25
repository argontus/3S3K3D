#version 150

uniform vec3 ambientLightColor; // ambient lighting color

uniform sampler2D diffuseMap;   // diffuse map
uniform sampler2D glowMap;      // glow map

in vec2 texCoord_;              // fragment texture coordinate

out vec4 fragColor;             // fragment color

void main()
{
    vec4 diffuseColor = texture(diffuseMap, texCoord_);
    vec4 glowColor = texture(glowMap, texCoord_);
   
    fragColor = vec4(ambientLightColor * diffuseColor.rgb + glowColor.rgb, 1.0);
    gl_FragDepth = gl_FragCoord.z;
}
