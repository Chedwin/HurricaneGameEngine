#version 150 



in   vec4 vertexPosition;
in   vec3 vertexNormal;

// output values that will be interpretated per-fragment
out  vec3 fN;
out  vec3 fE;
out  vec3 fL;

uniform mat4 model_view_matrix;
uniform vec4 lightPosition;
uniform mat4 projection_matrix;

void main()
{
    fN = vertexNormal;
    fE = (model_view_matrix * vertexPosition).xyz;
    fL = lightPosition.xyz;
    
    if (lightPosition.w != 0.0 ) {
		fL = lightPosition.xyz - vertexPosition.xyz;
    }

    gl_Position = projection_matrix * vertexPosition;
}
