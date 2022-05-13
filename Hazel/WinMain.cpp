#include "../Core/Hazel_API.h"
#include <iostream>

int main()
{
	Window * win = HazelCreateWindow( 800 , 800 , "Hello" );
	std::cout << HazelGetWindowHeight( win );
	while( true )
	{
		HazelHandleEvent();
	}
	return 0;
}