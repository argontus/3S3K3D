#version 150

uniform sampler2D particleTexture;

in vec4 color_;
in vec2 texCoord_;

out vec4 fragColor;

void main()
{
    fragColor = color_ * texture(particleTexture, texCoord_);
    gl_FragDepth = gl_FragCoord.z;
}
