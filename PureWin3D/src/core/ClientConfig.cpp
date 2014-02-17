#include "pch.h"
#include "../../include/core/ClientConfig.h"
#include "../../include/window/Window.h"

namespace pw
{
	ClientConfig::ClientConfig( ) : _windowStyle( WindowStyle::Default )
	{
		std::tie( _width, _height, _bitsPerPx ) = Window::getCurrentMode( );
	}
	unsigned ClientConfig::getWidth( ) const
	{
		return _width;
	}
	unsigned ClientConfig::getHeight( ) const
	{
		return _height;
	}
	unsigned ClientConfig::getBitsPerPx( ) const
	{
		return _bitsPerPx;
	}
	WindowStyle ClientConfig::getWindowStyle( ) const
	{
		return _windowStyle;
	}
}