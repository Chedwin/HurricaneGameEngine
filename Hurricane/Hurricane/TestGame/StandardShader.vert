#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 vTexCoord;
//layout(location = 2) in vec3 vNormal;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  projection * view * model * vPosition;
	
	// UV of the vertex. No special space for this one.
	UV = vTexCoord;
}

