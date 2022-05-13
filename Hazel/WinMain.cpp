#include "../Core/CORE.h"
int main()
{
	Window win( 900 , 900 );
	Graphics gfx( win );
	while( Window::m_WindowState )
	{
		gfx.Clear();
		gfx.SetRenderTarget();
		gfx.Swap();
		Window::EventPoll();
	}
	return 0;
}