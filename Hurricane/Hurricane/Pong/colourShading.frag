#version 430 core

in vec4 myColor;
out vec4 fColor;

uniform sampler2D mySampler;

void main()
{
	fColor = myColor;
}