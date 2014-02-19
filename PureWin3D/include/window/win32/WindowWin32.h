#ifndef PW_WINDOW_WIN_32_H 
#define PW_WINDOW_WIN_32_H

#include "../../core/ClientConfig.h"
#include "../InputMessage.h"

namespace pw
{
	typedef HWND WindowHandle;
	class Window
	{
	public:
		Window( const wchar_t* windowName, const ClientConfig& clientConfig );
		Window( const Window& ) = delete;
		Window& operator=( const Window& ) = delete;
	public:
		bool isOpen( ) const;
	public:
		void close( );
		void switchToFullscreen( );
		bool popMessage( InputMessage& message );
	public:
		static std::tuple<unsigned, unsigned, unsigned> getCurrentMode( );
	private:
		std::queue<InputMessage>	_messages;
		std::array<bool, 255>		_oldKeyStates;
		WindowHandle				_windowHandle;
		HCURSOR						_mouseCursor;
		unsigned					_width;
		unsigned					_height;
		unsigned					_bitsPerPx;
		WindowStyle					_windowStyle;
		bool						_open;
		bool						_mouseCaptured;
		const wchar_t*				_windowName;
	private:
		LRESULT CALLBACK wndProc( WindowHandle handle, UINT message, WPARAM wParam, LPARAM lParam );
		void processMessages( );
		void setMouseCursorVisibility( bool visible );
		void captureMouse( );
		void releaseMouse( );
		bool isOnlyInstance( );
	private:
		static void setWindowVisibility( WindowHandle windowHandle, bool visible );
		static LRESULT CALLBACK staticWndProc( WindowHandle handle, UINT message, WPARAM wParam, LPARAM lParam );
	};

}

#endif