#version 430 core

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexColor;


uniform mat4 model_matrix; // TRANSFORMATION MATRIX
uniform mat4 view_matrix; // CAMERA
uniform mat4 projection_matrix; // PROJECTION MATRIX


out vec4 myColor;

void main(void)
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vertexPosition;

	myColor = vertexColor;
}