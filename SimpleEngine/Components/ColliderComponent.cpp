#pragma once
#include "ColliderComponent.h"

#include "../GameObject.h"

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

    // printf("FRAME:\n");
     for(int i = 0; i < Colliders.size(); ++i)
     {
         for(int j = i + 1; j < Colliders.size(); ++j)
         {
             ColliderComponent* collider1 = Colliders[i];
             ColliderComponent* collider2 = Colliders[j];

             if(collider1->GetGameObject()->IsParent(collider2->GetGameObject()) ||
                 collider2->GetGameObject()->IsParent(collider1->GetGameObject()))
                     return;
             
             XMFLOAT4 distanceVector; // distance is replicated to each element
             XMStoreFloat4(&distanceVector, XMVector3Length(collider1->gameObject->GetWorldPosition() - collider2->gameObject->GetWorldPosition()));
             float distance = distanceVector.x;
             
             if(distance <= collider1->radius + collider2->radius)
             {
                 collider1->OnCollide(collider2);
                 collider2->OnCollide(collider1);                 
             }
         }        
     }
}

void ColliderComponent::Update(const GameTimer& gt)
{
}
