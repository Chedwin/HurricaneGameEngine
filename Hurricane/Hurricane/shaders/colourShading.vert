#version 430 core

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexColor;
layout(location = 2) in vec2 vertexUV;


uniform mat4 model_matrix; 		 // TRANSFORMATION MATRIX
uniform mat4 view_matrix; 		 // CAMERA
uniform mat4 projection_matrix;  // PROJECTION MATRIX


out vec4 myColor;
out vec2 fragmentUV;

void main(void)
{
	// REMEMBER: Matrix multiplication order DOES matter!!
	//			 i.e. A*B != B*A
	gl_Position = projection_matrix * view_matrix * model_matrix * vertexPosition;

	myColor = vertexColor;
	fragmentUV = vertexUV;
	
	// ALSO:
	// B/c of the projection matrix (frustum) above,
	//		objects ONLY in the frustum are being draw = OCCLUSION CULLING
}