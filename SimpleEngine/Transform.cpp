#include "Transform.h"
#include "GameObject.h"

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

XMVECTOR Transform::GetWorldPosition()
{
    XMVECTOR scale, rot_quat, trans;
    XMMatrixDecompose(&scale, &rot_quat, &trans, XMLoadFloat4x4(&Owner->Ritem->World));
    return trans;
}

XMMATRIX Transform::GetWorldRotation()
{
    XMVECTOR newScale, newRot_quat, newTrans;
    XMMatrixDecompose(&newScale, &newRot_quat, &newTrans, XMLoadFloat4x4(&Owner->Ritem->World));
    XMMATRIX rotMatrix = XMMatrixRotationQuaternion(newRot_quat);
    return rotMatrix;
}

XMVECTOR Transform::GetWorldScale()
{
    XMVECTOR scale, rot_quat, trans;
    XMMatrixDecompose(&scale, &rot_quat, &trans, XMLoadFloat4x4(&Owner->Ritem->World));
    return scale;
}


void Transform::SetPosition(XMFLOAT3 pos)
{
    Position = pos;    
    Owner->RefreshWorldMatrix();
}

void Transform::SetRotation(XMFLOAT3 rot)
{
    Rotation = rot;    
    Owner->RefreshWorldMatrix();
}

void Transform::SetScale(XMFLOAT3 scale)
{
    Scale = scale;
    Owner->RefreshWorldMatrix();
}

void Transform::ChangePosition(float x, float y, float z)
{
    XMFLOAT3 oldPos = GetPosition();
    SetPosition({
        oldPos.x + x,
        oldPos.y + y,
        oldPos.z + z});
}



void Transform::SetOwner(GameObject* go)
{
    Owner = go;
}

