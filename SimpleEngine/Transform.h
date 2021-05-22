#pragma once
#include <DirectXMath.h>



class GameObject;
using namespace DirectX;
class Transform
{
public:
    Transform(XMFLOAT3 pos = {0, 0, 0}, XMFLOAT3 rot = {0, 0, 0}, XMFLOAT3 scale = {1, 1, 1});
    

    XMFLOAT3 GetPosition();
    XMFLOAT3 GetRotation();
    XMFLOAT3 GetScale();

    XMVECTOR Transform::GetWorldPosition();
    XMMATRIX Transform::GetWorldRotation(); //returns rotation matrx
    XMVECTOR Transform::GetWorldScale();

    
    void SetPosition(XMFLOAT3 pos);
    void SetRotation(XMFLOAT3 rot);
    void SetScale(XMFLOAT3 scale);

    void ChangePosition(float x, float y, float z);

    void SetOwner(GameObject* go);

private:
    XMFLOAT3 Position;
    XMFLOAT3 Rotation; //Radians
    XMFLOAT3 Scale;
    GameObject* Owner;
};
