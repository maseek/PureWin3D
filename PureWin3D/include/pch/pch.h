///
/// precompiled header
///
#ifndef PCH_H
#define PCH_H

#if defined( _WIN32 ) || defined( __WIN32__ )
// Windows
#   define PW_PLATFORM_WIN32
// exclude rarely-used services from Windows headers
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   include <Windows.h>
#	include <cstdlib>
#else
#   error This operation system is not supported
#endif

// redefine new for debugging purposes
#if defined( _DEBUG ) || defined( DEBUG )
#	define PW_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#   define PW_DEBUG
#else
#	define PW_NEW new
#endif

// safe delete pointer
#ifndef PW_DELETE
#   define PW_DELETE( x ) delete x; x = nullptr;
#endif
// safe delete array
#ifndef PW_DELETE_ARRAY
#   define PW_DELETE_ARRAY( x ) delete [] x; x = nullptr;
#endif
// safe release
#ifndef PW_RELEASE
#   define PW_RELEASE( x ) if( x ) x->Release( ); x = nullptr;
#endif

namespace pw
{
	extern const double PI;
	extern const double TWO_PI;
}

#endif