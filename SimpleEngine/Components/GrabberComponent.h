#pragma once
#include "BaseComponent.h"

class ColliderComponent;
class GrabberComponent : public BaseComponent
{
private:
    ColliderComponent* collider;

    void Grabb();
public:
    GrabberComponent(GameObject* gameObject);
    void Start() override;
    void Update(const GameTimer& gt) override;    
    
};


