#pragma once
#include "Common/Camera.h"
#include "FrameResource.h"
#include "Game.h"
#include "GameObject.h"
#include "ShadowMap.h"
#include "Common/UploadBuffer.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;



enum class RenderLayer : int
{
    Opaque = 0,
    Debug,
    Count
};

class KatamariGame : public Game
{
public:
    KatamariGame(HINSTANCE hInstance);
    ~KatamariGame();

    bool Initialize();

    NECESSARY_STATIC_FUNCTIONS(KatamariGame);

private:
    LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void Update(const GameTimer& gt);
    void Draw(const GameTimer& gt);
    void OnResize();
    virtual void CreateRtvAndDsvDescriptorHeaps()override;

    void OnKeyboardInput(const GameTimer& gt);
    void AnimateMaterials(const GameTimer& gt);
    void UpdateMaterialBuffer(const GameTimer& gt);
    void UpdateShadowTransform(const GameTimer& gt);
    void UpdateObjects(const GameTimer& gt);
    void UpdateObjectCBs(const GameTimer& gt);
    void UpdateMainPassCB(const GameTimer& gt);
    void UpdateShadowPassCB(const GameTimer& gt);

    void OnMouseDown(WPARAM btnState, int x, int y);
    void OnMouseUp(WPARAM btnState, int x, int y);
    void OnMouseMove(WPARAM btnState, int x, int y);

    void LoadTextures();
    void BuildRootSignature();
    void BuildDescriptorHeaps();
    void BuildShadersAndInputLayout();
    void BuildShapeGeometry();
    void BuildPSOs();
    void BuildFrameResources();
    void BuildMaterials();
    void BuildGameObjects();
    void DrawGameObjects(ID3D12GraphicsCommandList* cmdList, std::vector<std::shared_ptr<GameObject>>& ritems);
    void DrawSceneToShadowMap();

    std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> GetStaticSamplers();

    std::vector<std::unique_ptr<FrameResource>> mFrameResources;
    FrameResource* mCurrFrameResource = nullptr;
    int mCurrFrameResourceIndex = 0;

    UINT mCbvSrvDescriptorSize = 0;
    
    ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

    ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
    std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
    std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
    std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
    
    std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;

    std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
    
    std::vector<std::shared_ptr<GameObject>> AllGameObjects;

    // Render layers divided by PSO.
    std::vector<std::shared_ptr<GameObject>> RenderLayers[(int)RenderLayer::Count];

    UINT mShadowMapHeapIndex = 0;
    UINT mShadowSrvIndex = 0;

    CD3DX12_GPU_DESCRIPTOR_HANDLE mShadowSrv;
    
    PassConstants mMainPassCB;   // index 0 of pass cbuffer.
    PassConstants mShadowPassCB; // index 1 of pass cbuffer.

    Camera mCamera;

    std::unique_ptr<ShadowMap> mShadowMap;

    DirectX::BoundingSphere mSceneBounds;

    float mLightNearZ = 0.0f;
    float mLightFarZ = 0.0f;
    XMFLOAT3 mLightPosW;
    XMFLOAT4X4 mLightView = MathHelper::Identity4x4();
    XMFLOAT4X4 mLightProj = MathHelper::Identity4x4();
    XMFLOAT4X4 mShadowTransform = MathHelper::Identity4x4();

    UINT mPassCbvOffset = 0;

    float lightTheta = 1.25f*XM_PI;;
    float lightPhi = XM_PIDIV2;
    float lightDistance = 2.0f;

    float lightRotationSpeed = 3.0f;

    POINT mLastMousePos;

    bool debugKeyPrevStateIsDown = false;
    bool showDebug = false;

    bool flyCar = false;

};








