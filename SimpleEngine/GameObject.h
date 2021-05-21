#include <DirectXMath.h>
#include <vector>

#include "FrameResource.h"
#include "Game.h"
#include "Transform.h"
#include "Components/BaseComponent.h"
#include "Components/MoveComponent.h"


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


class GameObject
{
public:
    GameObject(/*GameObject* parent, */Material* mat, MeshGeometry* geo, std::string subgeoName, Transform transform);
    GameObject(/*GameObject* parent, */Material* mat, MeshGeometry* geo, std::string subgeoName);

    void Update(const GameTimer& gt);
    void AddChild(GameObject* child);
    void SetParent(GameObject* parent);
    template <class T> void AddComponent();
    void RefreshWorldMatrix();    

    Transform LocalTransform; //always relative to parent's
    std::shared_ptr<RenderItem> Ritem;
    std::string GeometryName;

private:
    GameObject* ParentGameObject;
    std::vector<GameObject*> ChildrenGameOjects;
    std::vector<std::shared_ptr<BaseComponent>> Components;
    XMFLOAT4X4 GetGlobalWorldMatrix();    

    inline static int cbIndex = 0;
    
};

template <class T>
inline void GameObject::AddComponent()
{
    static_assert(std::is_base_of<BaseComponent, T>::value, "T must derive from BaseComponent");
    auto component = std::make_shared<T>(this);
    Components.push_back(std::move(component));
}


