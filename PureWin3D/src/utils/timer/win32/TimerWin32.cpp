#include "pch.h"
#include "../../../../include/utils/timer/win32/TimerWin32.h"

namespace pw 
{
	const double TIMER_CURRENT_TIME_ADDITION = 4294967296;
	const double TIMER_INVERSE_FPS_UPDATE_FRAME_COUNT = 0.125;
	const unsigned TIMER_FPS_UPDATE_FRAME_COUNT = 8;

	TimerWin32::TimerWin32( ) : _currentTimeMs( TIMER_CURRENT_TIME_ADDITION ), _fpsCounterAccumulatedTimeMs( 0 ), _inverseFps( 0 ), _fpsCounterCurrentFrame( 0 ), _lastUpdateTimeMs( findCurrentTimeMs( ) )
	{

	}

	double TimerWin32::update( )
	{
		double now = findCurrentTimeMs( );
		double deltaMs = now - _lastUpdateTimeMs;
		_lastUpdateTimeMs = now;
		_currentTimeMs += deltaMs;
		if ( _fpsCounterCurrentFrame++ < TIMER_FPS_UPDATE_FRAME_COUNT )
		{
			_fpsCounterAccumulatedTimeMs += deltaMs;
		}
		else
		{
			_inverseFps = 0.001 * TIMER_INVERSE_FPS_UPDATE_FRAME_COUNT * _fpsCounterAccumulatedTimeMs;
			_fpsCounterAccumulatedTimeMs = 0;
			_fpsCounterCurrentFrame = 0;
		}
		return deltaMs;
	}

	void TimerWin32::reset( )
	{
		_currentTimeMs = TIMER_CURRENT_TIME_ADDITION;
	}

	double TimerWin32::timeInMs( ) const
	{
		return _currentTimeMs - TIMER_CURRENT_TIME_ADDITION;
	}

	double TimerWin32::inverseFps( ) const
	{
		return _inverseFps;
	}

	double TimerWin32::findCurrentTimeMs( )
	{
		// use only single thread to calculate time
		HANDLE currentThread = GetCurrentThread( );
		DWORD_PTR previousMask = SetThreadAffinityMask( currentThread, 1 );
		static LARGE_INTEGER frequency;
		LARGE_INTEGER time;
		QueryPerformanceFrequency( &frequency );
		// try using intristic __rdtsc( ) instead of QPC for better performance
		QueryPerformanceCounter( &time );
		// use previously used thread
		SetThreadAffinityMask( currentThread, previousMask );
		return 1000 * static_cast<double>( time.QuadPart ) / static_cast<double>( frequency.QuadPart );
	}
}
