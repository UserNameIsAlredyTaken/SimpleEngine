﻿#pragma once
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
             XMStoreFloat4(&distanceVector, XMVector3Length(collider1->gameObject->LocalTransform.GetWorldPosition() - collider2->gameObject->LocalTransform.GetWorldPosition()));
             float distance = distanceVector.x;

            float collider1Radius = collider1->radius * XMVectorGetX(collider1->GetGameObject()->LocalTransform.GetWorldScale()); //CHECKS ONLY X COORDINATE!!
            float collider2Radius = collider2->radius * XMVectorGetX(collider2->GetGameObject()->LocalTransform.GetWorldScale()); //CHECKS ONLY X COORDINATE!!
             
             if(distance <= collider1Radius + collider2Radius)
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
