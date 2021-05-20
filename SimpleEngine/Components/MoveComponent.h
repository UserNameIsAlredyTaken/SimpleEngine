#pragma once
#include <string>

#include "BaseComponent.h"

class MoveComponent : public BaseComponent
{
public:
    void Update(const GameTimer& gt) override;
    
};
