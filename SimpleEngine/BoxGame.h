#pragma once
#include "Game.h"
#include "MathHelper.h"
#include "UploadBuffer.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct ObjectConstants
{
	XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};

class BoxGame : public Game
{
public:
	BoxGame(HINSTANCE hInstance);
	~BoxGame();

	bool Initialize();


private:
	XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
    XMFLOAT4X4 mView = MathHelper::Identity4x4();
    XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	NECESSARY_STATIC_FUNCTIONS(BoxGame);
	// static LRESULT BoxGame::StaticMsgProc(Game* concreteGame, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	// {
	// 	return ((BoxGame*)concreteGame)->MsgProc(hwnd, msg, wParam, lParam);
	// }
	// static void BoxGame::StaticUpdate(Game* concreteGame, const GameTimer& gt)
	// {
	// 	((BoxGame*)concreteGame)->Update(gt);
	// }
	// static void BoxGame::StaticDraw(Game* concreteGame, const GameTimer& gt)
	// {
	// 	((BoxGame*)concreteGame)->Draw(gt);
	// }
	// static void BoxGame::StaticOnMouseDown(Game* concreteGame, const WPARAM btnState, int x, int y)
	// {
	// 	((BoxGame*)concreteGame)->OnMouseDown(btnState, x, y);
	// }
	// static void BoxGame::StaticOnMouseUp(Game* concreteGame, const WPARAM btnState, int x, int y)
	// {
	// 	((BoxGame*)concreteGame)->OnMouseUp(btnState, x, y);
	// }
	// static void BoxGame::StaticOnMouseMove(Game* concreteGame, const WPARAM btnState, int x, int y)
	// {
	// 	((BoxGame*)concreteGame)->OnMouseMove(btnState, x, y);
	// }
	// static void BoxGame::StaticOnResize(Game* concreteGame)
	// {
	// 	((BoxGame*)concreteGame)->OnResize();
	// }

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Update(const GameTimer& gt);
	void Draw(const GameTimer& gt);
	void OnResize();

	void BuildDescriptorHeaps();
	void BuildConstantBuffers();
	void BuildRootSignature();
	void BuildShadersAndInputLayout();
	void BuildBoxGeometry();
	void BuildPSO();

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);
	

	ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;
	std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;
	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
	ComPtr<ID3DBlob> mvsByteCode = nullptr;
	ComPtr<ID3DBlob> mpsByteCode = nullptr;
	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;
	ComPtr<ID3D12PipelineState> mPSO = nullptr;

	float mTheta = 1.5f*XM_PI;
	float mPhi = XM_PIDIV2;
	float mRadius = 5.0f;

	POINT mLastMousePos;
};


