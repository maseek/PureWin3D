#include "pch.h"
#include "../../include/graphics/Renderer.h"

namespace pw
{
	bool loadRenderer( RendererKind rendererKind )
	{
#		ifdef PW_PLATFORM_WIN32
		HINSTANCE hGetProcIDDLL = LoadLibrary(  );

		// Check if DLL is loaded.
		if ( hGetProcIDDLL == NULL )
		{
			std::cerr << "Could not load DLL \"" << dllName << "\"" << std::endl;
			exit( EXIT_FAILURE );
		}

		// Locate function in DLL.
		FARPROC lpfnGetProcessID = GetProcAddress( hGetProcIDDLL, funcName.c_str( ) );

		// Check if function was located.
		if ( !lpfnGetProcessID )
		{
			std::cerr << "Could not locate the function \"" << funcName << "\" in DLL\"" << dllName << "\"" << std::endl;
			exit( EXIT_FAILURE );
		}
#		endif
		return false;
	}
}