#include "GarabberComponent.h"
#include "../GameObject.h"

GarabberComponent::GarabberComponent(GameObject* gameObject) : BaseComponent(gameObject)
{
}

void GarabberComponent::Start()
{
    collider = gameObject->GetComponent<ColliderComponent>();
}
