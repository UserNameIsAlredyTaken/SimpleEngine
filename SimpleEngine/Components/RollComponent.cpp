#pragma once
#include "RollComponent.h"
#include "../GameObject.h"

RollComponent::RollComponent(GameObject* gameObject) : BaseComponent(gameObject)
{
}

void RollComponent::Start()
{
    inputManager = gameObject->GetComponent<InputComponent>();
}

void RollComponent::Update(const GameTimer& gt)
{
    if(inputManager->GetForward())
        printf("FORWARD!!!\n");
}
