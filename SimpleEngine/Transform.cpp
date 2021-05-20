#include "Transform.h"

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
    Scale = Scale;
}


XMFLOAT4X4 Transform::GetGlobalWorldMatrix()
{
    XMFLOAT4X4 result;
    XMStoreFloat4x4(&result,
        XMMatrixTranslation(Position.x, Position.y, Position.z) *
        XMMatrixRotationX(Rotation.x) *
        XMMatrixRotationY(Rotation.y) *
        XMMatrixRotationZ(Rotation.z) 
        );
    return result;
}
