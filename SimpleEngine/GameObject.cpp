#pragma once
#include "GameObject.h"


GameObject::GameObject(Material* mat, MeshGeometry* geo, std::string subgeoName, std::string goName, Transform transform) :
ParentGameObject(nullptr),
GeometryName(subgeoName),
Name(goName),
LocalTransform(transform)
{
    auto ritem = std::make_shared<RenderItem>();
    ritem->World = GetGlobalWorldMatrix();
    ritem->TexTransform = MathHelper::Identity4x4();
    ritem->ObjCBIndex = cbIndex++;
    ritem->Mat = mat;
    ritem->Geo = geo;
    ritem->PrimitiveType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    ritem->IndexCount = geo->DrawArgs[subgeoName].IndexCount;
    ritem->StartIndexLocation = geo->DrawArgs[subgeoName].StartIndexLocation;
    ritem->BaseVertexLocation = geo->DrawArgs[subgeoName].BaseVertexLocation;

    Ritem = std::move(ritem);
}


void GameObject::Update(const GameTimer& gt)
{
    for(auto& component : Components)
    {
        component->Update(gt);
    }
}

void GameObject::Start()
{
    for(auto& component : Components)
    {
        component->Start();
    }
}

void GameObject::AddChild(GameObject* child)
{
    if(CheckVectorContains<GameObject>(ChildrenGameOjects, child))
            ChildrenGameOjects.push_back(child);
    
    if(child->ParentGameObject != this) 
        child->SetParent(this);    
}

void GameObject::SetParent(GameObject* parent)
{
    if(ParentGameObject != parent) 
        ParentGameObject = parent;

    if(CheckVectorContains<GameObject>(parent->ChildrenGameOjects, this))
        parent->AddChild(this);

    XMFLOAT3 oldPos = LocalTransform.GetPosition();
    XMFLOAT3 parentPos = parent->LocalTransform.GetPosition();    
    LocalTransform.SetPosition({oldPos.x - parentPos.x, oldPos.y - parentPos.y, oldPos.z - parentPos.z});

    XMFLOAT3 oldRot = LocalTransform.GetRotation();
    XMFLOAT3 parentRot = parent->LocalTransform.GetRotation();
    XMFLOAT3 n = {oldRot.x - parentRot.x, oldRot.y - parentRot.y, oldRot.z - parentRot.z};
    LocalTransform.SetRotation({oldRot.x - parentRot.x, oldRot.y - parentRot.y, oldRot.z - parentRot.z});
    
    RefreshWorldMatrix();
}


void GameObject::RefreshWorldMatrix()
{
    Ritem->World = GetGlobalWorldMatrix(); //recalculates world matrix for this game objects and stores it in assosiated RenderItem
    //set dirty flag for all frame resources
    //this forces to ubdate objects constant buffer 
    Ritem->NumFramesDirty = gNumFrameResources; 

    for(auto& child : ChildrenGameOjects)
        child->RefreshWorldMatrix();
}

XMVECTOR GameObject::GetWorldPosition()
{
    XMVECTOR scale, rot_quat, trans;
    XMMatrixDecompose(&scale, &rot_quat, &trans, XMLoadFloat4x4(&Ritem->World));
    return trans;
}


XMFLOAT4X4 GameObject::GetGlobalWorldMatrix()
{
    //recursively calculates world matrix from parents chain
    XMMATRIX parentMatrix = ParentGameObject ? XMLoadFloat4x4(&ParentGameObject->GetGlobalWorldMatrix()) : XMLoadFloat4x4(&MathHelper::Identity4x4());

    auto origin = XMVectorSet(0, 0, 0, 0);
    auto scale = XMVectorSet(LocalTransform.GetScale().x, LocalTransform.GetScale().y, LocalTransform.GetScale().z, 0);
    auto translation = XMVectorSet(LocalTransform.GetPosition().x, LocalTransform.GetPosition().y, LocalTransform.GetPosition().z, 0);
    auto rotation = XMQuaternionRotationRollPitchYaw(LocalTransform.GetRotation().x, LocalTransform.GetRotation().y, LocalTransform.GetRotation().z);
    
    auto localMatrix = XMMatrixAffineTransformation(scale, origin, rotation, translation);
    
    XMFLOAT4X4 result;
    XMStoreFloat4x4(&result,localMatrix * parentMatrix);
    return result;
}

