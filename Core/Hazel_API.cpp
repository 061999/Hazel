

#include "Hazel_API.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include "Image.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

using Microsoft::WRL::ComPtr;

static ComPtr<ID3D11Device> device;
static ComPtr<ID3D11DeviceContext> context;
static ComPtr<IDXGISwapChain> swapchain;
static ComPtr<ID3D11RenderTargetView> RTV;

struct Window
{
	HWND hwnd;
	int width;
	int height;
	bool cursorState;
	bool isClose;
	bool keyboradState[256] = { false };
	std::vector<std::function<void( unsigned char )>> fn_keycallbacks;
	std::vector<std::function<void( float , float )>> fn_mousecallback;
	std::vector<std::function<void( std::vector<char[128]> & paths )>> Fn_DropFile;
	void HandMessage( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam )
	{
		switch( msg )
		{
			case WM_CLOSE:
			{
				isClose = true;
				break;
			}
			case WM_KEYDOWN:
			{
				if( !(lParam & 0x40000000) )
				{
					keyboradState[wParam] = true;
				}
				for( size_t i = 0; i < fn_keycallbacks.size(); i++ )
				{
					fn_keycallbacks[i]( static_cast<unsigned char>(wParam) );
				}
				break;
			}
			case WM_KEYUP:
			{
				keyboradState[wParam] = false;
				break;
			}
			case WM_INPUT:
			{
				if( cursorState )
				{
					break;
				}
				static unsigned int mouseRawDataSize = 1024u;
				static char * mouseRawData = new char[mouseRawDataSize];
				GetRawInputData( (HRAWINPUT)lParam , RID_INPUT , mouseRawData , &mouseRawDataSize , sizeof( RAWINPUTHEADER ) );
				RAWINPUT * data = (RAWINPUT *)mouseRawData;
				if( data->header.dwType == RIM_TYPEMOUSE && (data->data.mouse.lLastX != 0l || data->data.mouse.lLastY != 0l) )
				{
					for( auto & e : fn_mousecallback )
					{
						e( (float)data->data.mouse.lLastX , (float)data->data.mouse.lLastY );
					}
				}

				break;
			}
			case WM_DROPFILES:
				HDROP hDrop = reinterpret_cast<HDROP>(wParam);
				UINT count = DragQueryFileA( hDrop , -1 , nullptr , 0u );
				std::vector<char[128]> filepaths( count );
				for( UINT i = 0; i < count; i++ )
				{
					DragQueryFileA( hDrop , i , filepaths[i] , 128u );
				}
				DragFinish( hDrop );
				for( auto & e : Fn_DropFile )
				{
					e( filepaths );
				}
				break;

		}
	}
};

static LRESULT ProcMessage( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam )
{
	Window * win = (Window *)GetWindowLongPtr( hWnd , GWLP_USERDATA );
	win->HandMessage( hWnd , msg , wParam , lParam );
	return DefWindowProc( hWnd , msg , wParam , lParam );
}


static LRESULT HandleMessageSetup( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam )
{
	if( msg == WM_NCCREATE )
	{
		const CREATESTRUCTW * const pCreate = reinterpret_cast<CREATESTRUCTW *>(lParam);
		Window * const pWnd = static_cast<Window *>(pCreate->lpCreateParams);
		SetWindowLongPtr( hWnd , GWLP_USERDATA , reinterpret_cast<LONG_PTR>(pWnd) );
		SetWindowLongPtr( hWnd , GWLP_WNDPROC , reinterpret_cast<LONG_PTR>(&ProcMessage) );
	}
	return DefWindowProc( hWnd , msg , wParam , lParam );
}


struct WINDOWCLASS_DESC :WNDCLASSEXA
{
	WINDOWCLASS_DESC()
	{
		cbSize = sizeof( WNDCLASSEXA );
		style = 0u;
		lpfnWndProc = HandleMessageSetup;
		cbClsExtra = 0u;
		cbWndExtra = 0u;
		hInstance = GetModuleHandleA( nullptr );
		hIcon = nullptr;
		hCursor = nullptr;
		hbrBackground = nullptr;
		lpszMenuName = nullptr;
		lpszClassName = "Engin Window";
		hIconSm = nullptr;
	}
};



HAZEL_API Window * HazelCreateWindow( int width , int height , const char * title )
{
	WINDOWCLASS_DESC window_desc;
	RegisterClassExA( &window_desc );
	Window * window = new Window;
	window->width = width;
	window->height = height;
	window->cursorState = true;
	window->isClose = false;
	RECT wr{ 0l,0l,width,height };
	AdjustWindowRect( &wr , WS_CAPTION , FALSE );
	window->hwnd = CreateWindowExA( WS_EX_ACCEPTFILES ,
									window_desc.lpszClassName ,
									title , WS_CAPTION | WS_SYSMENU ,
									CW_USEDEFAULT , CW_USEDEFAULT,
									wr.right - wr.left , wr.bottom - wr.top ,
									nullptr , nullptr ,
									GetModuleHandleA( nullptr ) ,
									window
	);
	ShowWindow( window->hwnd , SW_SHOWDEFAULT );

	RAWINPUTDEVICE rid;

	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = RIDEV_INPUTSINK;
	rid.hwndTarget = window->hwnd;

	RegisterRawInputDevices( &rid , 1 , sizeof( rid ) );

	return window;
}

