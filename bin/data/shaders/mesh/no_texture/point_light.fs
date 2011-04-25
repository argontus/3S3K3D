#version 150

uniform vec3 lightPosition;     // light position in view space
uniform vec3 lightColor;        // light color
uniform float lightRange;       // light range in world space

uniform vec3 diffuseColor;      // material diffuse reflectance color
uniform vec3 specularColor;     // material diffuse reflectance color
uniform float specularExponent; // specular exponent

in vec3 position_;              // fragment position in view space
in vec3 normal_;                // fragment normal in view space
in vec2 texCoord_;              // fragment texture coordinate

out vec4 fragColor;             // fragment color

void main()
{
    // normal_ is interpolated linearly, calculate normalized version
    vec3 normal = normalize(normal_);

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

    vec3 color = kDistance * (kDiffuse * diffuseColor + kSpecular * specularColor) * lightColor;

    fragColor = vec4(color, 1.0);
    gl_FragDepth = gl_FragCoord.z;
}
