#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    fragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3);
};