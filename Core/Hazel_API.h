#pragma once
#ifdef ISDLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif // ISDLL

#include <functional>
#include <vector>

typedef struct Window Window;

typedef struct Texture2D Texture2D;

typedef struct VertexBuffer VertexBuffer;

typedef struct IndexBuffer IndexBuffer;

typedef struct InputLayout InputLayout;

typedef struct ShaderVertex ShaderVertex;

typedef struct ShaderPixel ShaderPixel;

/// <summary>
/// 创建一个窗口, 返回一个窗口句柄
/// </summary>
/// <param name="width">窗口的宽度</param>
/// <param name="height">窗口的高度</param>
/// <param name="title">窗口的标题</param>
/// <returns>窗口的句柄</returns>
HAZEL_API Window * HazelCreateWindow( int width , int height , const char * title );

HAZEL_API void HazelMakeContext( Window * window );

/// <summary>
/// 窗口是否关闭
/// </summary>
/// <param name="window">Window句柄</param>
/// <returns>bool</returns>
HAZEL_API bool HazelWindowIsClose( Window * window );

/// <summary>
/// 消息处理
/// </summary>
/// <returns></returns>
HAZEL_API void HazelHandleEvent();

/// <summary>
/// 返回窗口宽度
/// </summary>
/// <param name="window">Window句柄</param>
/// <returns>宽度</returns>
HAZEL_API int HazelGetWindowWidth( Window * window );

/// <summary>
/// 返回窗口高度
/// </summary>
/// <param name="window">Window句柄</param>
/// <returns>高度</returns>
HAZEL_API int HazelGetWindowHeight( Window * window );

/// <summary>
/// 添加一个KeyDown回调
/// </summary>
/// <param name="window">Window句柄</param>
/// <param name="fn_back">回调函数</param>
/// <returns></returns>
HAZEL_API void HazelPushKeyDownCallBack( Window * window , const std::function<void( unsigned char )> & fn_back );

/// <summary>
/// 添加一个MouseDelta回调
/// </summary>
/// <param name="window">Window句柄</param>
/// <param name="fn_back">回调函数</param>
/// <returns></returns>
HAZEL_API void HazelPushMouseDeltaCallBack( Window * window , const std::function<void( float , float )> & fn_back );

/// <summary>
/// 文件拖拽回调
/// </summary>
/// <param name="window">window句柄</param>
/// <param name="fn_back">回调函数</param>
/// <returns></returns>
HAZEL_API void HazelPushDropFileCallBack( Window * window , const std::function<void( std::vector<char[128]> & paths )> & fn_back );

/// <summary>
/// 交换缓冲区
/// </summary>
/// <param name="gfx">Graphics句柄</param>
/// <returns></returns>
HAZEL_API void HazelSwapBuffer();

/// <summary>
/// 判断键盘是否按下
/// </summary>
/// <param name="window">Window句柄</param>
/// <param name="code">被判断的键值</param>
/// <returns>是否按下</returns>
HAZEL_API bool HazelIsKeyDown( Window * window , const unsigned char & code );

HAZEL_API VertexBuffer * HazelCreateVertexBuffer( void * data , unsigned int stride , unsigned int count );

HAZEL_API IndexBuffer * HazelCreateIndexBuffer( unsigned int * data , unsigned int count );

HAZEL_API void HazelBindBuffer( VertexBuffer * vbo , IndexBuffer * ibo );

HAZEL_API InputLayout * HazelCreateInputLayout();

HAZEL_API void HazelAddInputElementDesc( InputLayout * layout , const char * name , int type , unsigned int count );

HAZEL_API ShaderVertex * HazelCreateShaderVertex( const wchar_t * path , InputLayout * layout );

HAZEL_API ShaderPixel * HazelCreateShaderPixel( const wchar_t * path );

HAZEL_API void HazelBindShader( ShaderVertex * vs , ShaderPixel * ps );

HAZEL_API Texture2D * HazelCreateTexture2D( const char * path , unsigned int slot = 0u );

HAZEL_API void HazelBindTexture2D( Texture2D * pTexture );

/// <summary>
/// 清除
/// </summary>
/// <param name="gfx">Graphics句柄</param>
/// <param name="ColorRGBA">颜色</param>
/// <returns></returns>
HAZEL_API void HazelClearColor( const float ColorRGBA[4] );



