﻿#include "Transform.h"

Transform::Transform(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale) :
Position(pos),
Rotation(rot),
Scale(scale)
{
}

XMFLOAT3 Transform::GetPosition()
{
    return Position;
}

XMFLOAT3 Transform::GetRotation()
{
    return Rotation;
}

XMFLOAT3 Transform::GetScale()
{
    return Scale;
}

void Transform::SetPosition(XMFLOAT3 pos)
{
    Position = pos;
}

void Transform::SetRotation(XMFLOAT3 rot)
{
    Rotation = rot;
}

void Transform::SetScale(XMFLOAT3 scale)
{
    Scale = scale;
}

