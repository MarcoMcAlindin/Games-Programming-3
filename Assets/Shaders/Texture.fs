#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D myTexture;

uniform vec3 color;

uniform float opacity;

void main()
{
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = vec4(color, opacity) * texture(myTexture, TexCoord);
}