#include "Camera.h"
#include "HurricaneProperties.h"


Camera::Camera() 
{
	// EMPTY
}

Camera::Camera(const VEC3& pos, hFLOAT fov, hFLOAT aspect, hFLOAT zNear, hFLOAT zFar) {
	_pos = pos;
	_projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);

	ResourceHandle<ShaderProgram> i = SHADER_MANAGER->GetShaderProgHandle("myShaderProgram").GetIndex();
	_mvpLoc = SHADER_MANAGER->GetShaderProgram(i)->GetUniformLocation("MVP");
}

Camera::~Camera()
{
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::Init(hINT scrWidth, hINT scrHeight)
{
	_screenWidth = scrWidth;
	_screenHeight = scrHeight;

	_projectionMatrix = glm::perspective(60.0f, (float)_screenWidth/ (float)_screenHeight, 0.1f, 100.0f);
	_cameraMatrix = glm::lookAt(_pos, _dir, _up);
}

void Camera::LookAt(VEC3& pos, VEC3& dir, VEC3& up) 
{
	//_cameraMatrix = glm::lookAt(pos, dir, up);
}

void Camera::Update(const hFLOAT _deltaTime)
{
	/*ResourceHandle<ShaderProgram> i = SHADER_MANAGER->GetShaderProgHandle("myShaderProgram").GetIndex();
	_mvpLoc = SHADER_MANAGER->GetShaderProgram(i)->GetUniformLocation("MVP");*/

	_cameraMatrix = glm::lookAt(
		glm::vec3(1, 1, -1), // Camera is at (4,3,-3), in World Space
		glm::vec3(0.0f, 0.0f, 0.0f), // and looks at the origin
		glm::vec3(0.0f, 1.0f, 0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	_modelView = MATRIX4(1.0f);

	_MVPmat = _projectionMatrix * _cameraMatrix * _modelView;

	glUniformMatrix4fv(_mvpLoc, 1, GL_FALSE, &_MVPmat[0][0]);


	//_projectionLocation = SHADER_MANAGER->GetShaderProgram(i)->GetUniformLocation("projection_matrix");
	//glProgramUniformMatrix4fv(SHADER_MANAGER->GetShaderProgram(i)->GetProgramID(), _projectionLocation, 1, GL_FALSE, &(_projectionMatrix[0][0]));

	//
	//_cameraMatrix = glm::lookAt(
	//	glm::vec3(2, 1, -1), // Camera is at (4,3,-3), in World Space
	//	glm::vec3(0, 0, 0), // and looks at the origin
	//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	//	);

	//_cameraLocation = SHADER_MANAGER->GetShaderProgram(i)->GetUniformLocation("camera_matrix");
	//glProgramUniformMatrix4fv(SHADER_MANAGER->GetShaderProgram(i)->GetProgramID(), _cameraLocation, 1, GL_FALSE, &(_cameraMatrix[0][0]));
	
}


// Reset the camera setting to default
void Camera::ResetCamera()
{
	_pos = VEC3(0.0f, 0.0f, 5.0f);
	_dir = VEC3(0.0f, 0.0f, -1.0f);
	_up = VEC3(0.0f, 1.0f, 0.0f);

	_scale = 1.0f;

	_screenWidth = 0;
	_screenHeight = 0;

	_projectionMatrix = MATRIX4(1.0);
	_cameraMatrix = MATRIX4(1.0);

	_cameraLocation = 0;
	_projectionLocation = 0;
}
