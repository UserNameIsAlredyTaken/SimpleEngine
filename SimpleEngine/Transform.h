#pragma once
#include <DirectXMath.h>

using namespace DirectX;
class Transform
{
public:
    Transform(XMFLOAT3 pos = {0, 0, 0}, XMFLOAT3 rot = {0, 0, 0}, XMFLOAT3 scale = {1, 1, 1});
    

    XMFLOAT3 GetPosition();
    XMFLOAT3 GetRotation();
    XMFLOAT3 GetScale();

    
    void SetPosition(XMFLOAT3 pos);
    void SetRotation(XMFLOAT3 rot);
    void SetScale(XMFLOAT3 scale);    

private:
    XMFLOAT3 Position;
    XMFLOAT3 Rotation; //Radians
    XMFLOAT3 Scale;    
};
