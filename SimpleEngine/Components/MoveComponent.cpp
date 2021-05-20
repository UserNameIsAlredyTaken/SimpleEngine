#include "MoveComponent.h"

#include "../GameObject.h"


MoveComponent::MoveComponent(GameObject* gameObject) : BaseComponent(gameObject)
{
}

void MoveComponent::Update(const GameTimer& gt)
{
    XMFLOAT3 oldPos = gameObject->LocalTransform.GetPosition();
    gameObject->LocalTransform.SetPosition({oldPos.x, oldPos.y + gt.DeltaTime() * 2, oldPos.z});
    
    // XMFLOAT3 oldRot = gameObject->LocalTransform.GetRotation();
    // gameObject->LocalTransform.SetRotation({oldRot.x + gt.DeltaTime() * 2, oldRot.y + gt.DeltaTime() * 2, oldRot.z + gt.DeltaTime() * 2});

    gameObject->RefreshWorldMatrix();    
}
