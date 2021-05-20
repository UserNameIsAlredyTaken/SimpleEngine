#pragma once
#include "../Common/GameTimer.h"
#include <cstdio>
#include <memory>

class GameObject;

class BaseComponent
{
protected:
    GameObject* gameObject;

public:
    BaseComponent(GameObject* gameObject);
    virtual void Update(const GameTimer& gt);    
};

inline BaseComponent::BaseComponent(GameObject* gameObject) : gameObject(gameObject)
{
}

inline void BaseComponent::Update(const GameTimer& gt)
{
    printf("BaseComponentUpdate\n");
}
