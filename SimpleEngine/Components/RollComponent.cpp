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
    gameObject->LocalTransform.ChangePosition(
        inputManager->GetForward() * gt.DeltaTime() * rollSpeed,
        0,
        -inputManager->GetRight() * gt.DeltaTime() * rollSpeed);

    //TODO: there is a bug if add this component to someones child
    XMVECTOR rotationAxis = {-inputManager->GetRight(),0,-inputManager->GetForward()};
    XMFLOAT3 temp;
    XMStoreFloat3(&temp, rotationAxis);    
    if(temp.x == 0 && temp.y == 0 && temp.z == 0)
        return;
    
    float x;
    float y;
    float z;
    ExtractPitchYawRollFromXMMatrix(&x, &y, &z, &(gameObject->LocalTransform.GetWorldRotation() * XMMatrixRotationAxis(rotationAxis, gt.DeltaTime() * rollSpeed)));
    gameObject->LocalTransform.SetRotation({x,y,z});
}
