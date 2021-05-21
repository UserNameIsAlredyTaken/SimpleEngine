#pragma once
#include "BaseComponent.h"

class CameraComponent : public BaseComponent
{
public:
    CameraComponent(GameObject* gameObject);
    void Update(const GameTimer& gt) override;
    
};
