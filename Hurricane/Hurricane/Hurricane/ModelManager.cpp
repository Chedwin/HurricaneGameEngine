#include "ModelManager.h"
#include "Debug.h"
#include "Model.h"
#include "ShaderProgram.h"

#include <glew.h>

// Assimp model loading
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing 

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
	// Gen buffers here
	glGenBuffers(NUMBER_OF_BUFFERS, Buffers);

	// Vertex
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

}

ModelManager::~ModelManager()
{
	_modelResources.EmptyResourceMap();
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ModelManager::LoadModel(const STRING& _name, const STRING& _filePath) 
{
	// Check if model (name) exists in the model manager already
	ResourceHandle<Model> test = GetModelHandle(_name);
	if (!test.IsNull())
		return;

	// Start using Assimp
	Assimp::Importer importer;

	// Ensure our models' polygons are triangles
	const aiScene* scene = importer.ReadFile(_filePath, aiProcess_Triangulate | aiProcess_SortByPType);

	hUINT totalVerts = 0; 
	hUINT currentVertex = 0;

	hBOOL hasNormals = false;

	// How many vertices are in this model?
	for (hINT i = 0; i < scene->mNumMeshes; i++) {
		totalVerts += scene->mMeshes[i]->mNumVertices;
	}

	//Debug::ConsoleLog("NumVertices: " + TO_STRING(totalVerts));

	Model* newModel = new Model();
	newModel->SetModelName(_name);

	// Start with the first mesh in the model
	// REMEMBER: a single model can have multiple "meshes" contained in it like pieces
	// i.e. Humanoid - head, legs, arms, hands, etc.
	for (int a = 0; a < scene->mNumMeshes; a++)
	{
		Model::Mesh newMesh;

		for (int b = 0; b < scene->mMeshes[a]->mNumVertices; b++)
		{
			VEC3 vertexCoords = VEC3(scene->mMeshes[a]->mVertices[b].x, scene->mMeshes[a]->mVertices[b].y, scene->mMeshes[a]->mVertices[b].z);
			newMesh.vertex.push_back(vertexCoords);


			if (scene->mMeshes[a]->HasNormals())
			{
				VEC3 normalCoords = VEC3(scene->mMeshes[a]->mNormals[b].x, scene->mMeshes[a]->mNormals[b].y, scene->mMeshes[a]->mNormals[b].z);
				newMesh.normal.push_back(normalCoords);
				hasNormals = true;
			}

			if (scene->mMeshes[a]->HasTextureCoords(0))
			{
				VEC2 textureCoords = VEC2(scene->mMeshes[a]->mTextureCoords[0][b].x, scene->mMeshes[a]->mTextureCoords[0][b].y);
				newMesh.textureMap.push_back(textureCoords);
			}

			currentVertex++;
		}

		newModel->meshes.push_back(newMesh);
	}

	for (int m = 0; m < newModel->meshes.size(); m++) {
		for (unsigned int i = 0; i < newModel->meshes[m].vertex.size(); i++) {
			newModel->meshes[m].edge.push_back(i);
	
		}	
	}

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		for (int j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
		{
			newModel->meshes[i].face.push_back(scene->mMeshes[i]->mFaces[j].mNumIndices);
		}
	}

	InsertModel(_name, newModel);
}


ResourceHandle<Model> ModelManager::InsertModel(const STRING& _name, Model* _model)
{
	ResourceHandle<Model> result(-1);

	// Check if the resource name is already in use
	result = _modelResources.Get(_name);
	if (!result.IsNull()) {
		return result;
	}
	
	result = _modelResources.Add(_name, _model);
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
