#pragma once
#include "BaseComponent.h"
#include "ColliderComponent.h"

class GarabberComponent : public BaseComponent
{
private:
    ColliderComponent* collider;
public:
    GarabberComponent(GameObject* gameObject);
    void Start() override;
    void Update(const GameTimer& gt) override;    
    
};
