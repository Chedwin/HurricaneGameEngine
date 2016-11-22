#include "MeshComponent.h"
#include "ModelManager.h"
#include "Debug.h"

MeshComponent::MeshComponent(GameObject* g, ShaderProgram* _shader)
	: Component(g, COMPONENT_TYPE::Renderable)
{
	shader = _shader;
	SetEnabled(true);
}

MeshComponent::~MeshComponent()
{
	// NOTE: Don't have to delete the model here
	// the model manager will do that for us
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Model* MeshComponent::GetModel(const STRING & _name)
{
	Model* m = MODEL_MANAGER->GetModel(_name);
	mesh = m;
	meshName = _name;
	return m;
}

Model* MeshComponent::GetModel(ResourceHandle<Model>& _handle)
{
	Model* m = MODEL_MANAGER->GetModel(_handle);
	return m;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MeshComponent::Render()
{
	Model* model = GetModel(meshName);
	if (!model) {
		return;
	}
	//COUT << model->GetModelName() << ENDL;
}