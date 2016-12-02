#include "MeshComponent.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "StandardShader.h"
#include "Debug.h"
#include "GameObject.h"
#include "Scene.h"

#define BUFFER_OFFSET(i) ((void*)(i))

MeshComponent::MeshComponent(GameObject* g, ShaderProgram* _shader, const STRING& _model)
	: Component(g, COMPONENT_TYPE::Renderable)
{
	shader = _shader;
	SetEnabled(true);
	
	GetModel(_model);
	program = _shader->GetProgramID();

	shader->UseShader();

	GLuint buffers[2];
	glGenBuffers(2, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertex.size() * sizeof(VEC3), &mesh->vertex[0], GL_STATIC_DRAW);
	glBindAttribLocation(program, 0, "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, mesh->uvs.size() * sizeof(VEC2), &mesh->uvs[0], GL_STATIC_DRAW);
	glBindAttribLocation(program, 1, "vTexCoord");
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBufferData(GL_ARRAY_BUFFER, mesh->normals.size() * sizeof(VEC3), &mesh->normals[0], GL_STATIC_DRAW);
	//glBindAttribLocation(program, 2, "vNormal");
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//glEnableVertexAttribArray(2);

	textureSampler = glGetUniformLocation(program, "myTextureSampler");
	glUniform1i(textureSampler, 0);
}

MeshComponent::~MeshComponent()
{
	// NOTE: Don't have to delete the model or texture here
	// the managers will do that for us
	//glDeleteBuffers(2, buffers);
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

void MeshComponent::Render()
{
	StandardShader* stdShader = STANDARD_SHADER;
	
	MATRIX4 transformMat = parentGmObj->ToMat4();

	glProgramUniformMatrix4fv(program, stdShader->model_Location, 1, GL_FALSE, &transformMat[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, mesh->vertex.size());
}