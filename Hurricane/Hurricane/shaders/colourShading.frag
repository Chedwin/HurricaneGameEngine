#version 430 core

in vec4 myColor;
in vec2 fragmentUV;

out vec4 fColor;

uniform sampler2D mySampler;
//uniform float myTime;

void main(void)
{
	vec4 textureColor = texture2D(mySampler, fragmentUV); // myColor;

	fColor= textureColor * myColor;

	//fColor = myColor + vec4(1.0 * (cos(myTime)+1.0) * 0.5, 1.0 * (cos(myTime)+2.0) * 0.5, 1.0 * (sin(myTime)+1.0) * 0.5, 1.0f);
	
}