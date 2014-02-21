#include "pch.h"
#include "../../include/utils/SharedLibWin32.h"

namespace pw
{
	void* loadSharedLibrary( const std::string& path )
	{
		return nullptr;// LoadLibraryEx( path, 0, 0 );
	}
}