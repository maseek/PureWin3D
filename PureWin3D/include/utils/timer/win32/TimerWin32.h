#ifndef TIMER_WIN_32_H
#define TIMER_WIN_32_H

#include "../ITimer.h"

namespace pw
{
	class TimerWin32 : public ITimer<TimerWin32>
	{
	public:
		TimerWin32( );
		double update( );
		void reset( );
		double timeInMs( ) const;
		double inverseFps( ) const;
	private:
		double findCurrentTimeMs( );
	private:
		double		_lastUpdateTimeMs;
		double		_currentTimeMs;
		double		_inverseFps;
		double		_fpsCounterAccumulatedTimeMs;
		unsigned	_fpsCounterCurrentFrame;
	};

	extern const double TIMER_CURRENT_TIME_ADDITION;
	extern const double TIMER_INVERSE_FPS_UPDATE_FRAME_COUNT;
	extern const unsigned TIMER_FPS_UPDATE_FRAME_COUNT;
}

#endif