//#include "Graphics.h"
//#include "Window.h"
//#pragma comment(lib,"d3d11.lib")
//struct SWAP_CHAIN_DESC_EXTENSION : public DXGI_SWAP_CHAIN_DESC
//{
//    SWAP_CHAIN_DESC_EXTENSION( HWND win , int width , int height )
//    {
//        DXGI_MODE_DESC mode_desc = {};
//
//        mode_desc.Width = width;
//        mode_desc.Height = height;
//        mode_desc.RefreshRate = { 0u,0u };
//        mode_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
//        mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//        mode_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//
//        BufferDesc = mode_desc;
//        SampleDesc = { 4u,0u };
//        BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//        BufferCount = 1u;
//        OutputWindow = win;
//        Windowed = TRUE;
//        SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//        Flags = 0u;
//    }
//};
//
//struct VIEW_PORT_EXTENSION : public D3D11_VIEWPORT
//{
//    VIEW_PORT_EXTENSION( float width , float height )
//    {
//        TopLeftX = 0.0f;
//        TopLeftY = 0.0f;
//        Width = width;
//        Height = height;
//        MinDepth = 0.0f;
//        MaxDepth = 1.0f;
//    }
//};
//
//struct DEPTH_STENCIL_VIEW_DESC :public D3D11_TEXTURE2D_DESC
//{
//    DEPTH_STENCIL_VIEW_DESC( UINT width , UINT height )
//    {
//        Width = width;
//        Height = height;
//        MipLevels = 1u;
//        ArraySize = 1u;
//        Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
//        SampleDesc = { 4u,0u };
//        Usage = D3D11_USAGE_DEFAULT;
//        BindFlags = D3D11_BIND_DEPTH_STENCIL;
//        CPUAccessFlags = 0u;
//        MiscFlags = 0u;
//    }
//};
//
//Graphics::Graphics( Window & win )
//{
//    SWAP_CHAIN_DESC_EXTENSION swapchain_desc( win.GetHWND() , win.GetWidth() , win.GetHeight() );
//    D3D11CreateDeviceAndSwapChain( nullptr ,
//                                   D3D_DRIVER_TYPE_HARDWARE ,
//                                   nullptr ,
//                                   0u ,
//                                   nullptr ,
//                                   0u ,
//                                   D3D11_SDK_VERSION ,
//                                   &swapchain_desc ,
//                                   swapchain.GetAddressOf() ,
//                                   device.GetAddressOf() ,
//                                   nullptr ,
//                                   context.GetAddressOf()
//    );
//    ComPtr<ID3D11Resource> buffer;
//    swapchain->GetBuffer( 0u , IID_PPV_ARGS( buffer.GetAddressOf() ) );
//    device->CreateRenderTargetView( buffer.Get() , nullptr , RTV.GetAddressOf() );
//
//    //Create Depth Stencil View
//    DEPTH_STENCIL_VIEW_DESC depth_desc( win.GetWidth() , win.GetHeight() );
//    ComPtr<ID3D11Texture2D> depthBuffer;
//    device->CreateTexture2D( &depth_desc , nullptr , depthBuffer.GetAddressOf() );
//    device->CreateDepthStencilView( depthBuffer.Get() , nullptr , DSV.GetAddressOf() );
//
//    VIEW_PORT_EXTENSION viewport( (float)win.GetWidth() , (float)win.GetHeight() );
//    context->RSSetViewports( 1u , &viewport );
//}
//
//ID3D11Device * Graphics::GetDevice()
//{
//    return device.Get();
//}
//
//ID3D11DeviceContext * Graphics::GetContext()
//{
//    return context.Get();
//}
//
//void Graphics::Swap()
//{
//    swapchain->Present( 0u , 0u );
//}
//
//void Graphics::Clear()
//{
//    context->ClearRenderTargetView( RTV.Get() , DirectX::Colors::Aqua );
//}
//
//void Graphics::SetRenderTarget()
//{
//    context->OMSetRenderTargets( 1u , RTV.GetAddressOf() , DSV.Get() );
//}

#include "Hazel_API.h"
#include <d3d11.h>
#include <iostream>


struct Window
{
    HWND hwnd;
    int width;
    int height;
};

