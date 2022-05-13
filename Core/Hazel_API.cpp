//#include "Hazel_PCH.h"
//#include "Window.h"
//
//bool Window::m_CursorState = true;
//std::unique_ptr<Window::WindowClass> Window::m_WindowClass = std::make_unique<Window::WindowClass>();
//bool Window::m_WindowState = true;
//
////IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hwnd , UINT msg , WPARAM wParam , LPARAM lParam );
//
//static LRESULT ProcMessage( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam )
//{
//	Window * win = (Window *)GetWindowLongPtr( hWnd , GWLP_USERDATA );
//	win->HandMsg( hWnd , msg , wParam , lParam );
//	/*if( ImGui_ImplWin32_WndProcHandler( hWnd , msg , wParam , lParam ) )
//	{
//		return true;
//	}*/
//	return DefWindowProc( hWnd , msg , wParam , lParam );
//}
//
//static LRESULT HandleMessageSetup( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam )
//{
//	if( msg == WM_NCCREATE )
//	{
//		const CREATESTRUCTW * const pCreate = reinterpret_cast<CREATESTRUCTW *>(lParam);
//		Window * const pWnd = static_cast<Window *>(pCreate->lpCreateParams);
//		SetWindowLongPtr( hWnd , GWLP_USERDATA , reinterpret_cast<LONG_PTR>(pWnd) );
//		SetWindowLongPtr( hWnd , GWLP_WNDPROC , reinterpret_cast<LONG_PTR>(&ProcMessage) );
//	}
//	return DefWindowProc( hWnd , msg , wParam , lParam );
//}
//
//LPCWSTR Window::WindowClass::GetName()
//{
//	return ClassName.c_str();
//}
//
//UINT Window::WindowClass::GetStyle()
//{
//	return wc.style;
//}
//
//HINSTANCE Window::WindowClass::GetInstance()
//{
//	return hInstance;
//}
//
//Window::WindowClass::WindowClass() :
//	hInstance( GetModuleHandle( nullptr ) )
//{
//	wc.cbSize = sizeof( WNDCLASSEX );
//	wc.style = 0u;
//	wc.lpfnWndProc = HandleMessageSetup;
//	wc.cbClsExtra = 0u;
//	wc.cbWndExtra = 0u;
//	wc.hInstance = GetModuleHandle( nullptr );
//	wc.hIcon = nullptr;
//	wc.hCursor = nullptr;
//	wc.hbrBackground = nullptr;
//	wc.lpszMenuName = nullptr;
//	wc.lpszClassName = ClassName.c_str();
//	wc.hIconSm = nullptr;
//	RegisterClassEx( &wc );
//}
//
//Window::WindowClass::~WindowClass()
//{
//	UnregisterClass( ClassName.c_str() , hInstance );
//}
//
//void Window::HandMsg( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam ) noexcept
//{
//	switch( msg )
//	{
//		case WM_SIZE:
//			width = LOWORD( lParam );
//			height = HIWORD( lParam );
//			for( auto & e : Fn_Resize )
//			{
//				e( width , height );
//			}
//			break;
//		case WM_CLOSE:
//			m_WindowState = false;
//			break;
//		case WM_KEYDOWN:
//			if( !(lParam & 0x40000000) )
//			{
//				//Keyborad::OnPress( (int)wParam );
//			}
//			if( wParam == VK_ESCAPE )
//			{
//				if( m_CursorState )
//				{
//					DisableCursor();
//				}
//				else
//				{
//					EnableCursor();
//				}
//			}
//			for( auto & e : Fn_KeyDown )
//			{
//				e( wParam );
//			}
//			break;
//		case WM_KEYUP:
//			//Keyborad::OnRelease( (int)wParam );
//			break;
//		
//		case WM_INPUT:
//		{
//			if( m_CursorState )
//			{
//				break;
//			}
//			GetRawInputData( (HRAWINPUT)lParam , RID_INPUT , mouseRawData , &mouseRawDataSize , sizeof( RAWINPUTHEADER ) );
//			RAWINPUT * data = (RAWINPUT *)mouseRawData;
//			if( data->header.dwType == RIM_TYPEMOUSE && (data->data.mouse.lLastX != 0l || data->data.mouse.lLastY != 0l) )
//			{
//				for( auto & e : Fn_MouseDelta )
//				{
//					e( (float)data->data.mouse.lLastX , (float)data->data.mouse.lLastY );
//				}
//			}
//			break;
//		}
//		case WM_DROPFILES:
//			HDROP hDrop = reinterpret_cast<HDROP>(wParam);
//			UINT count = DragQueryFileA( hDrop , -1 , nullptr , 0u );
//			vector<char[128]> filepaths( count );
//			for( UINT i = 0; i < count; i++ )
//			{
//				DragQueryFileA( hDrop , i , filepaths[i] , 128u );
//			}
//			DragFinish( hDrop );
//			for( auto & e : Fn_DropFile )
//			{
//				e( filepaths );
//			}
//			break;
//		
//	}
//}
//
//Window::Window( int width , int height , const wchar_t * title ) :
//	width( width ) , height( height ) , mouseRawDataSize( sizeof( mouseRawData ) )
//{
//
//	RECT wr{ 0l,0l,width,height };
//	AdjustWindowRect( &wr , WS_CAPTION , FALSE );
//
//	hwnd = CreateWindowEx( WS_EX_ACCEPTFILES ,
//						   m_WindowClass->GetName() , title ,
//						   WS_CAPTION | WS_SYSMENU ,
//						   CW_USEDEFAULT , CW_USEDEFAULT , wr.right - wr.left , wr.bottom - wr.top ,
//						   nullptr , nullptr , m_WindowClass->GetInstance() , this
//	);
//	ShowWindow( hwnd , SW_SHOWDEFAULT );
//
//	RAWINPUTDEVICE rid;
//
//	rid.usUsagePage = 0x01;
//	rid.usUsage = 0x02;
//	rid.dwFlags = RIDEV_INPUTSINK;
//	rid.hwndTarget = hwnd;
//
//	RegisterRawInputDevices( &rid , 1 , sizeof( rid ) );
//}
//
//void Window::EventPoll()
//{
//	static MSG msg;
//	while( PeekMessage( &msg , nullptr , 0 , 0 , PM_REMOVE ) )
//	{
//		DispatchMessage( &msg );
//	}
//}
//
//HWND Window::GetHWND()
//{
//	return hwnd;
//}
//
//int Window::GetWidth() const
//{
//	return width;
//}
//
//int Window::GetHeight() const
//{
//	return height;
//}
//
//void Window::EnableCursor() const
//{
//	m_CursorState = true;
//	while( ::ShowCursor( TRUE ) < 0 );
//	ClipCursor( nullptr );
//}
//
//void Window::DisableCursor() const
//{
//	m_CursorState = false;
//	while( ::ShowCursor( FALSE ) >= 0 );
//	RECT rect;
//	GetClientRect( hwnd , &rect );
//	MapWindowPoints( hwnd , nullptr , reinterpret_cast<POINT *>(&rect) , 2 );
//	rect = {
//		(rect.right - rect.left) / 2 + rect.left ,
//		(rect.bottom - rect.top) / 2 + rect.top,
//		(rect.right - rect.left) / 2 + rect.left + 1 ,
//		(rect.bottom - rect.top) / 2 + rect.top + 1
//	};
//	ClipCursor( &rect );
//}
//
//void Window::PushCallBackKeyDown( const std::function<void( WPARAM )> & temp )
//{ 
//	Fn_KeyDown.push_back( temp );
//}
//
//void Window::PushCallBackMouseDelta( const std::function<void( float , float )>&temp )
//{ 
//	Fn_MouseDelta.push_back( temp );
//}
//
//void Window::PushCallBackDropFile( const std::function<void( vector<char[128]> & )>&temp )
//{ 
//	Fn_DropFile.push_back( temp );
//}
//
//void Window::PushCallBackResize( const std::function<void( int , int )>&temp )
//{
//	Fn_Resize.push_back( temp );
//}

