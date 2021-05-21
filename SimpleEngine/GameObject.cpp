#include "GameObject.h"



GameObject::GameObject(/*GameObject* parent, */Material* mat, MeshGeometry* geo, std::string subgeoName, Transform transform) :
ParentGameObject(nullptr),
GeometryName(subgeoName),
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

    //add self to parents child list
    // if(parent)
    //     parent->AddChild(this);
    
}

GameObject::GameObject(/*GameObject* parent, */Material* mat, MeshGeometry* geo, std::string subgeoName) :
GameObject(/*parent, */mat, geo, subgeoName,
    Transform(
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f})
        )
{
}

void GameObject::Update(const GameTimer& gt)
{
    for(auto& component : Components)
    {
        component->Update(gt);
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

XMFLOAT4X4 GameObject::GetGlobalWorldMatrix()
{
    //recursively calculates world matrix from parents chain
    XMMATRIX parentMatrix = ParentGameObject ? XMLoadFloat4x4(&ParentGameObject->GetGlobalWorldMatrix()) : XMLoadFloat4x4(&MathHelper::Identity4x4());
    
    XMFLOAT4X4 result;
    //calclate world matrix from position, rotation and scale
    XMStoreFloat4x4(&result,
        XMMatrixTranslation(LocalTransform.GetPosition().x, LocalTransform.GetPosition().y, LocalTransform.GetPosition().z) *
        XMMatrixRotationX(LocalTransform.GetRotation().x) *
        XMMatrixRotationY(LocalTransform.GetRotation().y) *
        XMMatrixRotationZ(LocalTransform.GetRotation().z) *
        XMMatrixScaling(LocalTransform.GetScale().x, LocalTransform.GetScale().y, LocalTransform.GetScale().z) *
        parentMatrix
        );
    return result;
}

