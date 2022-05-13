#pragma once
#ifdef ISDLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif // ISDLL

#include <functional>

typedef struct Window Window;
typedef struct Graphics Graphics;

HAZEL_API Window * HazelCreateWindow( int width , int height , const char * title );

HAZEL_API Graphics * HazelMakeGraphics( Window * window );

HAZEL_API bool HazelWindowIsClose( Window * window );

HAZEL_API void HazelHandleEvent();

HAZEL_API int HazelGetWindowWidth( Window * window );

HAZEL_API int HazelGetWindowHeight( Window * window );

HAZEL_API void HazelPushKeyDownCallBack( Window * window , const std::function<void( unsigned char )> & fn_back );

HAZEL_API void HazelPushMouseDeltaCallBack( Window * window , const std::function<void( float , float )> & fn_back );

HAZEL_API void HazelSwapBuffer( Graphics * gfx );

HAZEL_API void HazelClearColor( Graphics * gfx , const float ColorRGBA[4] );