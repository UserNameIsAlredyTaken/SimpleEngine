#pragma once
#include "BaseComponent.h"

class ColliderComponent : public BaseComponent
{
private:
    float radius = 1;
    
public:
    ColliderComponent(GameObject* gameObject);
    void Start() override;
    void Update(const GameTimer& gt) override;    
};