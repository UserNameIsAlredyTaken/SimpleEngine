#include "GameObject.h"

Transform::Transform(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale) :
Position(pos),
Rotation(rot),
Scale(scale)
{
}

GameObject::GameObject(GameObject* parent, std::string matName, std::string geoName, Transform transform) :
ParentGameObject(parent),
MaterialName(matName),
GeometryName(geoName),
LocalTransform(transform)
{
    // RenderItem ritem;
    // Ritem = std::move(&ritem);
}

GameObject::GameObject(GameObject* parent, std::string matName, std::string geoName) :
GameObject(parent, matName, geoName,
    Transform(
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}))
{
}

void GameObject::AddChild(GameObject* child)
{
    ChildrenGameOjects.push_back(child);
}

