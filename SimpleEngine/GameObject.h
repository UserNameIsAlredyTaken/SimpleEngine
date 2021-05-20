#include <DirectXMath.h>
#include <vector>
#include "Game.h"

using namespace DirectX;

struct RenderItem
{
    RenderItem() = default;

    XMFLOAT4X4 World = MathHelper::Identity4x4();
    XMFLOAT4X4 TexTransform = MathHelper::Identity4x4();  
    
    int NumFramesDirty = gNumFrameResources;

    // Index into GPU constant buffer corresponding to the ObjectCB for this render item.
    UINT ObjCBIndex = -1;

    Material* Mat = nullptr;
    MeshGeometry* Geo = nullptr;

    D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

    // DrawIndexedInstanced parameters.
    UINT IndexCount = 0;
    UINT StartIndexLocation = 0;
    int BaseVertexLocation = 0;
};

struct Transform
{
    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Rotation;
    DirectX::XMFLOAT3 Scale;

    Transform(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale);
    XMFLOAT4X4 GetGlobalWorldMatrix();
};

class GameObject
{
public:
    GameObject(GameObject* parent, Material* mat, MeshGeometry* geo, std::string subgeoName, Transform transform);
    GameObject(GameObject* parent, Material* mat, MeshGeometry* geo, std::string subgeoName);

    void AddChild(GameObject* child);    

    Transform LocalTransform; //always relative to parent's
    std::shared_ptr<RenderItem> Ritem;
    std::string GeometryName;

private:
    GameObject* ParentGameObject;
    std::vector<GameObject*> ChildrenGameOjects;    
    

    inline static int cbIndex = 0;
    
};


