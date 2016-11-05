#include <Component.h>
#include "Pong.h"

Pong::Pong()
{
	_gameInstance = this;
	box = nullptr;
	player = nullptr;
	pongCam = nullptr;
}

Pong::~Pong() 
{
	glDeleteBuffers(2, Buffers);

	_shaderProgram->UnuseShader();
	delete box;
	box = nullptr;
}

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint location;

GLuint view_matrix_location;
GLuint projection_matrix_location;

GLfloat BallSize = 0.02f;
GLfloat playerSize = 0.05f;
GLfloat computerSize = 0.05f;
GLfloat walls = 0.5f + BallSize;

const GLuint NumVerticesInCube = 24;
const GLuint numVertsInPlayer = 24;
const GLuint numVertsInComp = 24;
const GLuint numVertsPerWall = 4;

const GLuint NumVertices = NumVerticesInCube + numVertsInPlayer + numVertsInComp + (numVertsPerWall * 3); //+ whatever other vertices you add above

glm::vec3 ballTranslateValue;
float ballXspeed = 0.0001;
float ballYspeed = 0.00015;

float rotate_value = 0;

glm::vec3 cameratranslateVal = glm::vec3(0, 0, -1.5);

glm::vec3 playerTranslateValue = glm::vec3(0, -0.5, 0);;
float computerTranslateValue = 0.25;

bool computerTurn = true;
bool hitBackWall = true;

