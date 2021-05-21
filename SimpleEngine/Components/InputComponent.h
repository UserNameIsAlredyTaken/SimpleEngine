#pragma once
#include <string>
#include "BaseComponent.h"
#include "../Game.h"

class InputComponent : public BaseComponent
{
public:
    InputComponent(GameObject* gameObject);
    void Update(const GameTimer& gt) override;

    float GetForward();
    float GetRight();
    

private:
    int forwardKey = VK_UP;
    int backKey = VK_DOWN;
    int leftKey = VK_LEFT;
    int rightKey = VK_RIGHT;

    

    float forwardValue = 0;
    float rightValue = 0;
    
    
};