HAZEL_API bool HazelWindowIsClose( Window * window )
{
	return window->isClose;
}

HAZEL_API void HazelHandleEvent()
{
	static MSG msg;
	while( PeekMessageA( &msg , nullptr , 0u , 0u , PM_REMOVE ) )
	{
		DispatchMessageA( &msg );
	}
}

HAZEL_API int HazelGetWindowWidth( Window * window )
{
	return window->width;
}

HAZEL_API int HazelGetWindowHeight( Window * window )
{
	return window->height;
}

HAZEL_API void HazelPushKeyDownCallBack( Window * window , const std::function<void( unsigned char )> & fn_back )
{
	window->fn_keycallbacks.push_back( fn_back );
}

HAZEL_API void HazelPushMouseDeltaCallBack( Window * window , const std::function<void( float , float ) > & fn_back )
{ 
	window->fn_mousecallback.push_back( fn_back );
}

struct SWAP_CHAIN_DESC_EXTENSION : public DXGI_SWAP_CHAIN_DESC
{
	SWAP_CHAIN_DESC_EXTENSION( HWND win , int width , int height )
	{
		DXGI_MODE_DESC mode_desc = {};

		mode_desc.Width = width;
		mode_desc.Height = height;
		mode_desc.RefreshRate = { 0u,0u };
		mode_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		mode_desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		mode_desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		BufferDesc = mode_desc;
		SampleDesc = { 4u,0u };
		BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		BufferCount = 1u;
		OutputWindow = win;
		Windowed = TRUE;
		SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		Flags = 0u;
	}
};

struct VIEW_PORT_EXTENSION : public D3D11_VIEWPORT
{
	VIEW_PORT_EXTENSION( float width , float height )
	{
		TopLeftX = 0.0f;
		TopLeftY = 0.0f;
		Width = width;
		Height = height;
		MinDepth = 0.0f;
		MaxDepth = 1.0f;
	}
};

HAZEL_API void HazelMakeContext( Window * window )
{
	SWAP_CHAIN_DESC_EXTENSION swapchain_desc( window->hwnd , window->width , window->height );
	D3D11CreateDeviceAndSwapChain( nullptr ,
								   D3D_DRIVER_TYPE_HARDWARE ,
								   nullptr ,
								   0u ,
								   nullptr ,
								   0u ,
								   D3D11_SDK_VERSION ,
								   &swapchain_desc ,
								   swapchain.GetAddressOf() ,
								   device.GetAddressOf() ,
								   nullptr ,
								   context.GetAddressOf()
	);
	ComPtr<ID3D11Resource> buffer;
	swapchain->GetBuffer( 0u , IID_PPV_ARGS( buffer.GetAddressOf() ) );
	device->CreateRenderTargetView( buffer.Get() , nullptr , RTV.GetAddressOf() );
	VIEW_PORT_EXTENSION viewport( (float)window->width , (float)window->height );
	context->RSSetViewports( 1u , &viewport );

	context->OMSetRenderTargets( 1u , RTV.GetAddressOf() , nullptr );
}

HAZEL_API void HazelPushDropFileCallBack( Window * window , const std::function<void( std::vector<char[128]> & paths )> & fn_back )
{
	window->Fn_DropFile.push_back( fn_back );
}

HAZEL_API void HazelSwapBuffer()
{
	swapchain->Present( 0u , 0u );
}

HAZEL_API bool HazelIsKeyDown( Window * window , const unsigned char & code )
{
	return window->keyboradState[code];
}

struct VertexBuffer
{
	ComPtr<ID3D11Buffer> vertexBuffer;
	UINT stride = 0u;
};

HAZEL_API VertexBuffer * HazelCreateVertexBuffer( void * data , unsigned int stride , unsigned int count )
{
	VertexBuffer * buffer = new VertexBuffer;
	D3D11_BUFFER_DESC vbd = {};
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = stride * count;
	vbd.StructureByteStride = stride;
	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem = data;
	device->CreateBuffer( &vbd , &vsd , buffer->vertexBuffer.GetAddressOf() );
	buffer->stride = stride;
	return buffer;
}

struct IndexBuffer
{
	ComPtr<ID3D11Buffer> indexBuffer;
	UINT count = 0u;
};

