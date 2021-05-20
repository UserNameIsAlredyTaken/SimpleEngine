#pragma once
#include <DirectXMath.h>

using namespace DirectX;
class Transform
{
public:
    Transform(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);

    XMFLOAT3 GetPosition();
    XMFLOAT3 GetRotation();
    XMFLOAT3 GetScale();
    
    void SetPosition(XMFLOAT3 pos);
    void SetRotation(XMFLOAT3 rot);
    void SetScale(XMFLOAT3 scale);
    
    XMFLOAT4X4 GetGlobalWorldMatrix();

private:
    XMFLOAT3 Position;
    XMFLOAT3 Rotation;
    XMFLOAT3 Scale;    
};
