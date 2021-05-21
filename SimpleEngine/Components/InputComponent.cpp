﻿#pragma once
#include "InputComponent.h"
#include "../GameObject.h"

InputComponent::InputComponent(GameObject* gameObject) : BaseComponent(gameObject)
{
}

void InputComponent::Update(const GameTimer& gt)
{
    if(GetAsyncKeyState(forwardKey) & 0x8000)
    	forwardValue = 1;
    else if(GetAsyncKeyState(backKey) & 0x8000)  
    	forwardValue = -1;
    else
        forwardValue = 0;

    if(GetAsyncKeyState(rightKey) & 0x8000)
        rightValue = 1;
    else if(GetAsyncKeyState(leftKey) & 0x8000)
        rightValue = -1;
    else
        rightValue = 0;
}

float InputComponent::GetForward()
{
    return forwardValue;
}

float InputComponent::GetRight()
{
    return rightValue;
}
