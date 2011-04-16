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

    // unit vector pointing from fragment to view point, we are in view space,
    // so eye position is the origin
    vec3 eyeDirection = normalize(-position_);

    // distance between the light source and the fragment
    float distance = length(lightPosition - position_);

    // distance coefficient, between [0, 1]
    float kDistance = 1 - (distance * distance) / (lightRange * lightRange);

    // direction vector pointing from fragment to the light source
    vec3 lightDirection = normalize(lightPosition - position_);

    // diffuse coefficient
    float kDiffuse = clamp(dot(lightDirection, normal), 0.0, 1.0);

    // light reflection direction
    vec3 reflection = reflect(-lightDirection, normal);

    // specular coefficient
    float kSpecular = max(0.0, dot(eyeDirection, reflection));
    kSpecular = pow(kSpecular, specularExponent);

    vec3 color = vec3(0.0, 0.0, 0.0);

    vec4 diffuseColor = texture(diffuseMap, texCoord_);
    vec4 specularColor = texture(specularMap, texCoord_);

    // TODO: make this a uniform variable?
    // diffuse and specular lighting correction threshold angle in radians, the
    // lighting correction will be applied when the angle between 'n' and
    // 'lightDirection' is between [0, 'correctionThreshold')
    const float correctionThreshold = 0.165;

    float correction = asin(clamp(dot(lightDirection, n), 0.0, 1.0));

    if (correction < correctionThreshold)
    {
        float kShadowFix = (correction * correction) / (correctionThreshold * correctionThreshold);
        color += kDistance * kShadowFix * (kDiffuse * diffuseColor.rgb + kSpecular * specularColor.rgb) * lightColor;

        // for debugging, shows which pixels are affected by the correction
        //color += vec3(1.0 - kShadowFix, 0.0, 0.0);
    }
    else
    {
        color += kDistance * (kDiffuse * diffuseColor.rgb + kSpecular * specularColor.rgb) * lightColor;
    }

    // for debugging, shows which pixels are affected by the light
    //color += lightColor;

    fragColor = vec4(color, 1.0);
    gl_FragDepth = gl_FragCoord.z;
}
