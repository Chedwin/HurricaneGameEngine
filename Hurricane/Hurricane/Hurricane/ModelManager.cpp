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
	//glGenBuffers(NUMBER_OF_BUFFERS, Buffers);

	//// Verties
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[Buffer_Type::VERTEX_BUFFER]);
	//glVertexAttribPointer(Attribute_Type::VERTEX_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//glEnableVertexAttribArray(Attribute_Type::VERTEX_ATTRIBUTE);

	//// Textures
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[Buffer_Type::TEXTURE_BUFFER]);
	//glVertexAttribPointer(Attribute_Type::TEXTURE_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//glEnableVertexAttribArray(Attribute_Type::TEXTURE_ATTRIBUTE);

	//// Normals (i.e. Lights)
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[Buffer_Type::NORMAL_BUFFER]);
	//glVertexAttribPointer(Attribute_Type::NORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//glEnableVertexAttribArray(Attribute_Type::NORMAL_ATTRIBUTE);

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

	//Debug::ConsoleLog("NumVertices: " + TO_STRING(totalVerts));

	Model* newModel = new Model();
	newModel->SetModelName(_name);

	const aiMesh* mesh = scene->mMeshes[0];

	// Fill vertices positions
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D pos = mesh->mVertices[i];
		newModel->mesh.vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
	}

	// Fill vertices texture coordinates
	for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
		aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		newModel->mesh.uvs.push_back(glm::vec2(UVW.x, UVW.y));
	}

	// Fill vertices normals
	for (unsigned int i = 0; i<mesh->mNumVertices; i++) {
		aiVector3D n = mesh->mNormals[i];
		newModel->mesh.normals.push_back(glm::vec3(n.x, n.y, n.z));
	}

	// Fill face indices
	for (unsigned int i = 0; i<mesh->mNumFaces; i++) {
		// Assume the model has only triangles.
		newModel->mesh.indices.push_back(mesh->mFaces[i].mIndices[0]);
		newModel->mesh.indices.push_back(mesh->mFaces[i].mIndices[1]);
		newModel->mesh.indices.push_back(mesh->mFaces[i].mIndices[2]);
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