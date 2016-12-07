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
	// EMPTY
}

ModelManager::~ModelManager()
{
	// Delete all models
	ClearAllModels();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ASSIMP MODEL LOADING (i.e. fbx, obj, 3ds, etc.)
void ModelManager::LoadAssimpModel(const STRING& _name, const STRING& _filePath) 
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
		aiProcess_SortByPType 
	);

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

	Debug::ConsoleLog("NumVertices: " + TO_STRING(totalVerts));

	Model* model = new Model();
	model->SetModelName(_name);

	const aiMesh* thisMesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

	// Fill vertices positions
	//model->vertex.reserve(thisMesh->mNumVertices);
	for (unsigned int i = 0; i < thisMesh->mNumVertices; i++) {
		// Vertices
		aiVector3D pos = thisMesh->mVertices[i];
		model->vertex.push_back(VEC3(pos.x, pos.y, pos.z));

		// Texture coordinates (UV map)
		aiVector3D UVW = thisMesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
		model->uvs.push_back(VEC2(UVW.x, UVW.y));

		// Normals
		aiVector3D n = thisMesh->mNormals[i];
		model->normals.push_back(VEC3(n.x, n.y, n.z));
	}

	//// Fill face indices
	//indices.reserve(3 * thisMesh->mNumFaces);
	//for (unsigned int i = 0; i<thisMesh->mNumFaces; i++) {
	//	// Assume the model has only triangles.
	//	indices.push_back(thisMesh->mFaces[i].mIndices[0]);
	//	indices.push_back(thisMesh->mFaces[i].mIndices[1]);
	//	indices.push_back(thisMesh->mFaces[i].mIndices[2]);
	//}
	
	InsertModel(_name, model);
}

/////////////////////////////////////////////////////

// Strictly load OBJ files
// Written w/o 3rd party APIs
hBOOL ModelManager::LoadOBJ(const STRING& _name, const STRING& _filePath) 
{
	printf("Loading OBJ file %s...\n", _filePath.c_str());

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<VEC3> temp_vertices;
	std::vector<VEC2> temp_uvs;
	std::vector<VEC3> temp_normals;


	FILE * file = fopen(_filePath.c_str(), "r");
	if (file == NULL) {
		Debug::ConsoleError("CANNONT OPEN FILE: " + _filePath, __FILE__, __LINE__);
		GETCHAR();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			VEC3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			VEC2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			VEC3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// Create a new temp model object to be store in the model manager
	Model* model = new Model();
	model->SetModelName(_name);

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		VEC3 vertex = temp_vertices[vertexIndex - 1];
		VEC2 uv = temp_uvs[uvIndex - 1];
		VEC3 normal = temp_normals[normalIndex - 1];



		// Put the attributes in buffers
		model->vertex.push_back(vertex);
		model->uvs.push_back(uv);
		model->normals.push_back(normal);

	}

	InsertModel(_name, model);
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MODEL MANAGEMENT STUFF

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