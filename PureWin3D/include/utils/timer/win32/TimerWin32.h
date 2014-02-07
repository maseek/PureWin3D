#ifndef PW_TIMER_WIN_32_H
#define PW_TIMER_WIN_32_H

#include "../ITimer.h"

namespace pw
{
	class TimerWin32 : public ITimer<TimerWin32>
	{
	public:
		TimerWin32( );
		double update( );
		void reset( );
		double elapsedTime( ) const;
		double inverseFps( ) const;
	private:
		double findCurrentTimeMs( );
		static void queryPerformanceFrequency( LARGE_INTEGER* frequency );
	private:
		double		_lastUpdateTimeMs;
		double		_elapsedTimeMs;
		double		_inverseFps;
		double		_fpsCounterAccumulatedTimeMs;
		unsigned	_fpsCounterCurrentFrame;
		static const double ELAPSED_TIME_ADDITION;
		static const double INVERSE_FPS_UPDATE_FRAME_COUNT;
		static const unsigned FPS_UPDATE_FRAME_COUNT;
	};

}

#endif