int playerScore = 0;
int computerScore = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
hBOOL Pong::InitGame()
{
	// CREATE THE SHADERS
	_shaderProgram = new ShaderProgram();
	_shaderProgram->CompileShaders("colourShading.vert", "colourShading.frag");
	//_shaderProgram->AddAttribute("vertexPosition");
	//_shaderProgram->AddAttribute("vertexColor");
	_shaderProgram->LinkShaders();


	STRING name = "myShaderProgram";
	SHADER_MANAGER->StoreShaderProg(name, _shaderProgram);

	//hFLOAT aspect = renderer->GetAspectRatio();
	//pongCam = new Camera(VEC3(0.0f, 0.0f, 1.0f), 60.0f, aspect, 0.1f, 100.0f);

	//player = new PlayerPaddle();
	//box = new Box();

	GLfloat vertices[NumVertices][3] = {
		//Ball Coordinates
		//A
		{ -BallSize, BallSize, BallSize },
		{ BallSize, BallSize, BallSize },
		{ BallSize, BallSize, -BallSize },
		{ -BallSize, BallSize, -BallSize },

		//B
		{ -BallSize, BallSize, -BallSize },
		{ -BallSize, -BallSize, -BallSize },
		{ BallSize, -BallSize, -BallSize },
		{ BallSize, BallSize, -BallSize },

		//C
		{ BallSize, BallSize, -BallSize },
		{ BallSize, BallSize, BallSize },
		{ BallSize, -BallSize, BallSize },
		{ BallSize, -BallSize, -BallSize },

		//D
		{ -BallSize, BallSize, -BallSize },
		{ -BallSize, -BallSize, -BallSize },
		{ -BallSize, -BallSize, BallSize },
		{ -BallSize, BallSize, BallSize },

		//E
		{ BallSize, BallSize, BallSize },
		{ -BallSize, BallSize, BallSize },
		{ -BallSize, -BallSize, BallSize },
		{ BallSize, -BallSize, BallSize },

		//F
		{ BallSize, -BallSize, BallSize },
		{ -BallSize, -BallSize, BallSize },
		{ -BallSize, -BallSize, -BallSize },
		{ BallSize, -BallSize, -BallSize },

		///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
		//Player Coordinates
		//A
		{ -playerSize * 2, playerSize, playerSize },
		{ playerSize * 2, playerSize, playerSize },
		{ playerSize * 2, playerSize, -playerSize },
		{ -playerSize * 2, playerSize, -playerSize },

		//B
		{ -playerSize * 2, playerSize, -playerSize },
		{ -playerSize * 2, -playerSize, -playerSize },
		{ playerSize * 2, -playerSize, -playerSize },
		{ playerSize * 2, playerSize, -playerSize },

		//C
		{ playerSize * 2, playerSize, -playerSize },
		{ playerSize * 2, playerSize, playerSize },
		{ playerSize * 2, -playerSize, playerSize },
		{ playerSize * 2, -playerSize, -playerSize },

		//D
		{ -playerSize * 2, playerSize, -playerSize },
		{ -playerSize * 2, -playerSize, -playerSize },
		{ -playerSize * 2, -playerSize, playerSize },
		{ -playerSize * 2, playerSize, playerSize },

		//E
		{ playerSize * 2, playerSize, playerSize },
		{ -playerSize * 2, playerSize, playerSize },
		{ -playerSize * 2, -playerSize, playerSize },
		{ playerSize * 2, -playerSize, playerSize },

		//F
		{ playerSize * 2, -playerSize, playerSize },
		{ -playerSize * 2, -playerSize, playerSize },
		{ -playerSize * 2, -playerSize, -playerSize },
		{ playerSize * 2, -playerSize, -playerSize },

		///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
		///////////////////////////////////////////////////////
		//Computer Coordinates
		//A
		{ -computerSize * 2, computerSize, computerSize },
		{ computerSize * 2, computerSize, computerSize },
		{ computerSize * 2, computerSize, -computerSize },
		{ -computerSize * 2, computerSize, -computerSize },

		//B
		{ -computerSize * 2, computerSize, -computerSize },
		{ -computerSize * 2, -computerSize, -computerSize },
		{ computerSize * 2, -computerSize, -computerSize },
		{ computerSize * 2, computerSize, -computerSize },

		//C
		{ computerSize * 2, computerSize, -computerSize },
		{ computerSize * 2, computerSize, computerSize },
		{ computerSize * 2, -computerSize, computerSize },
		{ computerSize * 2, -computerSize, -computerSize },

		//D
		{ -computerSize * 2, computerSize, -computerSize },
		{ -computerSize * 2, -computerSize, -computerSize },
		{ -computerSize * 2, -computerSize, computerSize },
		{ -computerSize * 2, computerSize, computerSize },

		//E
		{ computerSize * 2, computerSize, computerSize },
		{ -computerSize * 2, computerSize, computerSize },
		{ -computerSize * 2, -computerSize, computerSize },
		{ computerSize * 2, -computerSize, computerSize },

		//F
		{ computerSize * 2, -computerSize, computerSize },
		{ -computerSize * 2, -computerSize, computerSize },
		{ -computerSize * 2, -computerSize, -computerSize },
		{ computerSize * 2, -computerSize, -computerSize },

		//Wall 1
		{ walls, walls, walls },
		{ walls, walls, -walls },
		{ -walls, walls, -walls },
		{ -walls, walls, walls },

		//Wall 2
		{ walls, walls, walls },
		{ walls, -walls, walls },
		{ walls, -walls, -walls },
		{ walls, walls, -walls },

		//Wall 3
		{ -walls, walls, walls },
		{ -walls, -walls, walls },
		{ -walls, -walls, -walls },
		{ -walls, walls, -walls }
	};

	GLfloat colorData[NumVertices][3] = {
		//START BALL COLOUR
		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },

		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },

		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },

		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },

		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },

		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },
		{ 1,0,0 },
		//END BALL COLOUR
		//START PLAYER COLOUR
		{ 0,1,0 }, // color for vertices
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },

		{ 0,1,0 }, // color for vertices
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },

		{ 0,1,0 }, // color for vertices
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },

		{ 0,1,0 }, // color for vertices
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },

		{ 0,1,0 }, // color for vertices
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },

		{ 0,1,0 }, // color for vertices
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },
		//END PLAYER COLOUR
		//START COMPUTER COLOUR
		{ 0,0,1 }, // color for vertices
		{ 0,0,1 },
		{ 0,0,1 },
		{ 0,0,1 },

		{ 0,0,1 }, // color for vertices
		{ 0,0,1 },
		{ 0,0,1 },
		{ 0,0,1 },

		{ 0,0,1 }, // color for vertices
		{ 0,0,1 },
		{ 0,0,1 },
		{ 0,0,1 },

		{ 0,0,1 }, // color for vertices
		{ 0,0,1 },
		{ 0,0,1 },
		{ 0,0,1 },

		{ 0,0,1 }, // color for vertices
		{ 0,0,1 },
		{ 0,0,1 },
		{ 0,0,1 },

		{ 0,0,1 }, // color for vertices
		{ 0,0,1 },
		{ 0,0,1 },
		{ 0,0,1 },
		//END COMPUTER COLOUR

		//WALL COLOURS
		{ 1,0,1 }, // color for vertices
		{ 1,0,1 },
		{ 1,0,1 },
		{ 1,0,1 },

		{ 0,1,1 }, // color for vertices
		{ 0,1,1 },
		{ 0,1,1 },
		{ 0,1,1 },

		{ 0,1,1 }, // color for vertices
		{ 0,1,1 },
		{ 0,1,1 },
		{ 0,1,1 }
	};

	glGenBuffers(2, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindAttribLocation(_shaderProgram->GetProgramID(), 0, "vertexPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	glBindAttribLocation(_shaderProgram->GetProgramID(), 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	location = glGetUniformLocation(_shaderProgram->GetProgramID(), "model_matrix");
	view_matrix_location = glGetUniformLocation(_shaderProgram->GetProgramID(), "view_matrix");
	projection_matrix_location = glGetUniformLocation(_shaderProgram->GetProgramID(), "projection_matrix");


	return true;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Pong::GameUpdate(const hFLOAT _deltatime)
{
	// window title bar update
	STRINGSTREAM ss;
	ss << "Pong | FPS: " << fps;
	STRING _fps = ss.str();

	SDL_SetWindowTitle(gameWindow->GetWindow(), _fps.c_str());
}



////////////////////////////////////////////////////////////
void Pong::GameRender()
{
	_shaderProgram->UseShader();

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);

	//////////////////////
	//Draw the ball/cube//
	//////////////////////
	glm::mat4 model_view = glm::translate(glm::mat4(1.0), ballTranslateValue);
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);

	glDrawArrays(GL_QUADS, 0, NumVerticesInCube);


	//////////////////////////
	//Draw the player square//
	//////////////////////////
	model_view = glm::translate(glm::mat4(1.0), playerTranslateValue);
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
	glDrawArrays(GL_QUADS, NumVerticesInCube, numVertsInPlayer);

	////////////////////////////
	//Draw the computer square//
	////////////////////////////
	model_view = glm::translate(glm::mat4(1.0), glm::vec3(computerTranslateValue, -0.6, 0.0));
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
	glDrawArrays(GL_QUADS, NumVerticesInCube + numVertsInPlayer, numVertsInComp);

	model_view = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);

	//Cam
	glm::vec3 loc = cameratranslateVal;
	glm::vec3 dir = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cam_mat = glm::lookAt(loc, dir, up);
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, &cam_mat[0][0]);

	// Camera Type - lens properties, near and far planes
	glm::mat4 proj_mat = glm::frustum(-0.5f, .5f, -.5f, 0.5f, 1.0f, 10.0f);
	glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, &proj_mat[0][0]);
	glDrawArrays(GL_QUADS, NumVerticesInCube + numVertsInPlayer + numVertsInComp, numVertsPerWall * 3);
}