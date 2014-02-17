#include "pch.h"
#include "../../include/core/ClientView.h"

namespace pw
{
	const wchar_t* ClientView::WINDOW_NAME = L"PureWin3D client";
	ClientView::ClientView( const ClientConfig& clientConfig ) : _window( WINDOW_NAME, clientConfig )
	{

	}
	void ClientView::close( )
	{
		_window.close( );
	}
	bool ClientView::popMessage( InputMessage& message )
	{
		return _window.popMessage( message );
	}
}