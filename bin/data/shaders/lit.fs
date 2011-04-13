#version 150

uniform vec3 lightPosition;     // light positions in view space
uniform vec3 lightColor;        // light colors
uniform float lightRange;       // light ranges in world space

uniform float specularExponent; // specular exponent

uniform sampler2D diffuseMap;   // diffuse map
uniform sampler2D specularMap;  // specular map
uniform sampler2D normalMap;    // normal map

in vec3 position_;              // fragment position in view space
in vec3 normal_;                // fragment normal in view space
in vec3 tangent_;               // fragment tangent in view space
in vec3 binormal_;              // fragment binormal in view space
in vec2 texCoord_;              // fragment texture coordinate

out vec4 fragColor;             // fragment color

void main()
{
    // these are interpolated linearly, calculate normalized versions
    vec3 t = normalize(tangent_);
    vec3 b = normalize(binormal_);
    vec3 n = normalize(normal_);

    // quick & dirty & ridiculously slow
    mat3 tbn = mat3(t, b, n);

    // calculate the fragment by transforming the tangent space normal map vector to view space
    vec3 normal = normalize(tbn * (texture(normalMap, texCoord_).xyz - vec3(0.5, 0.5, 0.5)));
    //vec3 normal = n;

    vec4 diffuseColor = texture(diffuseMap, texCoord_);
    vec4 specularColor = texture(specularMap, texCoord_);

    // for testing the normal mapping
    //vec4 diffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
    //vec4 glowColor = vec4(0.0, 0.0, 0.0, 1.0);

    vec3 color = vec3(0.0, 0.0, 0.0);

    // unit vector pointing from fragment to view point, we are in view space,
    // so eye position is the origin
    vec3 eyeDirection = normalize(-position_);

    // distance between the light source and the fragment
    float distance = length(lightPosition - position_);

    // distance coefficient, between [0, 1]
    float kDistance = max(lightRange - distance, 0.0) / lightRange;

    // direction vector pointing from light source to the fragment
    vec3 lightDirection = normalize(lightPosition - position_);

    // diffuse coefficient
    float kDiffuse = clamp(dot(lightDirection, normal), 0.0, 1.0);

    // light reflection direction
    vec3 reflection = reflect(-lightDirection, normal);

    // specular coefficient
    float kSpecular = max(0.0, dot(eyeDirection, reflection));
    kSpecular = pow(kSpecular, specularExponent);

    // this is an attempt at fixing the shadow jumping problem
    float kShadowFix = clamp(dot(lightDirection, n), 0.0, 1.0);
    kShadowFix = pow(min(1.0, kShadowFix / 0.15), 2.0);
    //kShadowFix = min(1.0, kShadowFix / 0.15);

    color += kDistance * kShadowFix * (kDiffuse * diffuseColor.rgb + kSpecular * specularColor.rgb) * lightColor;
    //color += kDistance * (kDiffuse * diffuseColor.rgb + kSpecular * specularColor.rgb) * lightColor;
/*
    if (kShadowFix < 1.0)
    {
        color += vec3(1.0 - kShadowFix, 0.0, 0.0);
    }
    else
    {
        color += kDistance * (kDiffuse * diffuseColor.rgb + kSpecular * specularColor.rgb) * lightColor;
    }
*/
    // force alpha component to diffuse color alpha component
    fragColor = vec4(color, diffuseColor.a);

    // identical to fixed-functionality fragment depth calculation
    gl_FragDepth = gl_FragCoord.z;
}
