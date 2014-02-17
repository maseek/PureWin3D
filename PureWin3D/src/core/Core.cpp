#include "pch.h"
#include "../../include/core/Core.h"
#include "../../include/utils/timer/Timer.h"

namespace pw
{
	Core::Core( const ClientConfig& clientConfig ) : _running( true ), _clientView( clientConfig )
	{

	}
	bool Core::isRunning( ) const
	{
		return _running;
	}
	void Core::gameLoop()
	{
		double startTime = time( );
		double previousTime = 0;
		while ( _running )
		{
			double currentTime = time( ) - startTime;
			double fps = 1000 / ( currentTime - previousTime );
			std::cout << ( fps ) << '\n';
			previousTime = currentTime;
			InputMessage msg;
			while ( _clientView.popMessage( msg ) )
			{
				switch ( msg.type )
				{
				case InputMessage::Type::Close:
				{
					_clientView.close( );
					_running = false;
					break;
				}
				}
			}
		}
	}
}