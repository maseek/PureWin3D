#ifndef TIMER_H
#define TIMER_H

#include "../../pch/pch.h"

#ifdef PW_PLATFORM_WIN32
#include "win32/TimerWin32.h"
namespace pw
{
	typedef TimerWin32 Timer;
}
#endif

#endif