#include "pch.h"
#include "../../../include/window/win32/WindowWin32.h"

namespace pw
{
	Window::Window( const wchar_t* windowName, const ClientConfig& clientConfig ) : _windowHandle( nullptr ), _mouseCursor( nullptr ), _width( clientConfig.getWidth( ) ), 
		_height( clientConfig.getHeight( ) ), _bitsPerPx( clientConfig.getBitsPerPx( ) ), _windowStyle( clientConfig.getWindowStyle( ) ), 
		_open( false ), _mouseCaptured( false ), _windowName( windowName )
	{
		if ( isOnlyInstance( ) )
		{
			// window class details
			WNDCLASSEX windowClass = { 0 };
			windowClass.cbSize = sizeof( WNDCLASSEX );
			windowClass.style = CS_VREDRAW | CS_HREDRAW;
			windowClass.lpfnWndProc = &staticWndProc;
			windowClass.cbClsExtra = 0;
			windowClass.cbWndExtra = 0;
			windowClass.hInstance = GetModuleHandle( nullptr );
			windowClass.hIcon = 0;
			windowClass.hIconSm = 0;
			windowClass.hCursor = 0;
			windowClass.hbrBackground = 0;
			windowClass.lpszMenuName = 0;
			windowClass.lpszClassName = _windowName;
			// register the window
			if ( RegisterClassEx( &windowClass ) )
			{
				// find position and size
				HDC screenDC = GetDC( nullptr );
				unsigned left = ( GetDeviceCaps( screenDC, HORZRES ) - _width ) / 2;
				unsigned top = ( GetDeviceCaps( screenDC, VERTRES ) - _height ) / 2;
				unsigned width = _width;
				unsigned height = _height;
				ReleaseDC( nullptr, screenDC );
				// set the style of the window
				DWORD style = WS_VISIBLE;
				if ( _windowStyle == WindowStyle::Windowed )
				{
					style |= WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_SYSMENU;
					// adjust the window size with the borders etc.
					RECT rectangle = { 0, 0, _width, _height };
					AdjustWindowRect( &rectangle, style, false );
					width = rectangle.right - rectangle.left;
					height = rectangle.bottom - rectangle.top;
				}
				// create the window
				_windowHandle = CreateWindowEx( 0, _windowName, _windowName, style, left, top, width, height, GetDesktopWindow( ), nullptr, GetModuleHandle( nullptr ), this );
				_open = true;
				if ( _windowStyle == WindowStyle::Fullscreen )
				{
					switchToFullscreen( );
				}
			}
		}
	}
	bool Window::isOpen( ) const
	{
		return _open;
	}
	void Window::close( )
	{
		// show cursor in case it was hidden
		setMouseCursorVisibility( true );
		ChangeDisplaySettings( 0, 0 );
		if ( _windowHandle )
		{
			DestroyWindow( _windowHandle );
		}
		// unregister window class
		UnregisterClass( _windowName, GetModuleHandle( nullptr ) );
		_open = false;
	}
	void Window::switchToFullscreen( )
	{
		// set display settings
		DEVMODE devMode;
		devMode.dmSize = sizeof( devMode );
		devMode.dmPelsWidth = _width;
		devMode.dmPelsHeight = _height;
		devMode.dmBitsPerPel = _bitsPerPx;
		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
		// change default display device settings
		if ( ChangeDisplaySettings( &devMode, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			return;
		}
		// set window style
		SetWindowLong( _windowHandle, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
		// set extended window style
		SetWindowLong( _windowHandle, GWL_EXSTYLE, WS_EX_APPWINDOW );
		// set window size, position and z-order
		SetWindowPos( _windowHandle, HWND_TOP, 0, 0, _width, _height, SWP_FRAMECHANGED );
		// show the window
		setWindowVisibility( _windowHandle, true );
	}
	bool Window::popMessage( InputMessage& message )
	{
		// if there are no messages in the queue, check for new ones
		if ( _messages.empty( ) )
		{
			processMessages( );
		}
		// if there are messages, pop a next message
		if ( !_messages.empty( ) )
		{
			message = _messages.front( );
			_messages.pop( );
			return true;
		}
		return false;
	}
	LRESULT CALLBACK Window::wndProc( WindowHandle handle, UINT message, WPARAM wParam, LPARAM lParam )
	{
		switch ( message )
		{
		case WM_CLOSE:
		{
			// create close message and push it to the queue
			InputMessage msg( InputMessage::Type::Close );
			_messages.push( msg );
			break;
		}
		default:
			// default window procedure
			return DefWindowProc( handle, message, wParam, lParam );
		}
		return 0;
	}
	void Window::processMessages( )
	{
		MSG message;
		while ( PeekMessage( &message, _windowHandle, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &message );
			DispatchMessage( &message );
		}
	}
	void Window::setMouseCursorVisibility( bool visible )
	{
		if ( visible )
		{
			if ( !_mouseCursor )
				_mouseCursor = LoadCursor( NULL, IDC_ARROW );
			SetCursor( _mouseCursor );
		}
		else
		{
			SetCursor( NULL );
		}
	}
	void Window::captureMouse( )
	{
		SetCapture( _windowHandle );
		_mouseCaptured = true;
	}
	void Window::releaseMouse( )
	{
		ReleaseCapture( );
		_mouseCaptured = false;
	}
	void Window::setWindowVisibility( WindowHandle windowHandle, bool visible )
	{
		ShowWindow( windowHandle, visible ? SW_SHOW : SW_HIDE );
		if ( visible )
		{
			SetFocus( windowHandle );
			SetForegroundWindow( windowHandle );
			SetActiveWindow( windowHandle );
		}
	}
	bool Window::isOnlyInstance( )
	{
		HANDLE handle = CreateMutex( nullptr, true, _windowName );
		if ( GetLastError( ) != ERROR_SUCCESS )
		{
			WindowHandle windowHandle = FindWindow( _windowName, nullptr );
			if ( windowHandle != nullptr )
			{
				setWindowVisibility( windowHandle, true );
				return false;
			}
		}
		return true;
	}
	LRESULT CALLBACK Window::staticWndProc( WindowHandle handle, UINT message, WPARAM wParam, LPARAM lParam )
	{
		Window* window;
		if ( message == WM_NCCREATE )
		{
			CREATESTRUCT *cs = ( CREATESTRUCT* ) lParam;
			window = ( Window* ) cs->lpCreateParams;
			SetLastError( 0 );
			if ( SetWindowLongPtr( handle, GWL_USERDATA, ( LONG_PTR ) window ) == 0 )
			{
				if ( GetLastError( ) != 0 )
					return FALSE;
			}
		}
		else
		{
			window = ( Window* ) GetWindowLongPtr( handle, GWL_USERDATA );
		}
		if ( window )
		{
			return window->wndProc( handle, message, wParam, lParam );
		}
		return DefWindowProc( handle, message, wParam, lParam );
	}
	std::tuple<unsigned, unsigned, unsigned> Window::getCurrentMode( )
	{
		DEVMODE mode;
		mode.dmSize = sizeof( mode );
		EnumDisplaySettings( nullptr, ENUM_CURRENT_SETTINGS, &mode );
		return std::make_tuple( mode.dmPelsWidth, mode.dmPelsHeight, mode.dmBitsPerPel );
	}
}