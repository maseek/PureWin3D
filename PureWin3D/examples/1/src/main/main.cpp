#include "pch/pch.h"

#ifdef PW_DEBUG
#include <vld.h>
#endif

#include "core/Core.h"

int main( )
{
	pw::Core core;
	core.run( );
	return 0;
}