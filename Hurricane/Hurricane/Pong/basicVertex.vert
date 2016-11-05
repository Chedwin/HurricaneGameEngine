#version 430 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexColor;


// Output data ; will be interpolated for each fragment.
out vec4 myColor;

void main()
{	
	gl_Position =  vertexPosition;



	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	myColor = vertexColor;
}
