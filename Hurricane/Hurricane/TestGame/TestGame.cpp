#include <FlyCamera.h>
#include <ImageManager.h>
#include <MaterialManager.h>
#include "TestGame.h"

TestGame::TestGame() : Game()
{
	_gameInstance = this;
}

TestGame::~TestGame()
{
	delete box;
	modelShader->UnuseShader();
}



/////////////////////////////////////////////////////////////////////////////////////////

hBOOL TestGame::InitGame()
{
	// CREATE THE SHADERS
	modelShader = new ShaderProgram("Model Shader");
	modelShader->CompileShaders("../shaders/modelStandard.vert", "../shaders/modelStandard.frag");
	modelShader->AddAttribute("vertexPosition");
	modelShader->AddAttribute("vertexColor");
	modelShader->AddAttribute("vertexUV");
	modelShader->LinkShaders();

	

	// Store shader in manager
	SHADER_MANAGER->StoreShaderProg(modelShader->GetProgramName(), modelShader);


	//// USE THE SHADER PROGRAM
	modelShader->UseShader();

	Material* myMaterial = new Material("myMaterial");
	MATERIAL_MANAGER->StoreMaterial(myMaterial->GetMaterialName(), myMaterial);
	myMaterial->SetShaderName(modelShader->GetProgramName());

	box = new Box();

	// Set location of uniform variables of matrices in shader
	location = modelShader->GetUniformLocation("model_matrix");
	view_matrix_location = modelShader->GetUniformLocation("view_matrix");
	projection_matrix_location = modelShader->GetUniformLocation("projection_matrix");

	
	box->transform.Translate(VEC3(1, 1, -20));

	FLY_DEBUG_CAM->frustum.WindowResized(60.0f, H_PROPERTIES->GetVideoProperties()->AspectRatio(), 0.1f, 10.0f);

	FLY_DEBUG_CAM->SetProjLocation(projection_matrix_location);
	FLY_DEBUG_CAM->SetViewLocation(view_matrix_location);
	FLY_DEBUG_CAM->SetPostion(VEC3(-1.0f, -1.0f, 1.0f));

	return true;
}


void TestGame::GameInput(SDL_Event & _evnt)
{
	FLY_DEBUG_CAM->MoveCamera(_evnt);
}

void TestGame::GameUpdate(const hFLOAT _deltaTime)
{
	// window title bar update
	STRINGSTREAM ss;
	ss << "New Game! | FPS: " << GetFPS();
	STRING fpsTitle = ss.str();

	SDL_SetWindowTitle(gameWindow->GetWindow(), fpsTitle.c_str());

	FLY_DEBUG_CAM->frustum.IsInside(box->transform.position);
	FLY_DEBUG_CAM->Update(_deltaTime);
}

void TestGame::GameRender()
{
	FLY_DEBUG_CAM->Render();
	static float time = 0.0f;

	//// Draw the triangle !
	glm::mat4 model_view = glm::mat4(1.0f) * glm::rotate(MATRIX4(1.0f), time, VEC3(1, 1, 1));

	//time += 0.003f;
	//glm::rotate(MATRIX4(1.0f), 10.0f, VEC3(0, 0, 1));
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
	//box->Render();

	GLint textureLocation = modelShader->GetUniformLocation("mySampler");

	glUniform1i(textureLocation, 0);

	box->Render();

	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glDrawArrays(GL_QUADS, 0, NumVertices);
}

