#version 150

uniform vec3 ambient;           // ambient lighting color

uniform sampler2D diffuseMap;   // diffuse map
uniform sampler2D glowMap;      // glow map

in vec3 coord_;                 // fragment coordinate in view space, unused
in vec3 normal_;                // fragment normal in view space, unused
in vec3 tangent_;               // fragment tangent in view space, unused
in vec3 binormal_;              // fragment binormal in view space, unused
in vec2 texCoord_;              // fragment texture coordinate

out vec4 fragColor;             // fragment color

void main()
{
    vec4 diffuseColor = texture(diffuseMap, texCoord_);
    vec4 glowColor = texture(glowMap, texCoord_);
   
    fragColor = vec4(ambient * diffuseColor.rgb + glowColor.rgb, 1.0);

    gl_FragDepth = gl_FragCoord.z;
}
