#pragma once
#include "ColliderComponent.h"

std::vector<ColliderComponent*> ColliderComponent::Colliders;

ColliderComponent::ColliderComponent(GameObject* gameObject) : BaseComponent(gameObject)
{
    Colliders.push_back(this);
}

void ColliderComponent::Start()
{
}

void ColliderComponent::UpdateCollisionSystem()
{
    for(auto& collider : Colliders)
    {        
        collider->OnCollide();
    }
}

void ColliderComponent::Update(const GameTimer& gt)
{
}
