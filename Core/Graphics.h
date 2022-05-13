#pragma once
#include "Hazel_API.h"
#include "Hazel_PCH.h"
class Window;
class HAZEL_API Graphics
{
public:
	Graphics( Window & win );
	ID3D11Device * GetDevice();
	ID3D11DeviceContext * GetContext();
	void Resize( int width , int height );
	void Swap();
	void Clear();
	void SetRenderTarget();
private:
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	ComPtr<IDXGISwapChain> swapchain;

	ComPtr<ID3D11RenderTargetView> RTV;
	ComPtr<ID3D11DepthStencilView> DSV;
};