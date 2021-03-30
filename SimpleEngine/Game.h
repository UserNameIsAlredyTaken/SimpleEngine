#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif


// Link necessary d3d12 libraries.
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#include<memory>
#include "BaseWindow.h"
#include "set"
#include "GameTimer.h"
#include "Util.h"
#include "d3d12.h"
#include "d3dx12.h"
#include <functional>

#define NECESSARY_STATIC_FUNCTIONS(GameClass)\
	static LRESULT GameClass::StaticMsgProc(Game* concreteGame, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)\
	{\
		return ((GameClass*)concreteGame)->MsgProc(hwnd, msg, wParam, lParam);\
	}\
	static void GameClass::StaticUpdate(Game* concreteGame, const GameTimer& gt)\
	{\
		((GameClass*)concreteGame)->Update(gt);\
	}\
	static void GameClass::StaticDraw(Game* concreteGame, const GameTimer& gt)\
	{\
		((GameClass*)concreteGame)->Draw(gt);\
	}


#define NECESSARY_STATIC_INIT(){\
	if (!Game::Initialize(StaticMsgProc))\
	return false;\
	InitUpdateFunction(StaticUpdate);\
	InitDrawFunction(StaticDraw);\
	}

class Game
{
public:
	Game(HINSTANCE hInstance);
	~Game();

protected:	
	Game(const Game& rhs) = delete;
	Game& operator=(const Game& rhs) = delete;
	

	static Game* mGame;

	HINSTANCE mhGameInst = nullptr; // application instance handle
	HWND      mhMainWnd = nullptr; // main window handle
	bool      mGamePaused = false;  // is the application paused?
	bool      mMinimized = false;  // is the application minimized?
	bool      mMaximized = false;  // is the application maximized?
	bool      mResizing = false;   // are the resize bars being dragged?
	bool      mFullscreenState = false;// fullscreen enabled

	// Set true to use 4X MSAA (§4.1.8).  The default is false.
	bool      m4xMsaaState = false;    // 4X MSAA enabled
	UINT      m4xMsaaQuality = 0;      // quality level of 4X MSAA

	// Used to keep track of the “delta-time” and game time (§4.4).
	GameTimer mTimer;

	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;

	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	UINT64 mCurrentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;

	static const int SwapChainBufferCount = 2;
	int mCurrBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

	D3D12_VIEWPORT mScreenViewport;
	D3D12_RECT mScissorRect;

	UINT mRtvDescriptorSize = 0;
	UINT mDsvDescriptorSize = 0;
	UINT mCbvSrvUavDescriptorSize = 0;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption = L"Game";
	D3D_DRIVER_TYPE md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	int mClientWidth = 800;
	int mClientHeight = 600;

	void CreateRtvAndDsvDescriptorHeaps();
	void OnResize();
	/*
	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }*/

	bool InitMainWindow();
	bool InitDirect3D();
	void CreateCommandObjects();
	void CreateSwapChain();

	void FlushCommandQueue();

	ID3D12Resource* CurrentBackBuffer()const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;

	void CalculateFrameStats();

	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

	//constexpr void InitUpdateFunction(std::function<void(Game* concreteGame, const GameTimer& gt)> update) {
	constexpr void InitUpdateFunction(void(*update)(Game* concreteGame, const GameTimer& gt) ) {
		//updates.push_back(update);
		updates[0] = update;
	}
	//void InitDrawFunction(std::function<void(Game* concreteGame, const GameTimer& gt)> render) {
	constexpr void InitDrawFunction(void(*render)(Game* concreteGame, const GameTimer& gt)) {
		//renders.push_back(render);
		renders[0] = render;
	}

private:
	std::set<std::shared_ptr<BaseWindow>> windows;

	void CreateWindows();
	void ShowWindows();


	void Update(const GameTimer& gt);
	void Draw(const GameTimer& gt);
	//std::vector<std::function<void(Game* concreteGame, const GameTimer& gt)>> updates;
	//std::vector<std::function<void(Game* concreteGame, const GameTimer& gt)>> renders;
	std::array<void(*)(Game* concreteGame, const GameTimer& gt),1> updates;
	std::array<void(*)(Game* concreteGame, const GameTimer& gt),1> renders;

	

public:
	static Game* GetGame();
	HINSTANCE GameInst()const;
	HWND      MainWnd()const;
	float AspectRatio()const;
	bool Get4xMsaaState()const;
	void Set4xMsaaState(bool value);

	bool Initialize(std::function<LRESULT(Game* concreteGame, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)> msgProc);
	LRESULT BaseMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static std::function<LRESULT(Game* concreteGame, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)> staticMsgProcPtr;


	int Run();

};

