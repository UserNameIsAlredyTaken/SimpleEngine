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
    
    XMFLOAT3 oldPos = gameObject->LocalTransform.GetPosition();
    gameObject->LocalTransform.SetPosition({
        oldPos.x + inputManager->GetForward() * gt.DeltaTime() * rollSpeed,
        oldPos.y,
        oldPos.z - inputManager->GetRight() * gt.DeltaTime() * rollSpeed});
    
    gameObject->RefreshWorldMatrix();      
}
