#include "pch/pch.h"

#ifdef PW_DEBUG
#include <vld.h>
#endif

#include "core/Core.h"
#include "core/ClientConfig.h"
#include "utils/timer/Timer.h"

using namespace pw;

int main( )
{
	ClientConfig clientConfig;
	Core core( clientConfig );
	core.gameLoop( );
	return 0;
}

