#pragma once
#include "ColliderComponent.h"

std::vector<ColliderComponent*> ColliderComponent::Colliders;

ColliderComponent::ColliderComponent(GameObject* gameObject) : BaseComponent(gameObject)
{
    Colliders.push_back(this);
}

void ColliderComponent::Start()
{
    OnCollide.connect(boost::bind(&ColliderComponent::V, this));
    OnCollide();
}

void ColliderComponent::UpdateCollisionSystem()
{
    for(auto& collider : Colliders)
    {
        printf("collider");
    }
}

void ColliderComponent::Update(const GameTimer& gt)
{
}

void ColliderComponent::V()
{
    printf("called");
}
