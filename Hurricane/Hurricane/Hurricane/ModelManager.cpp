#include <glew.h>

// Assimp model loading
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing 


#include "ModelManager.h"
#include "Debug.h"
#include "Model.h"
#include "ShaderProgramManager.h"
#include "StandardShader.h"
#include "TextureManager.h"

void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UNIQUE_PTR(ModelManager) ModelManager::_modelManager(nullptr); // Declare static unique pointer

ModelManager* ModelManager::GetModelManager()
{
	if (_modelManager.get() == nullptr) {
		_modelManager.reset(new ModelManager());
	}
	return _modelManager.get();
}


ModelManager::ModelManager()
{
	// Create, init, then store our shaders in the GLOBAL shader manager
	StandardShader* stdShader = STANDARD_SHADER;
	SHADER_MANAGER->StoreShaderProg("StandardShader", stdShader);



	// Gen buffers here
	glGenBuffers(NUMBER_OF_BUFFERS, Buffers);

	// Verties
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Buffer_Type::VERTEX_BUFFER]);
	glVertexAttribPointer(Attribute_Type::VERTEX_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(Attribute_Type::VERTEX_ATTRIBUTE);

	// Textures
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Buffer_Type::TEXTURE_BUFFER]);
	glVertexAttribPointer(Attribute_Type::TEXTURE_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(Attribute_Type::TEXTURE_ATTRIBUTE);

	// Normals (i.e. Lights)
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Buffer_Type::NORMAL_BUFFER]);
	glVertexAttribPointer(Attribute_Type::NORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(Attribute_Type::NORMAL_ATTRIBUTE);

	textureArray = nullptr;
	numberOfTextures = 0;
}

