#include "../Core/Hazel_API.h"
#include <DirectXColors.h>
#include <iostream>

int main()
{
	Window * win = HazelCreateWindow( 800 , 800 , "Hello" );
//		Graphics * gfx = HazelMakeGraphics(win);
	
	

	while( !HazelWindowIsClose( win ) )
	{
		HazelHandleEvent();
		//HazelClearColor( gfx , DirectX::Colors::Aquamarine );
		//HazelSwapBuffer( gfx );
	}
	return 0;
}