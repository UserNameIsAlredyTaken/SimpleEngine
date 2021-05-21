#pragma once
#include "BaseComponent.h"
#include "InputComponent.h"

class RollComponent : public BaseComponent
{
private:
    InputComponent* inputManager;

    float rollSpeed = 4;
    
public:
    RollComponent(GameObject* gameObject);
    void Start() override;
    void Update(const GameTimer& gt) override;
    
};
