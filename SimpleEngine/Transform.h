#pragma once
#include <DirectXMath.h>

using namespace DirectX;
class Transform
{
public:
    Transform(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);
    Transform(XMFLOAT3 pos);

    XMFLOAT3 GetPosition();
    XMFLOAT3 GetRotation();
    XMFLOAT3 GetScale();
    
    void SetPosition(XMFLOAT3 pos);
    void SetRotation(XMFLOAT3 rot);
    void SetScale(XMFLOAT3 scale);    

private:
    XMFLOAT3 Position;
    XMFLOAT3 Rotation;
    XMFLOAT3 Scale;    
};
