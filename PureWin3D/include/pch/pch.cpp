#include "pch.h"

namespace pw
{
	const double PI = 3.14159265358979;
	const double TWO_PI = 2 * PI;
}

#ifdef PW_PLATFORM_WIN32
#	pragma comment( lib, "d3d11.lib" )
#	pragma comment( lib, "dxgi.lib" )
#	pragma comment( lib, "d3dx11.lib" )
#	pragma comment( lib, "DxErr.lib" )
#endif