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
/// ����һ������, ����һ�����ھ��
/// </summary>
/// <param name="width">���ڵĿ��</param>
/// <param name="height">���ڵĸ߶�</param>
/// <param name="title">���ڵı���</param>
/// <returns>���ڵľ��</returns>
HAZEL_API Window * HazelCreateWindow( int width , int height , const char * title );

HAZEL_API void HazelMakeContext( Window * window );

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
HAZEL_API void HazelSwapBuffer();

/// <summary>
/// �жϼ����Ƿ���
/// </summary>
/// <param name="window">Window���</param>
/// <param name="code">���жϵļ�ֵ</param>
/// <returns>�Ƿ���</returns>
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
/// ���
/// </summary>
/// <param name="gfx">Graphics���</param>
/// <param name="ColorRGBA">��ɫ</param>
/// <returns></returns>
HAZEL_API void HazelClearColor( const float ColorRGBA[4] );



