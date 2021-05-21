﻿#pragma once
#include "BaseComponent.h"
#include "InputComponent.h"

class RollComponent : public BaseComponent
{
private:
    InputComponent* inputManager;
    
public:
    RollComponent(GameObject* gameObject);
    void Start() override;
    void Update(const GameTimer& gt) override;
    
};
