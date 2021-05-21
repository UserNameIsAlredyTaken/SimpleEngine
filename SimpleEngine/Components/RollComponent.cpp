#include "RollComponent.h"
#include "../GameObject.h"

RollComponent::RollComponent(GameObject* gameObject) : BaseComponent(gameObject)
{
}

void RollComponent::Start()
{
    // inputManager = gameObject->GetComponent<InputComponent>();
    // inputManager = gameObject->GetComponent();
}

void RollComponent::Update(const GameTimer& gt)
{
    if(inputManager->GetForward())
        printf("FORWARD!!!\n");
}
