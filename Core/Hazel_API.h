#pragma once
#ifdef ISDLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif // ISDLL

#include <functional>
#include <vector>

typedef struct Window Window;

typedef struct Graphics Graphics;

/// <summary>
/// 创建一个窗口, 返回一个窗口句柄
/// </summary>
/// <param name="width">窗口的宽度</param>
/// <param name="height">窗口的高度</param>
/// <param name="title">窗口的标题</param>
/// <returns>窗口的句柄</returns>
HAZEL_API Window * HazelCreateWindow( int width , int height , const char * title );

/// <summary>
/// 制造一个Graphics句柄
/// </summary>
/// <param name="window">Window句柄</param>
/// <returns>Graphics句柄</returns>
HAZEL_API Graphics * HazelMakeGraphics( Window * window );

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
HAZEL_API void HazelSwapBuffer( Graphics * gfx );

/// <summary>
/// 清除
/// </summary>
/// <param name="gfx">Graphics句柄</param>
/// <param name="ColorRGBA">颜色</param>
/// <returns></returns>
HAZEL_API void HazelClearColor( Graphics * gfx , const float ColorRGBA[4] );