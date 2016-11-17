#include "ModelManager.h"
#include "Debug.h"

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
	_modelResources.EmptyResourceMap();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

hBOOL ModelManager::LoadOBJModel(const STRING & path, VECTOR(VEC3)& out_vertices, VECTOR(VEC2)& out_uvs, VECTOR(VEC3)& out_normals)
{
	VECTOR(hUINT) vertexIndices, uvIndices, normalIndices;
	VECTOR(VEC3) temp_vertices;
	VECTOR(VEC2) temp_uvs;
	VECTOR(VEC3) temp_normals;


	FILE * file = fopen(path.c_str(), "r");
	if (file == NULL) {
		Debug::ConsoleError("Impossible to open the file! Are you in the right path?", __FILE__, __LINE__);
		GETCHAR();
		return false;
	}

	while (1) {

		hCHAR lineHeader[128];
		// read the first word of the line
		hINT res = fscanf_s(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		// Vertices
		if (strcmp(lineHeader, "v") == 0) {
			VEC3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		// Vertex textures
		else if (strcmp(lineHeader, "vt") == 0) {
			VEC2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		// Vertex normals
		else if (strcmp(lineHeader, "vn") == 0) {
			VEC3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		// Faces
		else if (strcmp(lineHeader, "f") == 0) {
			STRING vertex1, vertex2, vertex3;
			hUINT vertexIndex[3], uvIndex[3], normalIndex[3];
			hINT matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				Debug::ConsoleError("File can't be read by our simple parser :-( Try exporting with other options\n", __FILE__, __LINE__);
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
			hCHAR stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (hUINT i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		hUINT vertexIndex = vertexIndices[i];
		hUINT uvIndex = uvIndices[i];
		hUINT normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		VEC3 vertex = temp_vertices[vertexIndex - 1];
		VEC2 uv = temp_uvs[uvIndex - 1];
		VEC3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}

	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ResourceHandle<Model> ModelManager::LoadModel(const STRING& _name, const STRING& _filePath) 
{
	ResourceHandle<Model> result(-1);
	return result;
}


ResourceHandle<Model> ModelManager::LoadModel(const STRING& _name, Model* _model)
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

Model * ModelManager::GetModel(ResourceHandle<Model>& _handle)
{
	return _modelResources.Get(_handle);
}