HAZEL_API IndexBuffer * HazelCreateIndexBuffer( unsigned int * data , unsigned int count )
{
	IndexBuffer * buffer = new IndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = count * sizeof( unsigned int );
	ibd.StructureByteStride = sizeof( unsigned int );
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = data;
	device->CreateBuffer( &ibd , &isd , buffer->indexBuffer.GetAddressOf() );
	buffer->count = count;
	return buffer;
}

HAZEL_API void HazelBindBuffer( VertexBuffer * vbo , IndexBuffer * ibo )
{ 
	static unsigned int offset = 0u;
	context->IASetVertexBuffers( 0u , 1u , vbo->vertexBuffer.GetAddressOf() , &vbo->stride , &offset );
	context->IASetIndexBuffer( ibo->indexBuffer.Get() , DXGI_FORMAT_R32_UINT , 0u );
	context->DrawIndexed( ibo->count , 0u , 0 );
}

struct InputLayout
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
	UINT offset = 0u;
};

HAZEL_API InputLayout * HazelCreateInputLayout()
{
	return new InputLayout;
}

HAZEL_API void HazelAddInputElementDesc( InputLayout * layout , const char * name , int type , unsigned int count )
{
	if( type == 0 )
	{
		switch( count )
		{
			case 2u:
				layout->descs.push_back( { name,0,DXGI_FORMAT_R32G32_FLOAT,0,layout->offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
				layout->offset += sizeof( float ) * 2;
				break;
			case 3u:
				layout->descs.push_back( { name,0,DXGI_FORMAT_R32G32B32_FLOAT,0,layout->offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
				layout->offset += sizeof( float ) * 3;
				break;
		}
	}
	else if( type == 1 )
	{

	}
}

struct ShaderVertex
{
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11InputLayout> inputLayout;
};

HAZEL_API ShaderVertex * HazelCreateShaderVertex( const wchar_t * path , InputLayout * layout )
{
	ShaderVertex * buffer = new ShaderVertex;
	ComPtr<ID3DBlob> b;
	D3DReadFileToBlob( path , b.GetAddressOf() );
	device->CreateVertexShader( b->GetBufferPointer() , b->GetBufferSize() , nullptr , buffer->vertexShader.GetAddressOf() );

	device->CreateInputLayout( layout->descs.data() , (UINT)layout->descs.size() , b->GetBufferPointer() , b->GetBufferSize() , buffer->inputLayout.GetAddressOf() );
	return buffer;
}

struct ShaderPixel
{
	ComPtr<ID3D11PixelShader> pixelShader;
};

HAZEL_API ShaderPixel * HazelCreateShaderPixel( const wchar_t * path )
{
	ShaderPixel * buffer = new ShaderPixel;
	ComPtr<ID3DBlob> b1;
	D3DReadFileToBlob( path , b1.GetAddressOf() );
	device->CreatePixelShader( b1->GetBufferPointer() , (UINT)b1->GetBufferSize() , nullptr , buffer->pixelShader.GetAddressOf() );

	return buffer;
}

HAZEL_API void HazelBindShader( ShaderVertex * vs , ShaderPixel * ps )
{
	context->IASetInputLayout( vs->inputLayout.Get() );
	context->VSSetShader( vs->vertexShader.Get() , nullptr , 0u );
	context->PSSetShader( ps->pixelShader.Get() , nullptr , 0u );
}



struct Texture2D
{
	ComPtr<ID3D11ShaderResourceView> texview;
	UINT startSlot;
};

HAZEL_API Texture2D * HazelCreateTexture2D( const char * path , unsigned int slot )
{
	Texture2D * buffer = new Texture2D;
	buffer->startSlot = slot;
	Image img( path );
	D3D11_TEXTURE2D_DESC tex_desc;
	tex_desc.Width = img.GetWidth();
	tex_desc.Height = img.GetHeight();
	tex_desc.MipLevels = 1;
	tex_desc.ArraySize = 1;
	tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tex_desc.CPUAccessFlags = 0;
	tex_desc.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = img.GetData();
	data.SysMemPitch = img.GetLineWidth();
	ComPtr<ID3D11Texture2D> pTexture;
	device->CreateTexture2D( &tex_desc , &data , pTexture.GetAddressOf() );
	D3D11_SHADER_RESOURCE_VIEW_DESC tex_view_desc;
	tex_view_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tex_view_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	tex_view_desc.Texture2D.MostDetailedMip = 0;
	tex_view_desc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView( pTexture.Get() , &tex_view_desc , buffer->texview.GetAddressOf() );
	return buffer;
}

HAZEL_API void HazelBindTexture2D( Texture2D * pTexture )
{
	context->PSSetShaderResources( pTexture->startSlot , 1u , pTexture->texview.GetAddressOf() );
}

HAZEL_API void HazelClearColor( const float ColorRGBA[4] )
{
	context->ClearRenderTargetView( RTV.Get() , ColorRGBA );
}