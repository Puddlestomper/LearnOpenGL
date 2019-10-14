#version 330 core

out vec4 FragColour;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	FragColour = mix(texture(texture0, TexCoord), texture(texture1, vec2(1-TexCoord.x, TexCoord.y)), 0.2);
}