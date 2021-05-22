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
    if(inputManager->GetRight() != 0 ||  inputManager->GetForward() != 0)
    {
        XMVECTOR rotationAxis = {-inputManager->GetRight(),0,-inputManager->GetForward()};
        XMVECTOR newScale, newRot_quat, newTrans;
        XMMatrixDecompose(&newScale, &newRot_quat, &newTrans, XMLoadFloat4x4(&gameObject->Ritem->World));

        XMFLOAT3 pos;
        XMStoreFloat3(&pos, newTrans);
        gameObject->LocalTransform.SetPosition(pos);


        XMMATRIX rotMatrix = XMMatrixRotationQuaternion(newRot_quat);
        float x;
        float y;
        float z;
        ExtractPitchYawRollFromXMMatrix(&x, &y, &z, &(rotMatrix * XMMatrixRotationAxis(rotationAxis,gt.DeltaTime() * rollSpeed)));
        gameObject->LocalTransform.SetRotation({x,y,z});

        XMFLOAT3 scale;
        XMStoreFloat3(&scale, newScale);
        gameObject->LocalTransform.SetScale(scale); //TODO: bug if parent has non uniform scale

    }
    
    XMFLOAT3 oldPos = gameObject->LocalTransform.GetPosition();
    gameObject->LocalTransform.SetPosition({
        oldPos.x + inputManager->GetForward() * gt.DeltaTime() * rollSpeed,
        oldPos.y,
        oldPos.z - inputManager->GetRight() * gt.DeltaTime() * rollSpeed});

    
    gameObject->RefreshWorldMatrix();
    

    // XMFLOAT3 oldRot = gameObject->LocalTransform.GetRotation();
    // gameObject->LocalTransform.SetRotation({
    //     oldRot.x + inputManager->GetForward() * gt.DeltaTime() * rollSpeed,
    //     oldRot.y + inputManager->GetRight() * gt.DeltaTime() * rollSpeed,
    //     oldRot.z});
    //
    // gameObject->RefreshWorldMatrix(); 

    
    // if(inputManager->GetRight() != 0 ||
    //     inputManager->GetForward() != 0)
    // {
    //     // XMVECTOR rotationAxis = {inputManager->GetRight(),0,inputManager->GetForward()};
    //     // printf("%f,%f,%f\n", inputManager->GetRight(),0,inputManager->GetForward());
    //     XMVECTOR rotationAxis = {0,0,1};
    //
    //
    //     XMStoreFloat4x4(&gameObject->Ritem->World,
    //         XMMatrixRotationAxis(rotationAxis,gt.DeltaTime() * rollSpeed) *
    //         XMLoadFloat4x4(&gameObject->Ritem->World));
    //     gameObject->Ritem->NumFramesDirty = gNumFrameResources;
    // }
    
    
    // XMMATRIX world = XMLoadFloat4x4(&gameObject->Ritem->World);
    //
    // XMStoreFloat4x4(&gameObject->Ritem->World, world * XMMatrixRotationAxis({1,0,0, 0},inputManager->GetRight() * gt.DeltaTime() * rollSpeed));
    // XMStoreFloat4x4(&gameObject->Ritem->World, world * XMMatrixRotationAxis({0,0,1, 0},inputManager->GetForward() * gt.DeltaTime() * rollSpeed));
    // gameObject->Ritem->NumFramesDirty = gNumFrameResources;

    // XMVECTOR origin = XMLoadFloat3(&gameObject->GetWorldPosition());
    // auto rotation = XMQuaternionRotationRollPitchYaw(inputManager->GetRight() * gt.DeltaTime() * rollSpeed, 0, inputManager->GetForward() * gt.DeltaTime() * rollSpeed);
    //
    // auto localMatrix = XMMatrixAffineTransformation({1,1,1}, /*gameObject->GetWorldPosition()*/{0,0,0}, rotation, {0,0,0});
    // auto localMatrix = XMMatrixRotationRollPitchYawFromVector({inputManager->GetRight() * gt.DeltaTime() * rollSpeed, 0, inputManager->GetForward() * gt.DeltaTime() * rollSpeed});
    
    // XMFLOAT3 oldRot = gameObject->LocalTransform.GetRotation();
    // XMVECTOR oldRotNeg = XMLoadFloat3(&oldRot) * -1;
    // XMVECTOR xAxis = XMVector3TransformNormal(XMVectorSet(1,0,0, 0), XMMatrixRotationRollPitchYawFromVector(oldRotNeg));
    // XMVECTOR zAxis = XMVector3TransformNormal(XMVectorSet(0,0,1, 0), XMMatrixRotationRollPitchYawFromVector(oldRotNeg));
    // float x1;
    // float y1;
    // float z1;
    // ExtractPitchYawRollFromXMMatrix(&x1, &y1, &z1,
    //     &XMMatrixRotationAxis(xAxis,inputManager->GetRight() * gt.DeltaTime() * rollSpeed));
    // float x2;
    // float y2;
    // float z2;
    // ExtractPitchYawRollFromXMMatrix(&x2, &y2, &z2,
    //     &XMMatrixRotationAxis(zAxis,inputManager->GetForward() * gt.DeltaTime() * rollSpeed));
    //
    // gameObject->LocalTransform.SetRotation({
    //     oldRot.x - x1 - x2,
    //     oldRot.y,
    //     oldRot.z - z1 - z2});
    
    // gameObject->RefreshWorldMatrix();      
}