#include "Hazel_API.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

struct Window
{
	HWND hwnd;
	int width;
	int height;
	bool cursorState;
	bool isClose;
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
				for( size_t i = 0; i < fn_keycallbacks.size(); i++ )
				{
					fn_keycallbacks[i]( static_cast<unsigned char>(wParam) );
				}
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
									"H e l l o" , WS_CAPTION | WS_SYSMENU ,
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

struct Graphics
{
	ID3D11Device * device;
	ID3D11DeviceContext * context;
	IDXGISwapChain * swapchain;
	ID3D11RenderTargetView * RTV;
};

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


HAZEL_API Graphics * HazelMakeGraphics( Window * window )
{
	Graphics * graphics = new Graphics;
	SWAP_CHAIN_DESC_EXTENSION swapchain_desc( window->hwnd , window->width , window->height );
	D3D11CreateDeviceAndSwapChain( nullptr ,
								   D3D_DRIVER_TYPE_HARDWARE ,
								   nullptr ,
								   0u ,
								   nullptr ,
								   0u ,
								   D3D11_SDK_VERSION ,
								   &swapchain_desc ,
								   &graphics->swapchain ,
								   &graphics->device ,
								   nullptr ,
								   &graphics->context
	);

	ID3D11Resource * buffer;
	graphics->swapchain->GetBuffer( 0u , IID_PPV_ARGS( &buffer ) );
	graphics->device->CreateRenderTargetView( buffer , nullptr , &graphics->RTV );
	buffer->Release();

	graphics->context->OMSetRenderTargets( 1u , &graphics->RTV , nullptr );

	return graphics;
}

HAZEL_API void HazelPushDropFileCallBack( Window * window , const std::function<void( std::vector<char[128]> & paths )> & fn_back )
{
	window->Fn_DropFile.push_back( fn_back );
}

HAZEL_API void HazelSwapBuffer( Graphics * gfx )
{
	gfx->swapchain->Present( 0u , 0u );
}


HAZEL_API void HazelClearColor( Graphics * gfx , const float ColorRGBA[4] )
{
	gfx->context->ClearRenderTargetView( gfx->RTV , ColorRGBA );
}