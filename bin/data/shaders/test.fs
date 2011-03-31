#version 150

// hard-coded material lighting parameters
const vec3 ambient = vec3(0.35, 0.35, 0.35);
const float specularExponent = 128.0;

// hard-coded maximum number of lights
const int maxLights = 8;

// light parameter arrays
uniform vec3 lightPositions[maxLights]; // light positions in view space
uniform vec3 lightColors[maxLights];    // light colors
uniform float lightRanges[maxLights];   // light ranges in world space
uniform int numLights;                  // number of active lights

uniform sampler2D diffuseMap;           // diffuse map
uniform sampler2D specularMap;          // specular map
uniform sampler2D glowMap;              // glow map
uniform sampler2D normalMap;            // normal map

in vec3 coord_;                         // fragment coordinate in view space
in vec3 normal_;                        // fragment normal in view space
in vec3 tangent_;                       // fragment tangent in view space
in vec3 binormal_;                      // fragment binormal in view space
in vec2 texCoord_;                      // fragment texture coordinate

out vec4 fragColor;                     // fragment color

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
    vec4 glowColor = texture(glowMap, texCoord_);

    // for testing the normal mapping
    //vec4 diffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
    //vec4 glowColor = vec4(0.0, 0.0, 0.0, 1.0);

    vec3 color = ambient * diffuseColor.rgb + glowColor.rgb;
    //vec3 color = ambient * diffuseColor.rgb;

    // unit vector pointing from fragment to view point, we are in view space,
    // so eye position is the origin
    vec3 eyeDirection = normalize(-coord_);

    // for each light
    for (int i = 0; i < numLights; ++i)
    {
        vec3 lightPosition = lightPositions[i];
        vec3 lightColor = lightColors[i];
        float lightRange = lightRanges[i];

        // distance between the light source and the fragment
        float distance = length(lightPosition - coord_);

        // distance coefficient, between [0, 1]
        float kDistance = max(lightRange - distance, 0.0) / lightRange;

        // direction vector pointing from light source to the fragment
        vec3 lightDirection = normalize(lightPosition - coord_);

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

        //if (kShadowFix < 1.0)
        //{
        //    color += vec3(kShadowFix, kShadowFix, kShadowFix);
        //}
        //else
        //{
        //    color += kDistance * (kDiffuse * diffuseColor.rgb + kSpecular * specularColor.rgb) * lightColor;
        //}
    }

    // force alpha component to diffuse color alpha component
    fragColor = vec4(color, diffuseColor.a);

    // identical to fixed-functionality fragment depth calculation
    gl_FragDepth = gl_FragCoord.z;
}
