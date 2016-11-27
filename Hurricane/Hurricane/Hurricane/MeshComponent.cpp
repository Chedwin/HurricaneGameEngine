#include "MeshComponent.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "Debug.h"

MeshComponent::MeshComponent(GameObject* g, ShaderProgram* _shader)
	: Component(g, COMPONENT_TYPE::Renderable)
{
	shader = _shader;
	SetEnabled(true);
	areBuffersInitialized = true;

	// Gen buffers here
	glGenBuffers(NUMBER_OF_BUFFERS, Buffers);

	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ModelManager::Buffer_Type::VERTEX_BUFFER]);
	glVertexAttribPointer(Attribute_Type::VERTEX_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(Attribute_Type::VERTEX_ATTRIBUTE);

	// Textures
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ModelManager::Buffer_Type::TEXTURE_BUFFER]);
	glVertexAttribPointer(Attribute_Type::TEXTURE_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(Attribute_Type::TEXTURE_ATTRIBUTE);

	// Normals (i.e. Lights)
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ModelManager::Buffer_Type::NORMAL_BUFFER]);
	glVertexAttribPointer(Attribute_Type::NORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(Attribute_Type::NORMAL_ATTRIBUTE);

	//PushModel();
}

MeshComponent::~MeshComponent()
{
	// NOTE: Don't have to delete the model or texture here
	// the managers will do that for us
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Model* MeshComponent::GetModel(const STRING & _name)
{
	Model* m = MODEL_MANAGER->GetModel(_name);
	if (m) {
		mesh = m;
		meshName = _name;
		return m;	
	}
	return nullptr;
}

Texture* MeshComponent::GetTexture(const STRING& _texture) 
{
	Texture* t = TEXTURE_MANAGER->GetTexture(_texture);
	if (t) {
		texture = t;
		textureName = _texture;
		return t;
	}
	return nullptr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshComponent::PushModel() 
{
	if (areBuffersInitialized) 
	{
		GLuint zero = 0;

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[ModelManager::Buffer_Type::VERTEX_BUFFER]);
		glClearBufferData(GL_ARRAY_BUFFER, GL_RGB32F, GL_RGB, GL_UNSIGNED_INT, &zero);

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[ModelManager::Buffer_Type::TEXTURE_BUFFER]);
		glClearBufferData(GL_ARRAY_BUFFER, GL_RG32F, GL_RG, GL_UNSIGNED_INT, &zero);

		glBindBuffer(GL_ARRAY_BUFFER, Buffers[ModelManager::Buffer_Type::NORMAL_BUFFER]);
		glClearBufferData(GL_ARRAY_BUFFER, GL_RGB32F, GL_RGB, GL_UNSIGNED_INT, &zero);
	}
	
	//glGenTextures(1, );
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, myCubeTexture->GetWidth(), myCubeTexture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, myCubeTexture->GetPixels());
	//
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//
	//glGenerateMipmap(GL_TEXTURE_2D);
}

void MeshComponent::RemoveModelFromGPU() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshComponent::Render()
{
	Model* model = GetModel(meshName);
	if (!model) {
		return;
	}

	Texture* text = GetTexture(textureName);
	if (!texture) {
		return;
	}

	if (!shader) {
		return;
	}

	shader->UseShader();

	//glProgramUniform3fv(shader->GetProgramID(), shader_->material_Location, 1, mat_);


	//glDrawArrays(GL_TRIANGLES, model->meshes[0].edge[0], model->meshes[0].vertex.size());
	//glDrawArrays(GL_TRIANGLES, 0, model->mesh.vertices.size());
}