#version 430 core
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexColor;

// TRANSFORMATION MATRIX
uniform mat4 model_matrix;

// CAMERA
uniform mat4 view_matrix;

// PROJECTION MATRIX
uniform mat4 projection_matrix;



out vec4 myColor;

void main()
{
	myColor = vertexColor;

	// REMEMBER: Matrix multiplication order DOES matter!!
	//			 i.e. A*B != B*A
	gl_Position = projection_matrix * view_matrix * model_matrix * vertexPosition;
	//gl_Position = view_matrix * model_matrix * vertexPosition;

	// ALSO:
	// B/c of the projection matrix (frustum) above,
	//		objects ONLY in the frustum are being draw = OCCLUSION CULLING
}
