#include "../Core/Hazel_API.h"
#include <DirectXColors.h>
#include <iostream>
int main()
{
    
    Window * win = HazelCreateWindow( 800 , 800 , "Hello" );
    HazelMakeContext( win );
    
    float position[] = {
        0.0f , 0.5f ,
        0.5f ,-0.5f ,
        -0.5f,-0.5f ,
    };

    unsigned int indices[] = {
        0,1,2
    };

    VertexBuffer * vbo = HazelCreateVertexBuffer( position , sizeof( float ) * 2 , 3 );
    IndexBuffer * ibo = HazelCreateIndexBuffer( indices , 3u );
    InputLayout * layout = HazelCreateInputLayout();
    HazelAddInputElementDesc( layout , "POSITION" , 0 , 2u );
    ShaderVertex * vs = HazelCreateShaderVertex( L"Shader/VS.cso" , layout );
    ShaderPixel * ps = HazelCreateShaderPixel( L"Shader/PS.cso" );

    while( !HazelWindowIsClose( win ) )
    {
        HazelHandleEvent();
        HazelClearColor( DirectX::Colors::Aquamarine );
        HazelBindShader( vs , ps );
        HazelBindBuffer( vbo , ibo );
        HazelSwapBuffer();
    }
    return 0;
}