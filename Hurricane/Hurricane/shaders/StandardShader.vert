#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec4 vNormal;


uniform mat4 model_matrix; 		 // TRANSFORMATION MATRIX
uniform mat4 view_matrix; 		 // CAMERA
uniform mat4 projection_matrix;  // PROJECTION MATRIX


out vec2 fragmentUV;
out vec4 worldPosition;

void main(void)
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vPosition;

	worldPosition = model_matrix * vPosition;

	fragmentUV = vTexCoord;
}