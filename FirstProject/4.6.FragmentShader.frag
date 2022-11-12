#version 460 core

out vec4 testColor;
in vec3 redColor;


void main()
{
	testColor = vec4(redColor,1.0f);
}