#include "MeshComponent.h"
#include "ModelManager.h"
#include "TextureManager.h"
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

	shader->UseShader(); 
}