#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
	FragColor = vec4(ourColor,1.0f);
}
