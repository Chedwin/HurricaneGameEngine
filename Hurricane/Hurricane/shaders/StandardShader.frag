#version 430 core

in vec2 fragmentUV;
in vec4 worldPosition;

out vec4 fColor;

uniform sampler2D mySampler;


void main(void)
{
	vec4 textureColor = texture2D(mySampler, fragmentUV); // myColor;

	fColor= textureColor;
}