#pragma once
#ifdef ISDLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif // ISDLL

typedef struct Window Window;

HAZEL_API Window * HazelCreateWindow( int width , int height , const char * title );

HAZEL_API void HazelHandleEvent();

HAZEL_API int HazelGetWindowWidth( Window * window );

HAZEL_API int HazelGetWindowHeight( Window * window );
