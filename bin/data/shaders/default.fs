#version 150

in vec3 coord_;     // fragment coordinate in view space
in vec3 normal_;    // fragment normal in view space

// quick & dirty
in vec3 lightPosition_; // light position in view space

out vec4 frag_color;

void main()
{
    // gl_FragCoord.x is between [0, width)
    // gl_FragCoord.y is between [0, height)
    // gl_FragCoord.z is between [0, 1]
    // gl_FragCoord.w is between ???

    // material lighting coefficients
    vec4 ambient  = vec4(0.05, 0.05, 0.05, 1.0);
    vec4 diffuse  = vec4(0.50, 0.50, 0.50, 1.0);
    vec4 specular = vec4(0.90, 0.90, 0.90, 1.0);
    float shininess = 128.0;

    // effect range radius for the light
    float range = 500.0;

    // distance between the light source and the fragment
    float distance = length(lightPosition_ - coord_);

    // distance coefficient, between [0, 1]
    float kDistance = max(range - distance, 0.0) / range;

    // direction vector pointing from light source to the fragment
    vec3 a = normalize(lightPosition_ - coord_);

    // diffuse term
    vec4 kDiffuse = max(dot(a, normal_), 0.0) * diffuse;
    kDiffuse = clamp(kDiffuse, 0.0, 1.0);

    // unit vector pointing from fragment to view point, we are in view space,
    // so eye position is the origin
    vec3 b = normalize(-coord_);

    // light reflection direction
    vec3 reflection = normalize(-reflect(a, normal_));

    // specular term
    vec4 kSpecular = pow(max(dot(b, reflection), 0.0), 0.3 + shininess) * specular;
    kSpecular = clamp(kSpecular, 0.0, 1.0);

    frag_color = ambient + kDistance * (kDiffuse + kSpecular);

    gl_FragDepth = gl_FragCoord.z;
}
