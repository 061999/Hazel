#include "../Core/Hazel_API.h"
#include <DirectXColors.h>
#include <iostream>
int main()
{
    
    Window * win = HazelCreateWindow( 800 , 800 , "Hello" );
    //Graphics * gfx = HazelMakeGraphics( win );
    
    

    while( !HazelWindowIsClose( win ) )
    {
        if( HazelIsKeyDown( win , 'A' ) )
        {
            static int index = 0;
            index++;
            std::cout << "KeyDown" << index << std::endl;
        }
        HazelHandleEvent();
        //HazelClearColor( gfx , DirectX::Colors::Aquamarine );
        //HazelSwapBuffer( gfx );
    }
    return 0;
}