ModelManager::~ModelManager()
{
	// Delete all models
	_modelResources.EmptyResourceMap();

	// Delete the buffers
	//glDeleteBuffers(NUMBER_OF_BUFFERS, Buffers);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ModelManager::LoadModel(const STRING& _name, const STRING& _filePath) 
{
	// Check if model (name) exists in the model manager already
	ResourceHandle<Model> test = GetModelHandle(_name);
	if (!test.IsNull()) {
		return;
	}

	// Start using Assimp
	Assimp::Importer importer;

	// Ensure our models' polygons are triangles
	const aiScene* scene = importer.ReadFile(_filePath,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene) {
		Debug::ConsoleError("Model format not supported!", __FILE__, __LINE__);
		Debug::Log(EMessageType::ERR, "ModelManager", "LoadModel", __TIMESTAMP__, __FILE__, __LINE__, "Model format failed to be uploaded");
		return;
	}

	hUINT totalVerts = 0; 
	hUINT currentVertex = 0;

	hBOOL hasNormals = false;

	// How many vertices are in this model?
	for (hINT i = 0; i < scene->mNumMeshes; i++) {
		totalVerts += scene->mMeshes[i]->mNumVertices;
	}

	VEC2 cursorPos = VEC2(wherex(), wherey());

	//Debug::ConsoleLog("NumVertices: " + TO_STRING(totalVerts));

	Model* model = new Model();
	model->SetModelName(_name);


	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		Model::Mesh mesh;

		for (int j = 0; j < scene->mMeshes[i]->mNumVertices; j++)
		{
			VEC3 vertex = VEC3(scene->mMeshes[i]->mVertices[j].x, scene->mMeshes[i]->mVertices[j].y, scene->mMeshes[i]->mVertices[j].z);
			mesh.vertex.push_back(vertex);

			if (scene->mMeshes[i]->HasNormals())
			{
				VEC3 normal = VEC3(scene->mMeshes[i]->mNormals[j].x, scene->mMeshes[i]->mNormals[j].y, scene->mMeshes[i]->mNormals[j].z);
				mesh.normal.push_back(normal);
				hasNormals = true;
			}

			if (scene->mMeshes[i]->HasTextureCoords(0))
			{
				VEC2 texture = VEC2(scene->mMeshes[i]->mTextureCoords[0][j].x, scene->mMeshes[i]->mTextureCoords[0][j].y);
				mesh.textureMap.push_back(texture);
			}

			currentVertex++;

			if (currentVertex % 1000 == 0)
			{
				gotoxy(cursorPos.x, cursorPos.y);
				COUT << (currentVertex / (float)totalVerts) * 100 << "%    ";
			}
		}

		model->meshes.push_back(mesh);
	}

	gotoxy(cursorPos.x, cursorPos.y);
	COUT << "100%     \n";

	for (int m = 0; m < model->meshes.size(); m++) {
		for (unsigned int i = 0; i < model->meshes[m].vertex.size(); i++) {
			model->meshes[m].edge.push_back(i);
		}
	}


	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		for (int j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
		{
			model->meshes[i].face.push_back(scene->mMeshes[i]->mFaces[j].mNumIndices);
		}
	}

	for (int m = 0; m < model->meshes.size(); m++) {
		for (auto it = model->meshes[m].textureMap.begin(); it != model->meshes[m].textureMap.end(); it++)
		{
			masterTextureCoords.push_back(*it);
		}	
	}


	InsertModel(_name, model);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ModelManager::PushModels() 
{
	//Clear Buffers
	if (areBuffersInitialized)
	{
		GLuint zero = 0;

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[VERTEX_BUFFER]); glClearBufferData(GL_ARRAY_BUFFER, GL_RGB32F, GL_RGB, GL_UNSIGNED_INT, &zero);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[TEXTURE_BUFFER]); glClearBufferData(GL_ARRAY_BUFFER, GL_RG32F, GL_RG, GL_UNSIGNED_INT, &zero);
		glBindBuffer(GL_ARRAY_BUFFER, Buffers[NORMAL_BUFFER]); glClearBufferData(GL_ARRAY_BUFFER, GL_RGB32F, GL_RGB, GL_UNSIGNED_INT, &zero);

		glDeleteTextures(numberOfTextures, textureArray);
	}

	/*  VERTICES  */
	if (masterVectorList.size() > 0)
	{
		int arraySize = masterVectorList.size() * 3 * 4; //Each vector contains 3 floats (which are 4 bytes)
		float * newMasterList = new float[masterVectorList.size() * 3];

		//populate vector list
		{
			int i = 0;
			COUT << "Loading Vertices: " << (i / (float)masterVectorList.size()) * 100 << "%";

			for (i = 0; i < masterVectorList.size(); i++)
			{
				newMasterList[i * 3] = masterVectorList[i].x;
				newMasterList[3 * i + 1] = masterVectorList[i].y;
				newMasterList[3 * i + 2] = masterVectorList[i].z;

				if (i % 1000 == 0)
				{
					gotoxy(18, wherey());
					COUT << "                                                     ";
					gotoxy(18, wherey());
					COUT << (i / (float)masterVectorList.size()) * 100 << "%";
				}
			}

			gotoxy(0, wherey());
			COUT << "                                                                        ";
			gotoxy(0, wherey());
			COUT << "Loading Vertices: 100%\n";

			glBindBuffer(GL_ARRAY_BUFFER, Buffers[VERTEX_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER, arraySize, newMasterList, GL_STATIC_DRAW);

			COUT << "Loaded " << i << " Vertices.\n";
		}
		delete[] newMasterList;
	}

	/*  TEXTURES  */
	if (textureArray)
	{
		delete[] textureArray;
		textureArray = nullptr;
	}

	TextureManager* myTextures = TEXTURE_MANAGER;

	numberOfTextures = myTextures->GetNumTextures();
	textureArray = new GLuint[numberOfTextures];
	glGenTextures(numberOfTextures, textureArray);

	//Pass texture id to textures
	hINT i = 0;

	VECTOR(Texture*)::iterator iter = myTextures->_textureResources.resourceVector.begin();
	auto textureVector = myTextures->_textureResources.resourceVector;

	for (iter; iter != myTextures->_textureResources.resourceVector.end(); iter++)
	{
		COUT << "Loading Texture #:" << i << " \"" << textureVector[i]->GetResourceName() << "\"...";

		textureVector[i]->address = textureArray[i];

		//switch (textureVector[i]->dataType)
		//{
		//case Texture::TextureDataType::Float:
		//	glBindTexture(GL_TEXTURE_2D, textureVector[i]->address);
		//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureVector[i]->GetWidth(), textureVector[i]->GetHeight(), 0, GL_RGBA, GL_FLOAT, textureVector[i]->GetPixels());
		//	break;
		//case Texture::TextureDataType::UnsignedByte:
		//	glBindTexture(GL_TEXTURE_2D, textureVector[i]->address);
		//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureVector[i]->GetWidth, textureVector[i]->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textureVector[i]->GetPixels());
		//	break;
		//case Texture::TextureDataType::UnsignedByte_3D:
		//	glBindTexture(GL_TEXTURE_3D, textureVector[i]->address);
		//	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
		//	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, textureVector[i]->GetWidth(), textureVector[i]->GetHeight(), textureVector[i]->depth, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureVector[i]->pixelData);
		//	break;
		//}

		glBindTexture(GL_TEXTURE_2D, textureVector[i]->address);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureVector[i]->GetWidth(), textureVector[i]->GetHeight(), 0, GL_RGBA, GL_FLOAT, textureVector[i]->GetPixels());

		COUT << " done!\n";

		i++;
	}

	if (masterTextureCoords.size() > 0)
	{
		float * newMasterTextureList = new float[masterTextureCoords.size() * 2];
		for (int i = 0; i < masterTextureCoords.size(); i++)
		{
			newMasterTextureList[2 * i + 0] = masterTextureCoords[i].x;
			newMasterTextureList[2 * i + 1] = masterTextureCoords[i].y * -1;
		}

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[TEXTURE_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, masterTextureCoords.size() * 2 * 4, newMasterTextureList, GL_STATIC_DRAW);

		delete[] newMasterTextureList;
	}

	/* NORMALS */
	if (masterNormalList.size() > 0)
	{
		int arraySize = masterNormalList.size() * 3 * 4; //Each vector contains 3 floats (which are 4 bytes)
		float * newMasterList = new float[masterNormalList.size() * 3];

		//populate vector list
		for (int i = 0; i < masterNormalList.size(); i++)
		{
			newMasterList[i * 3] = masterNormalList[i].x;
			newMasterList[3 * i + 1] = masterNormalList[i].y;
			newMasterList[3 * i + 2] = masterNormalList[i].z;
		}

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, arraySize, newMasterList, GL_STATIC_DRAW);

		delete[] newMasterList;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ResourceHandle<Model> ModelManager::InsertModel(const STRING& _name, Model* _model)
{
	ResourceHandle<Model> result(-1);

	// Check if the resource name is already in use
	result = _modelResources.Get(_name);
	if (!result.IsNull()) {
		return result;
	}
	
	result = _modelResources.Add(_name, _model);

	for (int m = 0; m < _model->meshes.size(); m++)
	{
		_model->meshes[m].offsetVertex = masterVectorList.size();

		//for (auto it = _model->meshes[m].vertex.begin(); it != _model->meshes[m].vertex.end(); it++)
		for (int i = 0; i < _model->meshes[m].vertex.size(); i++)
		{
			masterVectorList.push_back(_model->meshes[m].vertex[i]);
			masterNormalList.push_back(_model->meshes[m].normal[i]);
		}

		for (int i = 0; i < _model->meshes[m].edge.size(); i++) {
			_model->meshes[m].edge[i] += _model->meshes[m].offsetVertex;	
		}
	}
	return result;
}

void ModelManager::DeleteModel(const STRING & _name)
{
	_modelResources.Remove(_name); 
}

void ModelManager::ClearAllModels()
{
	_modelResources.EmptyResourceMap();
}

ResourceHandle<Model> ModelManager::GetModelHandle(const STRING & _name)
{
	return _modelResources.Get(_name);
}

Model* ModelManager::GetModel(ResourceHandle<Model>& _handle)
{
	return _modelResources.Get(_handle);
}

Model* ModelManager::GetModel(const STRING& _name) 
{
	Model* result = nullptr;
	ResourceHandle<Model> handle = _modelResources.Get(_name);

	if (handle.IsNull()) {
		Debug::ConsoleError("Model named '" + _name + "' does not exist in ModelManager");
		return result;
	}
	result = ModelManager::GetModel(handle);
	return result;
}