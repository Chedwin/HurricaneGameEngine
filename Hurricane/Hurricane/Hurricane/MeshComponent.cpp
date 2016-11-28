#include "MeshComponent.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "StandardShader.h"
#include "Debug.h"
#include "GameObject.h"

//VECTOR(MeshComponent*) MeshComponent::renderableComponents;

MeshComponent::MeshComponent(GameObject* g, ShaderProgram* _shader)
	: Component(g, COMPONENT_TYPE::Renderable)
{
	shader = _shader;
	SetEnabled(true);
	//renderableComponents.push_back(this);
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

	//Texture* text = GetTexture(textureName);
	//if (!texture) {
	//	return;
	//}

	//if (!shader) {
	//	return;
	//}

	/*shader->UseShader(); */
	StandardShader* stdShader = STANDARD_SHADER;
	//stdShader->UseShader();

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);

	MATRIX4 transformMat = parentGmObj->ToMat4();
	glProgramUniformMatrix4fv(stdShader->GetProgramID(), stdShader->model_Location, 1, GL_FALSE, &transformMat[0][0]);


	MATRIX4 rotMat = glm::mat4_cast(parentGmObj->transform.rotation);
	glProgramUniformMatrix4fv(stdShader->GetProgramID(), stdShader->rotation_Location, 1, GL_FALSE, &rotMat[0][0]);

	for (int m = 0; m < model->meshes.size(); m++)
	{
		////Get Texture
		//if (m < _textures.size() && _textures[m])
		//{
		//	glBindTexture(GL_TEXTURE_2D, _textures[m]->address);
		//}
		//else if (_textures[0])
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture->address);

		//glDrawArrays(GL_TRIANGLES, model->meshes[0].edge[0], model->meshes[0].vertex.size());
	}

	glDrawArrays(GL_LINE_STRIP, 0, MODEL_MANAGER->masterVectorList.size());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void MeshComponent::DrawRenderables() 
//{
//	for (int i = 0; i < renderableComponents.size(); i++)
//	{
//		if (renderableComponents[i]->isEnabled)
//		{
//			renderableComponents[i]->Render();
//		}
//	}
//}