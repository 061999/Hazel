#include "../Core/Window.h"

int main()
{

	Window win( 900 , 900 );
	while( Window::m_WindowState )
	{
		Window::EventPoll();
	}
	return 0;
}