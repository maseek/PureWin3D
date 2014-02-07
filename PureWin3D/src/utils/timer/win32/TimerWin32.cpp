#include "pch.h"
#include "../../../../include/utils/timer/win32/TimerWin32.h"

namespace pw 
{
	const double TimerWin32::ELAPSED_TIME_ADDITION = 4294967296;
	const double TimerWin32::INVERSE_FPS_UPDATE_FRAME_COUNT = 0.125;
	const unsigned TimerWin32::FPS_UPDATE_FRAME_COUNT = 8;

	TimerWin32::TimerWin32( ) : _elapsedTimeMs( ELAPSED_TIME_ADDITION ), _fpsCounterAccumulatedTimeMs( 0 ), _inverseFps( 0 ), _fpsCounterCurrentFrame( 0 ), _lastUpdateTimeMs( findCurrentTimeMs( ) )
	{

	}

	double TimerWin32::update( )
	{
		double now = findCurrentTimeMs( );
		double deltaMs = now - _lastUpdateTimeMs;
		_lastUpdateTimeMs = now;
		_elapsedTimeMs += deltaMs;
		if ( _fpsCounterCurrentFrame++ < FPS_UPDATE_FRAME_COUNT )
		{
			_fpsCounterAccumulatedTimeMs += deltaMs;
		}
		else
		{
			_inverseFps = 0.001 * INVERSE_FPS_UPDATE_FRAME_COUNT * _fpsCounterAccumulatedTimeMs;
			_fpsCounterAccumulatedTimeMs = 0;
			_fpsCounterCurrentFrame = 0;
		}
		return deltaMs;
	}

	void TimerWin32::reset( )
	{
		_elapsedTimeMs = ELAPSED_TIME_ADDITION;
	}

	double TimerWin32::elapsedTime( ) const
	{
		return _elapsedTimeMs - ELAPSED_TIME_ADDITION;
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
		queryPerformanceFrequency( &frequency );
		// try using intristic __rdtsc( ) instead of QPC for better performance
		LARGE_INTEGER time;
		QueryPerformanceCounter( &time );
		// use previously used thread
		SetThreadAffinityMask( currentThread, previousMask );
		return 1000 * static_cast<double>( time.QuadPart ) / static_cast<double>( frequency.QuadPart );
	}

	void TimerWin32::queryPerformanceFrequency( LARGE_INTEGER* frequency )
	{
		QueryPerformanceFrequency( frequency );
	}
}
