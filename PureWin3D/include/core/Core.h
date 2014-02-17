#ifndef PW_WORLD_H 
#define PW_WORLD_H

#include "ClientView.h"

namespace pw
{
	class ClientConfig;
	class Core
	{
	public:
		explicit Core( const ClientConfig& clientConfig );
		Core( const Core& ) = delete;
		Core& operator=( const Core& ) = delete;
	public:
		bool isRunning( ) const;
	public:
		void gameLoop( );
	private:
		bool		_running;
		ClientView	_clientView;
	};
}

#endif