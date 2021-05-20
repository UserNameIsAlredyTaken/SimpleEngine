#include "GameObject.h"

Transform::Transform(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale) :
Position(pos),
Rotation(rot),
Scale(scale)
{
}

XMFLOAT4X4 Transform::GetGlobalWorldMatrix()
{
    XMFLOAT4X4 result;
    XMStoreFloat4x4(&result, XMMatrixTranslation(Position.x, Position.y, Position.z));
    return result;
}

GameObject::GameObject(GameObject* parent, Material* mat, MeshGeometry* geo, std::string subgeoName, Transform transform) :
ParentGameObject(parent),
GeometryName(subgeoName),
LocalTransform(transform)
{
    auto ritem = std::make_shared<RenderItem>();
    ritem->World = MathHelper::Identity4x4();
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

GameObject::GameObject(GameObject* parent, Material* mat, MeshGeometry* geo, std::string subgeoName) :
GameObject(parent, mat, geo, subgeoName,
    Transform(
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f})
        )
{
}

void GameObject::Update(const GameTimer& gt)
{
}

void GameObject::AddChild(GameObject* child)
{
    ChildrenGameOjects.push_back(child);
}

