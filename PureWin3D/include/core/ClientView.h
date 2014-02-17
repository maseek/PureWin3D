#ifndef PW_CLIENT_VIEW_H 
#define PW_CLIENT_VIEW_H

#include "../window/Window.h"

namespace pw
{
	class ClientConfig;
	class ClientView
	{
	public:
		ClientView( const ClientConfig& clientConfig );
		ClientView( const ClientView& ) = delete;
		const ClientView& operator=( const ClientView& ) = delete;
	public:
		void close( );
		bool popMessage( InputMessage& message );
	private:
		Window _window; 
	private:
		static const wchar_t* WINDOW_NAME;
	};
}

#endif