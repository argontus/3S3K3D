#version 150

// hard-coded material ambient lighting parameter
const vec3 ambient = vec3(0.1, 0.1, 0.1);

// light parameters
//uniform vec3 lightPosition;     // light positions in view space
//uniform vec3 lightColor;        // light colors
//uniform float lightRange;       // light ranges in world space

uniform sampler2D diffuseMap;   // diffuse map
uniform sampler2D specularMap;  // specular map, unused
uniform sampler2D glowMap;      // glow map
uniform sampler2D normalMap;    // normal map, unused

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
