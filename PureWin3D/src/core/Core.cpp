#include "pch.h"
#include "../../include/core/Core.h"
#include "../../include/utils/timer/Timer.h"

namespace pw
{
	Core::Core( ) : _running( true )
	{

	}

	void Core::run( )
	{
		pw::Timer timer;
		while ( _running )
		{
			update( timer.update( ) );
		}
	}

	void Core::update( double deltaMs )
	{

	}
}