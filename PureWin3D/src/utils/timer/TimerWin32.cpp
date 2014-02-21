#include "pch.h"
#include "../../../include/utils/timer/TimerWin32.h"

namespace pw 
{
	double time( )
	{
		// use only single thread to calculate time
		HANDLE currentThread = GetCurrentThread( );
		DWORD_PTR previousMask = SetThreadAffinityMask( currentThread, 1 );
		static LARGE_INTEGER frequency;
		QueryPerformanceFrequency( &frequency );
		// try using intristic __rdtsc( ) instead of QPC for better performance
		LARGE_INTEGER time;
		QueryPerformanceCounter( &time );
		// use previously used thread
		SetThreadAffinityMask( currentThread, previousMask );
		return 1000 * static_cast<double>( time.QuadPart ) / static_cast<double>( frequency.QuadPart );
	}
}
