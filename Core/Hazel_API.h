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
/// ����һ������, ����һ�����ھ��
/// </summary>
/// <param name="width">���ڵĿ��</param>
/// <param name="height">���ڵĸ߶�</param>
/// <param name="title">���ڵı���</param>
/// <returns>���ڵľ��</returns>
HAZEL_API Window * HazelCreateWindow( int width , int height , const char * title );

/// <summary>
/// ����һ��Graphics���
/// </summary>
/// <param name="window">Window���</param>
/// <returns>Graphics���</returns>
HAZEL_API Graphics * HazelMakeGraphics( Window * window );

/// <summary>
/// �����Ƿ�ر�
/// </summary>
/// <param name="window">Window���</param>
/// <returns>bool</returns>
HAZEL_API bool HazelWindowIsClose( Window * window );

/// <summary>
/// ��Ϣ����
/// </summary>
/// <returns></returns>
HAZEL_API void HazelHandleEvent();

/// <summary>
/// ���ش��ڿ��
/// </summary>
/// <param name="window">Window���</param>
/// <returns>���</returns>
HAZEL_API int HazelGetWindowWidth( Window * window );

/// <summary>
/// ���ش��ڸ߶�
/// </summary>
/// <param name="window">Window���</param>
/// <returns>�߶�</returns>
HAZEL_API int HazelGetWindowHeight( Window * window );

/// <summary>
/// ���һ��KeyDown�ص�
/// </summary>
/// <param name="window">Window���</param>
/// <param name="fn_back">�ص�����</param>
/// <returns></returns>
HAZEL_API void HazelPushKeyDownCallBack( Window * window , const std::function<void( unsigned char )> & fn_back );

/// <summary>
/// ���һ��MouseDelta�ص�
/// </summary>
/// <param name="window">Window���</param>
/// <param name="fn_back">�ص�����</param>
/// <returns></returns>
HAZEL_API void HazelPushMouseDeltaCallBack( Window * window , const std::function<void( float , float )> & fn_back );

/// <summary>
/// �ļ���ק�ص�
/// </summary>
/// <param name="window">window���</param>
/// <param name="fn_back">�ص�����</param>
/// <returns></returns>
HAZEL_API void HazelPushDropFileCallBack( Window * window , const std::function<void( std::vector<char[128]> & paths )> & fn_back );

/// <summary>
/// ����������
/// </summary>
/// <param name="gfx">Graphics���</param>
/// <returns></returns>
HAZEL_API void HazelSwapBuffer( Graphics * gfx );

/// <summary>
/// ���
/// </summary>
/// <param name="gfx">Graphics���</param>
/// <param name="ColorRGBA">��ɫ</param>
/// <returns></returns>
HAZEL_API void HazelClearColor( Graphics * gfx , const float ColorRGBA[4] );