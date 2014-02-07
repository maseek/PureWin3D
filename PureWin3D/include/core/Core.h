#ifndef PW_CORE_H
#define PW_CORE_H

#include "../utils/INoCopy.h"

namespace pw
{
	class Core : INoCopy
	{
	public:
		Core( );
		void run( );
	private:
		void update( double deltaMs );
	private:
		bool _running;
	};
}

#endif