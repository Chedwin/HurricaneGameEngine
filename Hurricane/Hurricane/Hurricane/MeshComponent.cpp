#include "MeshComponent.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "StandardShader.h"
#include "Debug.h"

MeshComponent::MeshComponent(GameObject* g, ShaderProgram* _shader)
	: Component(g, COMPONENT_TYPE::Renderable)
{
	shader = _shader;
	SetEnabled(true);
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

	/*shader->UseShader(); */
	StandardShader* stdShader = STANDARD_SHADER;
	stdShader->UseShader();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	MATRIX4 model_view = MATRIX4(1.0f);
	glUniformMatrix4fv(stdShader->model_Location, 1, GL_FALSE, &model_view[0][0]);

	for (int m = 0; m < model->meshes.size(); m++)
	{
		////Get Texture
		//if (m < _textures.size() && _textures[m])
		//{
		//	glBindTexture(GL_TEXTURE_2D, _textures[m]->address);
		//}
		//else if (_textures[0])
		glBindTexture(GL_TEXTURE_2D, texture->address);


		glDrawArrays(GL_TRIANGLES, model->meshes[m].edge[0], model->meshes[m].vertex.size());
		//glDrawArrays(GL_TRIANGLES, 0, model->meshes[m].vertex.size());
	}
}