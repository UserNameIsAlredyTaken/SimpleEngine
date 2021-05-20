#pragma once
#include <string>

#include "BaseComponent.h"

class MoveComponent : public BaseComponent
{
public:
    MoveComponent(GameObject* gameObject);
    void Update(const GameTimer& gt) override;
    
};
