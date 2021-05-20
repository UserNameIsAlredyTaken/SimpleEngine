#pragma once
#include "../Common/GameTimer.h"
#include <cstdio>

class BaseComponent
{
public:
    virtual void Update(const GameTimer& gt);    
};

inline void BaseComponent::Update(const GameTimer& gt)
{
    printf("BaseComponentUpdate\n");
}
